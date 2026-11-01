#include "audio.h"
#include "client.h"
#include "common_src/game_dtos.h"
#include "mapa.h"
#include "alrededores.h"
#include "granja.h"
#include "caverna.h"

#include <algorithm>
#include <iostream>
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

	Mapa mapa_granja(renderer, MAPA_GRANJA, 20, 20, 42);
	Mapa mapa_caverna(renderer, MAPA_CAVERNA, 20, 20, 7);
	
	Alrededores alrededores(renderer, mapa_granja.obtener_ancho(), mapa_granja.obtener_alto(), 42);

	// Casas y animales
	Granja granja(renderer);

	Caverna caverna(renderer);

	bool en_caverna = false;

	bool viendo_mapa = false;

	WorldState ultimo_estado;

	const int TILE = 64;
		
	// Todo el sonido (música, pasos y volúmenes) está en la clase Audio
	Audio audio;

  // Todo el sonido (música, pasos y volúmenes) está en la clase Audio
  Audio audio;

	Interfaz interfaz(renderer);

  TasaConstante tasa(std::chrono::milliseconds(16)); // 60 vueltas por segundo
  long vueltas = 1;

	// Se repite hasta  que el usuario cierre la ventana
	bool corriendo = true;
	while (corriendo) {
		// Proceso eventos
		SDL_Event evento;
		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT) {
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

			// 1 a 4 elegir herramienta
			if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym >= SDLK_1 && evento.key.keysym.sym <= SDLK_4) {
				inventario.seleccionar(evento.key.keysym.sym - SDLK_1);
			}

			if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_z) {
				en_caverna = !en_caverna;
				if (en_caverna) {
					audio.poner_musica_caverna();
				} else {
					audio.poner_musica_granja();
				}
			}

			if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_SPACE && en_caverna) {
				int frente_x = personaje.obtener_tile_x();
				int frente_y = personaje.obtener_tile_y();
				switch (personaje.obtener_direccion()) {
					case ARRIBA:
						frente_y--;
						break;
					case ABAJO:
						frente_y++;
						break;
					case IZQUIERDA:
						frente_x--;
						break;
					case DERECHA:
						frente_x++;
						break;
				}
				if (inventario.tengo_en_la_mano(PICO)) {
					personaje.picar();
					int roto = caverna.picar(frente_x, frente_y);

					if (roto == 0) inventario.agregar(ITEM_HIERRO, 1);
					if (roto == 1) inventario.agregar(ITEM_CARBON, 1);
					if (roto == 2) inventario.agregar(ITEM_LAPISLAZULI, 1);
					if (roto == 3) inventario.agregar(ITEM_ORO, 1);
				}
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
		WorldState state;
		if (client.try_get_latest_state(state)) {
			ultimo_estado = state;
			for (const PlayerPosition& jugador : state.players) {
				if (jugador.id == client.get_my_id()) {
					if (personaje.aplicar(jugador.x, jugador.y)) {
						audio.reproducir_paso();

						int x = personaje.obtener_tile_x();
						int y = personaje.obtener_tile_y();
						if (!en_caverna && granja.es_entrada_mina(x, y)) {
							en_caverna = true;
							audio.poner_musica_caverna();
						} else if (en_caverna && mapa_caverna.es_escalera(x, y)) {
							en_caverna = false;
							audio.poner_musica_granja();
						}
					}
				}
			}
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

		if (en_caverna) {
			mapa_caverna.dibujar(renderer, camara_x, camara_y, window.GetWidth(), window.GetHeight());
			caverna.dibujar(renderer, camara_x, camara_y);
		} else {
			mapa_granja.dibujar(renderer, camara_x, camara_y, window.GetWidth(), window.GetHeight());
			granja.dibujar(renderer, camara_x, camara_y);
			alrededores.dibujar(renderer, camara_x, camara_y, window.GetWidth(), window.GetHeight());
		}

    // Primero los demás jugadores, después el propio para que quede encima
    for (auto &par : otros)
      par.second->dibujar(renderer, camara_x, camara_y);
    personaje.dibujar(renderer, camara_x, camara_y);

		// Mapa completo (M)
		if (viendo_mapa) {
			const int MARGEN = 40;
			const int SEPARACION = 30;

			int ancho_total = mapa_granja.obtener_ancho() + mapa_caverna.obtener_ancho();
			int alto_maximo = std::max(mapa_granja.obtener_alto(), mapa_caverna.obtener_alto());
			int lado_ancho = (window.GetWidth() - 2 * MARGEN - SEPARACION) / ancho_total;
			int lado_alto = (window.GetHeight() - 2 * MARGEN) / alto_maximo;
			int lado = std::min(lado_ancho, lado_alto);

			int ancho_dibujo = lado * ancho_total + SEPARACION;
			int origen_granja_x = (window.GetWidth() - ancho_dibujo) / 2;
			int origen_caverna_x = origen_granja_x + mapa_granja.obtener_ancho() * lado + SEPARACION;
			int origen_y = (window.GetHeight() - alto_maximo * lado) / 2;

			//Fondo oscuro
			renderer.SetDrawColor(20, 20, 20, 255);
			renderer.Clear();

			mapa_granja.dibujar_completo(renderer, origen_granja_x, origen_y, lado);
			granja.dibujar(renderer, -origen_granja_x, -origen_y, lado);
			mapa_caverna.dibujar_completo(renderer, origen_caverna_x, origen_y, lado);
			caverna.dibujar(renderer, -origen_caverna_x, -origen_y, lado);

			// Figurita de cada jugador
			for (const PlayerPosition& jugador : ultimo_estado.players) {
				int origen_x = origen_granja_x;
				if (jugador.id == client.get_my_id() && en_caverna) {
					origen_x = origen_caverna_x;
				}
				personaje.dibujar_quieto(renderer, jugador.x, jugador.y, -origen_x, -origen_y, lado);
			}
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
