#include "alrededores.h"
#include "audio.h"
#include "caverna.h"
#include "client.h"
#include "common_src/game_dtos.h"
#include "constantes_sdl.h"
#include "granja.h"
#include "inventario.h"
#include "mapa_mundo.h"
#include "pueblo.h"

#include "interfaz.h"
#include "mapa.h"
#include "pantalla.h"
#include "personaje.h"
#include "servicio_lobby_red.h"
#include "tasa_constante.h"
#include <algorithm>

#include <QApplication>

#include <cmath>
#include <cstdlib>
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
const int SOMBREROS_SDL[] = ROPA_SOMBREROS_SDL;
const int PELOS_SDL[] = ROPA_PELOS_SDL;
const int PANTALONES_SDL[] = ROPA_PANTALONES_SDL;
const int REMERAS_SDL[] = ROPA_REMERAS_SDL;

void mostrarLobby(int &argc, char *argv[], ServicioLobby &servicio) {
  QApplication app(argc, argv);
  Pantalla pantalla(servicio);
  pantalla.show();
  QApplication::exec();
}

// TODO : Revisar funcion, la pongo temporalmente para parsear de semilla a crop
bool es_semilla(ItemTypeDto item, CropTypeDto &cultivo) {
  switch (item) {
  case ItemTypeDto::SEED_STRAWBERRY:
    cultivo = CropTypeDto::STRAWBERRY;
    return true;
  case ItemTypeDto::SEED_GREEN_ONION:
    cultivo = CropTypeDto::GREEN_ONION;
    return true;
  case ItemTypeDto::SEED_POTATO:
    cultivo = CropTypeDto::POTATO;
    return true;
  case ItemTypeDto::SEED_PUMPKIN:
    cultivo = CropTypeDto::PUMPKIN;
    return true;
  default:
    return false;
  }
}
} // namespace

