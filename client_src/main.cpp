#include "audio.h"
#include "personaje.h"
#include "tasa_constante.h"
#include "client.h"
#include "interfaz.h"
#include "common_src/game_dtos.h"
#include "mapa.h"
#include "granja.h"
#include "caverna.h"

#include <iostream>
#include <exception>
#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <SDL.h>
#include <SDL_image.h>

using namespace SDL2pp;

int main(int argc, char* argv[]) try {

	if (argc != 3 && argc != 4) {
		std::cerr << "Uso: " << argv[0] << " <host> <puerto> [codigo de partida]" << std::endl;
		return 1;
	}

	Client client(argv[1], argv[2]);

	// Lobby
	std::string codigo;
	if (argc == 4) {
		codigo = argv[3];
	} else {
		codigo = client.create_match("Granja");
		std::cout << "Partida creada. Código para unirse: " << codigo << std::endl;
	}
	if (!client.join_match(codigo)) {
		std::cerr << "No existe la partida con código " << codigo << std::endl; 
		return 1;
	}

	// Initialize SDL library
	SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	SDLImage image(IMG_INIT_PNG);

	SDLTTF ttf;

	// Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
	Window window("SDL2pp demo",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			640, 480,
			SDL_WINDOW_RESIZABLE);

	// Create accelerated video renderer with default driver
	Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

	// El granjero: carga sus texturas, su ropa y su posición
	Personaje personaje(renderer);

	Mapa mapa_granja(renderer, MAPA_GRANJA, 20, 20, 42);
	Mapa mapa_caverna(renderer, MAPA_CAVERNA, 20, 20, 7);

	// Cass y animales
	Granja granja(renderer);

	Caverna caverna(renderer);

	bool en_caverna = false;

	const int TILE = 64;
		
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

			if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_4) {
				audio.subir_volumen_pasos();
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
				caverna.picar(frente_x, frente_y);
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
						client.send_move(Direction::Up);
						break;
					case SDLK_DOWN:
						client.send_move(Direction::Down);
						break;
					case SDLK_LEFT:
						client.send_move(Direction::Left);
						break;
					case SDLK_RIGHT:
						client.send_move(Direction::Right);
						break;
					default:
						break;
				}
			}
		}

		// Respuesta del servidor
		WorldState state;
		if (client.try_get_latest_state(state)) {
			for (const PlayerPosition& jugador : state.players) {
				if (jugador.id == client.get_my_id()) {
					if (personaje.aplicar(jugador.x, jugador.y)) {
						audio.reproducir_paso();
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

		granja.animar(vueltas);

		// Cámara centrada en el personaje así nunca se sale de la pantalla
		int camara_x = personaje.obtener_tile_x() * TILE + TILE / 2 - window.GetWidth() / 2;
		int camara_y = personaje.obtener_tile_y() * TILE - window.GetHeight() / 2;

		renderer.Clear();

		if (en_caverna) {
			mapa_caverna.dibujar(renderer, camara_x, camara_y, window.GetWidth(), window.GetHeight());
			caverna.dibujar(renderer, camara_x, camara_y);
		} else {
			mapa_granja.dibujar(renderer, camara_x, camara_y, window.GetWidth(), window.GetHeight());
			granja.dibujar(renderer, camara_x, camara_y);
		}

		// Granjero
		personaje.dibujar(renderer, camara_x, camara_y);

		interfaz.dibujar(renderer, audio);

		renderer.Present();

		// esperar al próximo casillero de 16 ms. si me pasé, se saltean vueltas
		vueltas = tasa.esperar();
	}

	// Here all resources are automatically released and library deinitialized
	return 0;
} catch (std::exception& e) {
	// If case of error, print it and exit with error
	std::cerr << e.what() << std::endl;
	return 1;
}
