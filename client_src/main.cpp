#include "alrededores.h"
#include "audio.h"
#include "caverna.h"
#include "client.h"
#include "common_src/game_dtos.h"
#include "granja.h"
#include "inventario.h"
#include "pueblo.h"
#include "mapa_mundo.h"

#include "interfaz.h"
#include "mapa.h"
#include "pantalla.h"
#include "personaje.h"
#include "servicio_lobby_red.h"
#include "tasa_constante.h"
#include <algorithm>
#include <iostream>

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

// TODO : Revisar funcion, la pongo temporalmente para parsear de semilla a crop
bool es_semilla(ItemTypeDto item, CropTypeDto &cultivo) {
  switch (item) {
  case ItemTypeDto::SEED_STRAWBERRY:  cultivo = CropTypeDto::STRAWBERRY;  return true;
  case ItemTypeDto::SEED_GREEN_ONION: cultivo = CropTypeDto::GREEN_ONION; return true;
  case ItemTypeDto::SEED_POTATO:      cultivo = CropTypeDto::POTATO;      return true;
  case ItemTypeDto::SEED_PUMPKIN:     cultivo = CropTypeDto::PUMPKIN;     return true;
  default:                            return false;
  }
}
}

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

  // Mapas
  SectorStateDto farm, cavern, village;
  for (const SectorStateDto &sector : client.get_world_map().sectors) {
      if (sector.type == SectorTypeDto::FARM) farm = sector;
      if (sector.type == SectorTypeDto::CAVERN) cavern = sector;
      if (sector.type == SectorTypeDto::VILLAGE) village = sector;
  }
  Mapa mapa_granja(renderer, farm.type, farm.width, farm.height, 42);
  Mapa mapa_caverna(renderer, cavern.type, cavern.width, cavern.height, 7);
  Mapa mapa_pueblo(renderer, village.type, village.width, village.height, 42);
  mapa_granja.actualizar(farm.sector);
  mapa_caverna.actualizar(cavern.sector);
  mapa_pueblo.actualizar(village.sector);

  const int TILE = 64;

  Alrededores alrededores(renderer, mapa_granja.obtener_ancho(), mapa_granja.obtener_alto(), 42);

  Granja granja(renderer);
  Caverna caverna(renderer);
  Pueblo pueblo(renderer);

  MapaMundo mapa_mundo(client.get_world_map(), mapa_granja, mapa_pueblo, mapa_caverna, granja, pueblo, caverna);

  SectorTypeDto zona = SectorTypeDto::FARM;
  bool viendo_mapa = false;

  // Todo el sonido (música, pasos y volúmenes) está en la clase Audio
  Audio audio;
  Interfaz interfaz(renderer, servicio.codigo());

  Inventario inventario(renderer);

  TasaConstante tasa(std::chrono::milliseconds(16)); // 60 vueltas por segundo
  long vueltas = 1;

  // Los demás jugadores de la partida, por id
  std::map<size_t, std::unique_ptr<Personaje>> otros;
  SectorStateDto ultimo_estado;
	// Se repite hasta  que el usuario cierre la ventana
	bool corriendo = true;
	while (corriendo) {
		// Proceso eventos
		SDL_Event evento;
		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT) {
				if (!interfaz.click(evento.button.x, evento.button.y, audio)) {
					if (inventario.click(evento.button.x, evento.button.y, window.GetWidth(), window.GetHeight())) {
						ToolTypeDto herramienta = ToolTypeDto::PICKAXE;
						if (inventario.herramienta_seleccionada(herramienta)) {
							client.send_select_tool(herramienta);
						}
					}
				}
			}

      if (evento.type == SDL_QUIT) {
        corriendo = false;
      }
      // Si el usuario presiona ESC, se cierra la ventana
      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_ESCAPE) {
        corriendo = false;
      }

      // M abre y cierra mapa
      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_m) {
        viendo_mapa = !viendo_mapa;
      }

      // 1 a 9 seleccionar herramienta
      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym >= SDLK_1 && evento.key.keysym.sym <= SDLK_9) {
        inventario.seleccionar(evento.key.keysym.sym - SDLK_1);
		    ToolTypeDto herramienta = ToolTypeDto::PICKAXE;
		    if (inventario.herramienta_seleccionada(herramienta)) {
		      client.send_select_tool(herramienta);
        }
		  }

      // G: regalar el item seleccionado al que tengo enfrente
      // TODO: REVISAR
      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_g && evento.key.repeat == 0) {
        int frente_x = personaje.obtener_tile_x();
        int frente_y = personaje.obtener_tile_y();
        switch (personaje.obtener_direccion()) {
        case ARRIBA:    frente_y--; break;
        case ABAJO:     frente_y++; break;
        case IZQUIERDA: frente_x--; break;
        case DERECHA:   frente_x++; break;
        }
        int casillero = 0;
        auto receptor = ultimo_estado.players.find(GamePositionDto{
            .x = static_cast<size_t>(frente_x), .y = static_cast<size_t>(frente_y)});
        if (receptor != ultimo_estado.players.end() && inventario.indice_item_seleccionado(casillero)) {
          client.send_gift_offer(static_cast<int>(receptor->second.id), casillero);
        }
      }

      // Y / N: aceptar o rechazar el regalo
      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_y) client.send_gift_response(true);
      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_n) client.send_gift_response(false);

      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_SPACE && evento.key.repeat == 0) {
        int frente_x = personaje.obtener_tile_x();
        int frente_y = personaje.obtener_tile_y();

        DirectionDto dir = DirectionDto::Up;
        switch (personaje.obtener_direccion()) {
        case ARRIBA:
          dir = DirectionDto::Up;
          frente_y--;
          break;
        case ABAJO:
          dir = DirectionDto::Down;
          frente_y++;
          break;
        case IZQUIERDA:
          dir = DirectionDto::Left;
          frente_x--;
          break;
        case DERECHA:
          dir = DirectionDto::Right;
          frente_x++;
          break;
        }
        InventorySlotDto en_la_mano;
        CropTypeDto cultivo = CropTypeDto::STRAWBERRY;

        if (zona == SectorTypeDto::CAVERN) {
          if (inventario.tengo_en_la_mano(PICO) && !personaje.esta_picando()) {
            personaje.picar();
            client.send_mine(dir);
          }
        } else if (inventario.tengo_en_la_mano(PALA)) {
            client.send_till(dir);
        } else if (inventario.item_seleccionado(en_la_mano) &&
                   es_semilla(en_la_mano.item, cultivo)) {
            client.send_plant(frente_x, frente_y, cultivo);
        } else {
            client.send_collect(dir);
        }
      }

      if (evento.type == SDL_KEYDOWN && evento.key.repeat == 0) {
        switch (evento.key.keysym.sym) {
        case SDLK_UP:
          personaje.mirar(ARRIBA);
          client.send_move(DirectionDto::Up);
          break;
        case SDLK_DOWN:
          personaje.mirar(ABAJO);
          client.send_move(DirectionDto::Down);
          break;
        case SDLK_LEFT:
          personaje.mirar(IZQUIERDA);
          client.send_move(DirectionDto::Left);
          break;
        case SDLK_RIGHT:
          personaje.mirar(DERECHA);
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
      ultimo_estado = state;

		if (state.type != zona) {
      zona = state.type;
      switch (zona) {
        case SectorTypeDto::CAVERN: audio.poner_musica_caverna(); break;
        case SectorTypeDto::VILLAGE: audio.poner_musica_pueblo(); break;
        default: audio.poner_musica_granja(); break;
      }
    }

  if (zona == SectorTypeDto::CAVERN) {
    mapa_caverna.actualizar(state.sector);
    caverna.actualizar(state.entities);
  } else if (zona == SectorTypeDto::VILLAGE) {
    mapa_pueblo.actualizar(state.sector);
    pueblo.actualizar(state.entities);
  } else {
    mapa_granja.actualizar(state.sector);
    granja.actualizar(state.entities);
  }

    // Actualizar jugadores
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
          personaje.agarrar(jugador.actualTool);
          if (!jugador.inventory.empty()) { // TODO : revisar esto, vamos a cambiar el inventory.front seguro
            inventario.actualizar(jugador.inventory.front());
          }
          continue;
        }
        presentes.insert(jugador.id);
        std::unique_ptr<Personaje> &otro = otros[jugador.id];
        if (!otro) {
          otro = std::make_unique<Personaje>(renderer); // recién llegado
          otro->vestir(SOMBREROS_SDL[static_cast<int>(jugador.outfit.hat)],
                       PELOS_SDL[static_cast<int>(jugador.outfit.hair)],
                       PANTALONES_SDL[static_cast<int>(jugador.outfit.pants)],
                       REMERAS_SDL[static_cast<int>(jugador.outfit.tshirt)]);
        }
        otro->aplicar(x, y);
        otro->agarrar(jugador.actualTool);
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
    caverna.animar(vueltas);
    pueblo.animar(vueltas);

    // Cámara centrada en el personaje
    int camara_x = personaje.obtener_tile_x() * TILE + TILE / 2 - window.GetWidth() / 2;
    int camara_y = personaje.obtener_tile_y() * TILE - window.GetHeight() / 2;

    Mapa *mapa_actual = &mapa_granja;
    if (zona == SectorTypeDto::CAVERN) {
      mapa_actual = &mapa_caverna;
    } else if (zona == SectorTypeDto::VILLAGE) {
      mapa_actual = &mapa_pueblo;
    }

    renderer.SetDrawColor(0, 0, 0, 255);
    renderer.Clear();

    mapa_actual->dibujar(renderer, camara_x, camara_y, window.GetWidth(), window.GetHeight());

    if (zona == SectorTypeDto::CAVERN) {
      caverna.dibujar(renderer, camara_x, camara_y);
    } else if (zona == SectorTypeDto::FARM) {
      granja.dibujar(renderer, camara_x, camara_y);
      alrededores.dibujar(renderer, camara_x, camara_y, window.GetWidth(), window.GetHeight());
    } else {
      pueblo.dibujar(renderer, camara_x, camara_y);
    }

    // Primero los demas jugadores
    for (auto &par : otros) {
      par.second->dibujar(renderer, camara_x, camara_y);
    }
    personaje.dibujar(renderer, camara_x, camara_y);
    
    // Mapa del mundo (M)
    if (viendo_mapa) {
      mapa_mundo.dibujar(renderer, window.GetWidth(), window.GetHeight(), zona, personaje);
    }

    interfaz.dibujar(renderer, audio);

    if (!viendo_mapa) {
      inventario.dibujar(renderer, window.GetWidth(), window.GetHeight());
    }

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