int main(int argc, char *argv[]) try {
  if (argc != CANTIDAD_ARGUMENTOS) {
    std::cerr << TEXTO_JUEGO_USO << argv[0] << TEXTO_JUEGO_ARGUMENTOS
              << std::endl;
    return EXIT_FAILURE;
  }

  Client client(argv[ARGUMENTO_HOST], argv[ARGUMENTO_PUERTO]);
  ServicioLobbyRed servicio(client);

  mostrarLobby(argc, argv, servicio);
  if (!servicio.estaEnPartida())
    return EXIT_SUCCESS; // cerró el lobby sin entrar a ninguna partida

  // Initialize SDL library
  SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  SDLImage image(IMG_INIT_PNG);
  SDLTTF ttf;

  // Ventana redimensionable, con el código de la partida en el título
  Window window(TEXTO_JUEGO_TITULO_VENTANA + servicio.codigo(),
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, VENTANA_ANCHO,
                VENTANA_ALTO, SDL_WINDOW_RESIZABLE);

  // Create accelerated video renderer with default driver
  Renderer renderer(window, RENDERER_DRIVER_POR_DEFECTO,
                    SDL_RENDERER_ACCELERATED);

  // El granjero: carga sus texturas, su ropa y su posición
  Personaje personaje(renderer);
  const DatosPersonaje &elegido = servicio.personajeElegido();
  personaje.vestir(
      SOMBREROS_SDL[elegido.ropa.gorro], PELOS_SDL[elegido.ropa.pelo],
      PANTALONES_SDL[elegido.ropa.pantalon], REMERAS_SDL[elegido.ropa.remera]);

  // Mapas
  SectorStateDto farm, cavern, village;
  for (const SectorStateDto &sector : client.get_world_map().sectors) {
    if (sector.type == SectorTypeDto::FARM)
      farm = sector;
    if (sector.type == SectorTypeDto::CAVERN)
      cavern = sector;
    if (sector.type == SectorTypeDto::VILLAGE)
      village = sector;
  }
  Mapa mapa_granja(renderer, farm.type, farm.width, farm.height,
                   SEMILLA_GRANJA);
  Mapa mapa_caverna(renderer, cavern.type, cavern.width, cavern.height,
                    SEMILLA_CAVERNA);
  Mapa mapa_pueblo(renderer, village.type, village.width, village.height,
                   SEMILLA_PUEBLO);
  mapa_granja.actualizar(farm.sector);
  mapa_caverna.actualizar(cavern.sector);
  mapa_pueblo.actualizar(village.sector);

  Alrededores alrededores(renderer, mapa_granja.obtener_ancho(),
                          mapa_granja.obtener_alto(), SEMILLA_ALREDEDORES);

  Granja granja(renderer);
  Caverna caverna(renderer);
  Pueblo pueblo(renderer);

  MapaMundo mapa_mundo(renderer, client.get_world_map(), mapa_granja,
                       mapa_pueblo, mapa_caverna, granja, pueblo, caverna);

  SectorTypeDto zona = SectorTypeDto::FARM;
  bool viendo_mapa = false;

  // Todo el sonido (música, pasos y volúmenes) está en la clase Audio
  Audio audio;
  Interfaz interfaz(renderer, servicio.codigo());

  Inventario inventario(renderer);

  TasaConstante tasa(std::chrono::milliseconds(LOOP_PERIODO_MS));
  long vueltas = 1;

  const SDL2pp::Color fondo = COLOR_FONDO_JUEGO;

  // Los demás jugadores de la partida, por id
  std::map<size_t, std::unique_ptr<Personaje>> otros;
  SectorStateDto ultimo_estado;
  // Se repite hasta  que el usuario cierre la ventana
  bool corriendo = true;
  while (corriendo) {
    // Proceso eventos
    SDL_Event evento;
    while (SDL_PollEvent(&evento)) {
      if (evento.type == SDL_MOUSEBUTTONDOWN &&
          evento.button.button == SDL_BUTTON_LEFT) {
        int mouse_x = evento.button.x;
        int mouse_y = evento.button.y;
        int camara_x = personaje.obtener_tile_x() * TAMANIO_TILE +
                       TAMANIO_TILE / 2 - window.GetWidth() / 2;
        int camara_y =
            personaje.obtener_tile_y() * TAMANIO_TILE - window.GetHeight() / 2;
        bool acepto = false;

        if (interfaz.click_regalo(mouse_x, mouse_y, acepto)) {
          client.send_gift_response(acepto);
        } else if (pueblo.hay_tienda_abierta()) {
          switch (pueblo.click_tienda(mouse_x, mouse_y)) {
          case Pueblo::COMPRAR:
            // TODO
            break;
          case Pueblo::VENDER:
            // TODO
            break;
          case Pueblo::HABLAR:
            // TODO
            break;
          case Pueblo::SALIR:
            pueblo.cerrar_tienda();
            break;
          default:
            break;
          }
        } else if (zona == SectorTypeDto::VILLAGE &&
                   pueblo.click_npc(mouse_x, mouse_y, camara_x, camara_y)) {
          // Se abre la tienda del npc
        } else if (!interfaz.click(mouse_x, mouse_y, audio)) {
          if (inventario.click(mouse_x, mouse_y, window.GetWidth(),
                               window.GetHeight())) {
            ToolTypeDto herramienta = ToolTypeDto::PICKAXE;
            if (inventario.herramienta_seleccionada(herramienta)) {
              client.send_select_tool(herramienta);
            }
          } else {
            int casillero = 0;
            if (inventario.indice_item_seleccionado(casillero)) {
              int tile_x = static_cast<int>(
                  std::floor((mouse_x + camara_x) / double(TAMANIO_TILE)));
              int tile_y = static_cast<int>(
                  std::floor((mouse_y + camara_y) / double(TAMANIO_TILE)));

              for (const auto &[posicion, jugador] : ultimo_estado.players) {
                int px = static_cast<int>(posicion.x);
                int py = static_cast<int>(posicion.y);

                bool lo_toque =
                    px == tile_x && (py == tile_y || py == tile_y + 1);

                int distancia = std::abs(px - personaje.obtener_tile_x()) +
                                std::abs(py - personaje.obtener_tile_y());

                bool es_otro =
                    static_cast<int>(jugador.id) != client.get_my_id();

                if (lo_toque && es_otro && distancia == REGALO_DISTANCIA) {
                  client.send_gift_offer(static_cast<int>(jugador.id),
                                         casillero);
                }
              }
            }
          }
        }
      }

      if (evento.type == SDL_QUIT) {
        corriendo = false;
      }
      // Si el usuario presiona ESC, se cierra la ventana
      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == TECLA_SALIR) {
        if (pueblo.hay_tienda_abierta()) {
          pueblo.cerrar_tienda();
        } else {
          corriendo = false;
        }
      }

      // M abre y cierra mapa
      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == TECLA_MAPA) {
        viendo_mapa = !viendo_mapa;
      }

      // 1 a 9 seleccionar herramienta
      if (evento.type == SDL_KEYDOWN &&
          evento.key.keysym.sym >= TECLA_PRIMER_CASILLERO &&
          evento.key.keysym.sym <= TECLA_ULTIMO_CASILLERO) {
        inventario.seleccionar(evento.key.keysym.sym - TECLA_PRIMER_CASILLERO);
        ToolTypeDto herramienta = ToolTypeDto::PICKAXE;
        if (inventario.herramienta_seleccionada(herramienta)) {
          client.send_select_tool(herramienta);
        }
      }

      // Y / N: aceptar o rechazar el regalo
      if (evento.type == SDL_KEYDOWN &&
          evento.key.keysym.sym == TECLA_ACEPTAR_REGALO) {
        client.send_gift_response(true);
        interfaz.cerrar_regalo();
      }
      if (evento.type == SDL_KEYDOWN &&
          evento.key.keysym.sym == TECLA_RECHAZAR_REGALO) {
        client.send_gift_response(false);
        interfaz.cerrar_regalo();
      }

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

      if (evento.type == SDL_KEYDOWN &&
          evento.key.keysym.sym == TECLA_CHEAT_RIEGO && evento.key.repeat == 0)
        client.send_cheat_water(dir);

      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_t &&
          evento.key.repeat == 0)
        client.send_chat("Hola, gente!");

      if (evento.type == SDL_KEYDOWN &&
          evento.key.keysym.sym == TECLA_CHEAT_CRECIMIENTO &&
          evento.key.repeat == 0)
        client.send_cheat_growth();

      if (evento.type == SDL_KEYDOWN &&
          evento.key.keysym.sym == TECLA_CHEAT_DIA &&
          evento.key.repeat == 0)
        client.send_end_day_cheat();


      if (evento.type == SDL_KEYDOWN &&
          evento.key.keysym.sym == SDLK_k &&
          evento.key.repeat == 0)
        client.send_enemies_damage_cheat();
      
      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == TECLA_ACCION &&
          evento.key.repeat == 0) {
        InventorySlotDto en_la_mano;
        CropTypeDto cultivo = CropTypeDto::STRAWBERRY;

        if (inventario.tengo_en_la_mano(ESPADA)) {
          client.send_attack(dir);
        } else if (zona == SectorTypeDto::CAVERN) {
          if (inventario.tengo_en_la_mano(PICO) && !personaje.esta_picando()) {
            personaje.picar();
            client.send_mine(dir);
          }
        } else if (inventario.tengo_en_la_mano(PALA)) {
          client.send_till(dir);
        } else if (inventario.tengo_en_la_mano(REGADERA)) {
          client.send_water(dir);
        } else if (inventario.item_seleccionado(en_la_mano) &&
                   es_semilla(en_la_mano.item, cultivo)) {
          client.send_plant(frente_x, frente_y, cultivo);
        } else {
          client.send_collect(dir);
        }
      }

      if (evento.type == SDL_KEYDOWN && evento.key.repeat == 0 &&
          !pueblo.hay_tienda_abierta()) {
        switch (evento.key.keysym.sym) {
        case TECLA_ARRIBA:
          personaje.mirar(ARRIBA);
          client.send_move(DirectionDto::Up);
          break;
        case TECLA_ABAJO:
          personaje.mirar(ABAJO);
          client.send_move(DirectionDto::Down);
          break;
        case TECLA_IZQUIERDA:
          personaje.mirar(IZQUIERDA);
          client.send_move(DirectionDto::Left);
          break;
        case TECLA_DERECHA:
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
      interfaz.actualizar_tiempo(renderer, state.time, state.dayNumber);

      if (state.type != zona) {
        pueblo.cerrar_tienda();
        zona = state.type;
        switch (zona) {
        case SectorTypeDto::CAVERN:
          audio.poner_musica_caverna();
          break;
        case SectorTypeDto::VILLAGE:
          audio.poner_musica_pueblo();
          break;
        default:
          audio.poner_musica_granja();
          break;
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
          // Si perdió vida en la caverna, le pegaron los de al lado
          if (zona == SectorTypeDto::CAVERN &&
              jugador.life < personaje.obtener_vida()) {
            caverna.golpearon_a(x, y);
          }
          personaje.agarrar(jugador.actualTool);
          if (!jugador.inventory.empty()) { // TODO : revisar esto, vamos a
                                            // cambiar el inventory.front seguro
            inventario.actualizar(jugador.inventory.front());
          }
          personaje.poner_vida(jugador.life);
          personaje.poner_energia(jugador.energy);
          interfaz.actualizar_monedas(renderer, jugador.coins);
          interfaz.actualizar_regalo(jugador.pendingGift);
          continue;
        }
        presentes.insert(jugador.id);
        std::unique_ptr<Personaje> &otro = otros[jugador.id];
        bool recien_llegado = !otro;
        if (recien_llegado) {
          otro = std::make_unique<Personaje>(renderer);
          otro->vestir(SOMBREROS_SDL[static_cast<int>(jugador.outfit.hat)],
                       PELOS_SDL[static_cast<int>(jugador.outfit.hair)],
                       PANTALONES_SDL[static_cast<int>(jugador.outfit.pants)],
                       REMERAS_SDL[static_cast<int>(jugador.outfit.tshirt)]);
        }
        otro->aplicar(x, y);
        if (zona == SectorTypeDto::CAVERN && !recien_llegado &&
            jugador.life < otro->obtener_vida()) {
          caverna.golpearon_a(x, y);
        }
        otro->poner_vida(jugador.life);
        otro->poner_energia(jugador.energy);
        otro->agarrar(jugador.actualTool);
      }
      // Los que ya no vienen en el estado se fueron de la partida
      std::erase_if(otros, [&presentes](const auto &par) {
        return !presentes.contains(par.first);
      });
    }

    // Si se cortó la conexión, se cierra el juego
    if (!client.is_connected()) {
      std::cerr << TEXTO_JUEGO_CONEXION_PERDIDA << STRING_BRK;
      corriendo = false;
    }

    personaje.animar(vueltas);
    for (auto &par : otros)
      par.second->animar(vueltas);

    granja.animar(vueltas);
    caverna.animar(vueltas);
    pueblo.animar(vueltas);

    // Cámara centrada en el personaje
    int camara_x = personaje.obtener_tile_x() * TAMANIO_TILE +
                   TAMANIO_TILE / 2 - window.GetWidth() / 2;
    int camara_y =
        personaje.obtener_tile_y() * TAMANIO_TILE - window.GetHeight() / 2;

    Mapa *mapa_actual = &mapa_granja;
    if (zona == SectorTypeDto::CAVERN) {
      mapa_actual = &mapa_caverna;
    } else if (zona == SectorTypeDto::VILLAGE) {
      mapa_actual = &mapa_pueblo;
    }

    renderer.SetDrawColor(fondo);
    renderer.Clear();

    mapa_actual->dibujar(renderer, camara_x, camara_y, window.GetWidth(),
                         window.GetHeight());

    if (zona == SectorTypeDto::CAVERN) {
      caverna.dibujar(renderer, camara_x, camara_y);
    } else if (zona == SectorTypeDto::FARM) {
      granja.dibujar(renderer, camara_x, camara_y);
      alrededores.dibujar(renderer, camara_x, camara_y, window.GetWidth(),
                          window.GetHeight());
    } else {
      pueblo.dibujar(renderer, camara_x, camara_y);
    }

    // Primero los demas jugadores
    for (auto &par : otros) {
      par.second->dibujar(renderer, camara_x, camara_y);
    }
    personaje.dibujar(renderer, camara_x, camara_y);

    interfaz.dibujar_noche(renderer);

    pueblo.dibujar_tienda(renderer, personaje);

    // Mapa del mundo (M)
    if (viendo_mapa) {
      mapa_mundo.dibujar(renderer, window.GetWidth(), window.GetHeight(), zona,
                         personaje);
    }

    interfaz.dibujar(renderer, audio);

    if (interfaz.hay_regalo_pendiente()) {
      interfaz.dibujar_regalo(renderer);
      inventario.dibujar_regalo(renderer, interfaz.regalo_pendiente(),
                                interfaz.lugar_icono_regalo());
    }

    if (!viendo_mapa) {
      inventario.dibujar(renderer, window.GetWidth(), window.GetHeight());
    }

    renderer.Present();

    // esperar al próximo casillero de 16 ms. si me pasé, se saltean vueltas
    vueltas = tasa.esperar();
  }

  // Here all resources are automatically released and library deinitialized
  return EXIT_SUCCESS;
} catch (std::exception &e) {
  // If case of error, print it and exit with error
  std::cerr << e.what() << std::endl;
  return EXIT_FAILURE;
}
