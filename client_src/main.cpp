#include "alrededores.h"
#include "audio.h"
#include "caverna.h"
#include "chat.h"
#include "client.h"
#include "common_src/game_dtos.h"
#include "constantes_sdl.h"
#include "granja.h"
#include "inventario.h"
#include "mapa_mundo.h"
#include "pueblo.h"
#include "centro_comunitario.h"
#include "ventana_cofre.h"
#include "decoraciones.h"

#include "interfaz.h"
#include "mapa.h"
#include "pantalla.h"
#include "personaje.h"
#include "servicio_lobby_red.h"
#include "tasa_constante.h"
#include <algorithm>
#include "Pantallas/PantallaFinDeJuego/pantallafinjuego.h"
#include "constantes_pantallas.h"

#include <QApplication>
#include <QFontDatabase>

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

void mostrarLobby(ServicioLobby &servicio) {
  Pantalla pantalla(servicio);
  pantalla.show();
  QApplication::exec();
}

void mostrarFinDeJuego() {
  QFontDatabase::addApplicationFont(RUTA_FUENTE);
  PantallaFinJuego pantalla;
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

  QApplication app(argc, argv);
  Client client(argv[ARGUMENTO_HOST], argv[ARGUMENTO_PUERTO]);
  ServicioLobbyRed servicio(client);

  mostrarLobby(servicio);
  if (!servicio.estaEnPartida())
    return EXIT_SUCCESS; // cerró el lobby sin entrar a ninguna partida

  // Initialize SDL library
  SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  SDLImage image(IMG_INIT_PNG);
  SDLTTF ttf;

  // Ventana redimensionable, con el código de la partida en el título
  Window window(TEXTO_JUEGO_TITULO_VENTANA + servicio.codigoPartidaActual(),
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, VENTANA_ANCHO,
                VENTANA_ALTO, SDL_WINDOW_RESIZABLE);

  // Create accelerated video renderer with default driver
  Renderer renderer(window, RENDERER_DRIVER_POR_DEFECTO,
                    SDL_RENDERER_ACCELERATED);

  // El granjero: carga sus texturas, su ropa y su posición
  Personaje personaje(renderer);
  const DatosPersonaje &elegido = servicio.personajeEnPartida();
  personaje.vestir(
      SOMBREROS_SDL[elegido.ropa.gorro], PELOS_SDL[elegido.ropa.pelo],
      PANTALONES_SDL[elegido.ropa.pantalon], REMERAS_SDL[elegido.ropa.remera]);

  // Mapas
  SectorStateDto farm, cavern, village, centro_comunitario;
  for (const SectorStateDto &sector : client.get_world_map().sectors) {
    if (sector.type == SectorTypeDto::FARM)
      farm = sector;
    if (sector.type == SectorTypeDto::CAVERN)
      cavern = sector;
    if (sector.type == SectorTypeDto::VILLAGE)
      village = sector;
    if (sector.type == SectorTypeDto::COMMUNITY_CENTER)
      centro_comunitario = sector;
  }
  Mapa mapa_granja(renderer, farm.type, farm.width, farm.height,
                   SEMILLA_GRANJA);
  Mapa mapa_caverna(renderer, cavern.type, cavern.width, cavern.height,
                    SEMILLA_CAVERNA);
  Mapa mapa_pueblo(renderer, village.type, village.width, village.height,
                   SEMILLA_PUEBLO);
  Mapa mapa_centro(renderer, centro_comunitario.type, centro_comunitario.width, centro_comunitario.height, SEMILLA_PUEBLO);

  Mapa mapa_cabana(renderer, SectorTypeDto::CABIN, CABANA_ANCHO, CABANA_ALTO, 0);

  mapa_granja.actualizar(farm.sector);
  mapa_caverna.actualizar(cavern.sector);
  mapa_pueblo.actualizar(village.sector);
  mapa_centro.actualizar(centro_comunitario.sector);

  Alrededores alrededores(renderer, mapa_granja.obtener_ancho(),
                          mapa_granja.obtener_alto(), SEMILLA_ALREDEDORES);

  Granja granja(renderer);
  Granja muebles_cabana(renderer);
  granja.actualizar_edificios(farm.buildings);
  Caverna caverna(renderer);
  Pueblo pueblo(renderer);
  Decoraciones decoraciones(renderer);
  pueblo.actualizar_edificios(village.buildings);
  CentroComunitario centro(renderer);

  MapaMundo mapa_mundo(renderer, client.get_world_map(), mapa_granja,
                       mapa_pueblo, mapa_caverna, granja, pueblo, caverna);

  SectorTypeDto zona = SectorTypeDto::FARM;
  long vueltas_hasta_paso = 0;
  int camara_granja_x = 0;
  int camara_granja_y = 0;
  bool viendo_mapa = false;

  // Todo el sonido (música, pasos y volúmenes) está en la clase Audio
  Audio audio;
  Interfaz interfaz(renderer, servicio.codigoPartidaActual());

  Inventario inventario(renderer);
  Chat chat(renderer);
  VentanaCofre ventana_cofre;

  TasaConstante tasa(std::chrono::milliseconds(LOOP_PERIODO_MS));
  long vueltas = 1;

  const SDL2pp::Color fondo = COLOR_FONDO_JUEGO;

  // Los demás jugadores de la partida, por id
  std::map<size_t, std::unique_ptr<Personaje>> otros;
  SectorStateDto ultimo_estado;
  // Se repite hasta  que el usuario cierre la ventana
  bool corriendo = true;
  bool fin_de_juego = false; // prueba para la pantalla de fin de juego!!
  while (corriendo) {
    // Proceso eventos
    SDL_Event evento;
    while (SDL_PollEvent(&evento)) {
      std::string mensaje;
      if (chat.manejar_evento(evento, mensaje)) {
        if (!mensaje.empty())
          client.send_chat(mensaje);
        continue;
      }
      if (evento.type == SDL_MOUSEBUTTONDOWN &&
          evento.button.button == SDL_BUTTON_LEFT) {
        int mouse_x = evento.button.x;
        int mouse_y = evento.button.y;
        int camara_x = personaje.obtener_tile_x() * TAMANIO_TILE +
                       TAMANIO_TILE / 2 - window.GetWidth() / 2;
        int camara_y = personaje.obtener_tile_y() * TAMANIO_TILE - window.GetHeight() / 2;
        if (zona == SectorTypeDto::FARM) {
          camara_granja_x = camara_x;
          camara_granja_y = camara_y;
        }
        bool acepto = false;
        GamePositionDto posicion_npc;

        int casillero_cofre = 0;
        if (ventana_cofre.click(mouse_x, mouse_y, window.GetWidth(),
                                window.GetHeight(), casillero_cofre)) {
          client.send_chest_move(casillero_cofre, false);
        } else if (ventana_cofre.esta_abierta() &&
                   inventario.click(mouse_x, mouse_y, window.GetWidth(),
                                    window.GetHeight()) &&
                   inventario.indice_item_seleccionado(casillero_cofre)) {
          client.send_chest_move(casillero_cofre, true);
        } else if (interfaz.click_regalo(mouse_x, mouse_y, acepto)) {
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
                   pueblo.click_npc(mouse_x, mouse_y, camara_x, camara_y,
                                    posicion_npc)) {
          client.send_interact(posicion_npc);
        } else if (zona == SectorTypeDto::COMMUNITY_CENTER) {
          CentroComunitario::AccionCentro accion =
              centro.click_set(mouse_x, mouse_y, camara_x, camara_y);
          if (accion == CentroComunitario::CANJEAR) {
            int slot = 0;
            InventorySlotDto casillero;
            if (inventario.indice_item_seleccionado(slot) &&
                inventario.item_seleccionado(casillero)) {
              client.send_redeem_set(centro.get_set_abierto(), slot, casillero.count);
            }
          }
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
          evento.key.keysym.sym == TECLA_CHEAT_DIA && evento.key.repeat == 0)
        client.send_end_day_cheat();

      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_k &&
          evento.key.repeat == 0)
        client.send_enemies_damage_cheat();

      if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == TECLA_ACCION &&
          evento.key.repeat == 0) {
        InventorySlotDto en_la_mano;
        CropTypeDto cultivo = CropTypeDto::STRAWBERRY;

        if (inventario.tengo_en_la_mano(ESPADA)) {
          client.send_attack(dir);
          if (zona == SectorTypeDto::CAVERN) {
            caverna.golpear(frente_x, frente_y);
          }
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
          client.send_interact({static_cast<size_t>(frente_x),
                                static_cast<size_t>(frente_y)});

          int casillero = 0;
          if (inventario.indice_item_seleccionado(casillero))
            client.send_place(casillero, dir);
        }
      }
    }

    // Respuesta del servidor
    SectorStateDto state;
    if (client.try_get_latest_state(state)) {
      ultimo_estado = state;
      centro.actualizar_sets(state.sets);
      chat.agregar(state.chat);
      ventana_cofre.actualizar(state.entities);
      interfaz.actualizar_tiempo(renderer, state.time, state.dayNumber);

      // Cambio de zona y música
      if (state.type != zona) {
        pueblo.cerrar_tienda();
        centro.cerrar_set();
        zona = state.type;
        switch (zona) {
        case SectorTypeDto::CAVERN:
          audio.poner_musica_caverna();
          break;
        case SectorTypeDto::VILLAGE:
        case SectorTypeDto::COMMUNITY_CENTER:
          audio.poner_musica_pueblo();
          break;
        default:
          audio.poner_musica_granja();
          break;
        }
      }

      // Actualizar mapa
      if (zona == SectorTypeDto::CAVERN) {
        mapa_caverna.actualizar(state.sector);
        caverna.actualizar(state.entities);
      } else if (zona == SectorTypeDto::VILLAGE) {
        mapa_pueblo.actualizar(state.sector);
        pueblo.actualizar(state.entities);
        pueblo.actualizar_edificios(state.buildings);
      } else if (zona == SectorTypeDto::COMMUNITY_CENTER) {
        mapa_centro.actualizar(state.sector);
      } else if (zona == SectorTypeDto::CABIN) {
        mapa_cabana.actualizar(state.sector);
        muebles_cabana.actualizar(state.entities);
      } else {
        mapa_granja.actualizar(state.sector);
        granja.actualizar(state.entities);
        granja.actualizar_edificios(state.buildings);
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
          // prueba para la pantalla de fin de juego!! es el if
          if(jugador.coins >= MONEDAS_FIN_DE_JUEGO_PRUEBA){
          	fin_de_juego = true;
            corriendo = false;
          }
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

    vueltas_hasta_paso -= vueltas;
    bool puede_caminar = !pueblo.hay_tienda_abierta() && !centro.hay_set_abierto() && !personaje.esta_muerto();
    if (vueltas_hasta_paso <= 0 && puede_caminar) {
      const Uint8 *teclado = SDL_GetKeyboardState(nullptr);
      bool camino = true;
      if (teclado[SDL_GetScancodeFromKey(TECLA_ARRIBA)]) {
        personaje.mirar(ARRIBA);
        client.send_move(DirectionDto::Up);
      } else if (teclado[SDL_GetScancodeFromKey(TECLA_ABAJO)]) {
        personaje.mirar(ABAJO);
        client.send_move(DirectionDto::Down);
      } else if (teclado[SDL_GetScancodeFromKey(TECLA_IZQUIERDA)]) {
        personaje.mirar(IZQUIERDA);
        client.send_move(DirectionDto::Left);
      } else if (teclado[SDL_GetScancodeFromKey(TECLA_DERECHA)]) {
        personaje.mirar(DERECHA);
        client.send_move(DirectionDto::Right);
      } else {
        camino = false;
      }
      if (camino) {
        vueltas_hasta_paso = personaje.vueltas_por_paso();
      }
    }

    personaje.animar(vueltas);
    for (auto &par : otros)
      par.second->animar(vueltas);

    granja.animar(vueltas);
    muebles_cabana.animar(vueltas);
    caverna.animar(vueltas);
    pueblo.animar(vueltas);

    // Cámara centrada en el personaje
    int camara_x = personaje.obtener_tile_x() * TAMANIO_TILE +
                   TAMANIO_TILE / 2 - window.GetWidth() / 2;
    int camara_y =
        personaje.obtener_tile_y() * TAMANIO_TILE - window.GetHeight() / 2;

    // Elegir mapa
    Mapa *mapa_actual = &mapa_granja;
    if (zona == SectorTypeDto::CAVERN) {
      mapa_actual = &mapa_caverna;
    } else if (zona == SectorTypeDto::VILLAGE) {
      mapa_actual = &mapa_pueblo;
    } else if (zona == SectorTypeDto::COMMUNITY_CENTER) {
      mapa_actual = &mapa_centro;
    } else if (zona == SectorTypeDto::CABIN) {
      mapa_actual = &mapa_cabana;
    }

    renderer.SetDrawColor(fondo);
    renderer.Clear();

    if (zona == SectorTypeDto::CABIN) {
      mapa_granja.dibujar(renderer, camara_granja_x, camara_granja_y, window.GetWidth(), window.GetHeight());
      granja.dibujar(renderer, camara_granja_x, camara_granja_y);
      alrededores.dibujar(renderer, camara_granja_x, camara_granja_y, window.GetWidth(), window.GetHeight());

      const SDL2pp::Color oscurecer = COLOR_CABANA_OSCURECER;
      renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
      renderer.SetDrawColor(oscurecer);
      renderer.FillRect(SDL2pp::Rect(0, 0, window.GetWidth(), window.GetHeight()));
    }

    mapa_actual->dibujar(renderer, camara_x, camara_y, window.GetWidth(),
                         window.GetHeight());
                         decoraciones.dibujar(renderer, mapa_actual->obtener_decoraciones(), camara_x, camara_y);

    // Dibujo lo que va encima del mapa
    if (zona == SectorTypeDto::CAVERN) {
      caverna.dibujar(renderer, camara_x, camara_y);
    } else if (zona == SectorTypeDto::FARM) {
      granja.dibujar(renderer, camara_x, camara_y);
      alrededores.dibujar(renderer, camara_x, camara_y, window.GetWidth(),
                          window.GetHeight());
    } else if (zona == SectorTypeDto::VILLAGE) {
      pueblo.dibujar(renderer, camara_x, camara_y);
    } else if (zona == SectorTypeDto::COMMUNITY_CENTER) {
      centro.dibujar(renderer, camara_x, camara_y);
    } else if (zona == SectorTypeDto::CABIN) {
      muebles_cabana.dibujar(renderer, camara_x, camara_y);
    }

    // Primero los demas jugadores
    for (auto &par : otros) {
      par.second->dibujar(renderer, camara_x, camara_y);
    }
    personaje.dibujar(renderer, camara_x, camara_y);

    interfaz.dibujar_noche(renderer);

    pueblo.dibujar_tienda(renderer, personaje);

    centro.dibujar_set(renderer);

    // Mapa del mundo (M)
    if (viendo_mapa) {
      mapa_mundo.dibujar(renderer, window.GetWidth(), window.GetHeight(), zona,
                         personaje);
    }

    interfaz.dibujar(renderer, audio);
    chat.dibujar(window.GetHeight());
    ventana_cofre.dibujar(renderer, inventario, window.GetWidth(), window.GetHeight());

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

  // prueba para la pantalla de fin de juego!! todo este if
  if(fin_de_juego){
  	window.Hide();
    mostrarFinDeJuego();
  }

  // Here all resources are automatically released and library deinitialized
  return EXIT_SUCCESS;
} catch (std::exception &e) {
  // If case of error, print it and exit with error
  std::cerr << e.what() << std::endl;
  return EXIT_FAILURE;
}
