#include "audio.h"
#include "client.h"
#include "common_src/game_dtos.h"
#include "granja.h"
#include "interfaz.h"
#include "mapa.h"
#include "pantalla.h"
#include "personaje.h"
#include "servicio_lobby_red.h"
#include "tasa_constante.h"

#include <QApplication>
#include <QFontDatabase>
#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>

#include <SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL_image.h>

using SDL2pp::Renderer;
using SDL2pp::SDL;
using SDL2pp::SDLImage;
using SDL2pp::SDLTTF;
using SDL2pp::Window;

namespace {
const int SOMBREROS_SDL[] = {45, 4, 40, 61, 121, 99};
const int PELOS_SDL[] = {9, 10, 33, 69, 21, 27};
const int PANTALONES_SDL[] = {0, 2, 5, 6};
const int REMERAS_SDL[] = {9, 19, 36, 27, 104};

void mostrarLobby(int &argc, char *argv[], ServicioLobby &servicio) {
  QApplication app(argc, argv);
  QFontDatabase::addApplicationFont(
      ":/fuentes/assets/fuentes/Stardew_Valley.otf");
  Pantalla pantalla(servicio);
  pantalla.show();
  QApplication::exec();
}
} // namespace

int main(int argc, char *argv[]) try {

  if (argc != 3) {
    std::cerr << "Uso: " << argv[0] << " <host> <puerto>" << std::endl;
    return 1;
  }

  Client client(argv[1], argv[2]);
  ServicioLobbyRed servicio(client);

  mostrarLobby(argc, argv, servicio);
  if (!servicio.estaEnPartida())
    return 0; // cerró el lobby sin entrar a ninguna partida

  // Initialize SDL library
  SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

  SDLImage image(IMG_INIT_PNG);

  SDLTTF ttf;

  // Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
  Window window("Stardew Valley - Partida " + servicio.codigo(),
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
                SDL_WINDOW_RESIZABLE);

  // Create accelerated video renderer with default driver
  Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

  // El granjero: carga sus texturas, su ropa y su posición
  Personaje personaje(renderer);

  const DatosPersonaje &elegido = servicio.personajeElegido();
  personaje.vestir(
      SOMBREROS_SDL[elegido.ropa.gorro], PELOS_SDL[elegido.ropa.pelo],
      PANTALONES_SDL[elegido.ropa.pantalon], REMERAS_SDL[elegido.ropa.remera]);

  // Suelo
  Mapa mapa(renderer, 20, 20, 42);

  // Cass y animales
  Granja granja(renderer);

  const int TILE = 64;

  // Todo el sonido (música, pasos y volúmenes) está en la clase Audio
  Audio audio;

  Interfaz interfaz(renderer);

  TasaConstante tasa(std::chrono::milliseconds(16)); // 60 vueltas por segundo
  long vueltas = 1;

  // Los demás jugadores de la partida, por id
  std::map<size_t, std::unique_ptr<Personaje>> otros;

  // Se repite hasta  que el usuario cierre la ventana
  bool corriendo = true;
  while (corriendo) {
    // Proceso eventos
    SDL_Event evento;
    while (SDL_PollEvent(&evento)) {
      if (evento.type == SDL_MOUSEBUTTONDOWN &&
          evento.button.button == SDL_BUTTON_LEFT) {
        interfaz.click(evento.button.x, evento.button.y, audio);
      }

      if (evento.type == SDL_QUIT) {
        corriendo = false;
      }
      // Si el usuario presiona ESC, se cierra la ventana
      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_ESCAPE) {
        corriendo = false;
      }

      // M cambia música
      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_m) {
        audio.cambiar_musica();
      }

      // Bajar y subir musica
      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_1) {
        audio.bajar_volumen_musica();
      }
      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_2) {
        audio.subir_volumen_musica();
      }

      // Bajar y subir pasos
      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_3) {
        audio.bajar_volumen_pasos();
      }

      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_4) {
        audio.subir_volumen_pasos();
      }

      // Cambiar de prenda
      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_p) {
        personaje.cambiar_pantalon();
      }

      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_r) {
        personaje.cambiar_remera();
      }

      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_c) {
        personaje.cambiar_pelo();
      }

      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_h) {
        personaje.cambiar_sombrero();
      }

      // Cambiar color (O pantalon, V pelo)
      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_o) {
        personaje.cambiar_color_pantalon();
      }

      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_v) {
        personaje.cambiar_color_pelo();
      }

      if (evento.type == SDL_KEYDOWN && evento.key.repeat == 0) {
        switch (evento.key.keysym.sym) {
        case SDLK_UP:
          client.send_move(DirectionDto::Up);
          break;
        case SDLK_DOWN:
          client.send_move(DirectionDto::Down);
          break;
        case SDLK_LEFT:
          client.send_move(DirectionDto::Left);
          break;
        case SDLK_RIGHT:
          client.send_move(DirectionDto::Right);
          break;
        default:
          break;
        }
      }
    }

    // Respuesta del servidor
    SectorStateDto state;
    if (client.try_get_latest_state(state)) {
      std::set<size_t> presentes;
      const size_t mi_id = static_cast<size_t>(client.get_my_id());
      // players es un mapa: posición -> jugador
      for (const auto &[posicion, jugador] : state.players) {
        const int x = static_cast<int>(posicion.x);
        const int y = static_cast<int>(posicion.y);
        if (jugador.id == mi_id) {
          if (personaje.aplicar(x, y)) {
            audio.reproducir_paso();
          }
          continue;
        }
        presentes.insert(jugador.id);
        std::unique_ptr<Personaje> &otro = otros[jugador.id];
        if (!otro) {
          otro = std::make_unique<Personaje>(renderer); // recién llegado
        }
        otro->aplicar(x, y);
      }
      // Los que ya no vienen en el estado se fueron de la partida
      std::erase_if(otros, [&presentes](const auto &par) {
        return !presentes.contains(par.first);
      });
    }

    // Si se cortó la conexión, se cierra el juego
    if (!client.is_connected()) {
      std::cerr << "Se perdió la conexión con el servidor." << STRING_BRK;
      corriendo = false;
    }

    personaje.animar(vueltas);
    for (auto &par : otros)
      par.second->animar(vueltas);

    granja.animar(vueltas);

    // Cámara centrada en el personaje así nunca se sale de la pantalla
    int camara_x =
        personaje.obtener_tile_x() * TILE + TILE / 2 - window.GetWidth() / 2;
    int camara_y = personaje.obtener_tile_y() * TILE - window.GetHeight() / 2;

    renderer.Clear();
    mapa.dibujar(renderer, camara_x, camara_y, window.GetWidth(),
                 window.GetHeight());

    granja.dibujar(renderer, camara_x, camara_y);

    // Primero los demás jugadores, después el propio para que quede encima
    for (auto &par : otros)
      par.second->dibujar(renderer, camara_x, camara_y);
    personaje.dibujar(renderer, camara_x, camara_y);

    interfaz.dibujar(renderer, audio);

    renderer.Present();

    // esperar al próximo casillero de 16 ms. si me pasé, se saltean vueltas
    vueltas = tasa.esperar();
  }

  // Here all resources are automatically released and library deinitialized
  return 0;
} catch (std::exception &e) {
  // If case of error, print it and exit with error
  std::cerr << e.what() << std::endl;
  return 1;
}
