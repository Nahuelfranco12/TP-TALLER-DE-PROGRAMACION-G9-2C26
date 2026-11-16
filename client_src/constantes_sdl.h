#ifndef CONSTANTES_SDL_H_
#define CONSTANTES_SDL_H_

// Ventana y loop
#define CANTIDAD_ARGUMENTOS 3
#define ARGUMENTO_HOST 1
#define ARGUMENTO_PUERTO 2
#define VENTANA_ANCHO 640
#define VENTANA_ALTO 480
#define RENDERER_DRIVER_POR_DEFECTO (-1)
#define LOOP_PERIODO_MS 16 // 60 vueltas por segundo

// Mapa: tiles, escala y generación de decoración
#define TAMANIO_TILE_ASSET 16
#define ESCALA_SPRITES 4
#define TAMANIO_TILE (TAMANIO_TILE_ASSET * ESCALA_SPRITES)
#define MAPA_MARGEN 30
#define MAPA_DADO_DECORACION_MAXIMO 9
#define SEMILLA_GRANJA 42
#define SEMILLA_CAVERNA 7
#define SEMILLA_PUEBLO 42
#define SEMILLA_ALREDEDORES 42

// Letras de la grilla del mapa
#define LETRA_PASTO '.'
#define LETRA_BORDE ','
#define LETRA_BORDE_CAVERNA '#'
#define LETRA_TIERRA 'T'
#define LETRA_ARADO 'X'
#define LETRA_PUERTA 'e'
#define LETRA_PARED 'w'
#define LETRA_PISO_CAVERNA 'p'
#define LETRA_CAVERNA_DECORACION_1 'q'
#define LETRA_CAVERNA_DECORACION_2 'r'
#define LETRA_PISO_PUEBLO 'c'
#define LETRA_FLORES 'f'

// Bosque alrededor de la granja (medidas en tiles)
#define BOSQUE_ZONA 30
#define BOSQUE_SEPARACION 3
#define BOSQUE_DESPLAZAMIENTO_MAXIMO (BOSQUE_SEPARACION - 2)
#define BOSQUE_PORCENTAJE 50
#define BOSQUE_DADO_MAXIMO 99
#define BOSQUE_DISTANCIA_GRANJA 1
#define BOSQUE_MARGEN 4
#define BOSQUE_SOMBRA 200

// Mapa general, tecla M (medidas en tiles salvo que diga px)
#define MUNDO_MARGEN 8
#define MUNDO_SEPARACION 14
#define MUNDO_PASILLO 10
#define MUNDO_BAJADA_PUEBLO 24
#define MUNDO_MARGEN_PANTALLA 16
#define MUNDO_TILES_DIFUMINADO 3
#define MUNDO_BLOQUE_PASTO 4
#define MUNDO_ENTRE_ARBOLES 2
#define MUNDO_SEMILLA 42
#define MUNDO_DADO_MAXIMO 9
#define MUNDO_PROBABILIDAD_ARBOL 7
#define MUNDO_PROBABILIDAD_PINO 4
#define MUNDO_ARBOL_TILES 3
#define MUNDO_FIGURA_TILES 4
#define MUNDO_FIGURA_MINIMA 12

// Granja
#define GRANJA_CASA_TILE_X 2
#define GRANJA_CASA_TILE_Y 1
#define GRANJA_CASA_MODELO 0
#define ANIMAL_CUADROS_ANIMACION 4
#define ANIMAL_VUELTAS_POR_CUADRO 20 // 20 x 16 ms = 0,3 s
#define PRODUCTO_VUELTAS_POR_SALTO 20
#define PRODUCTO_SALTO 1
#define CULTIVO_ULTIMA_ETAPA                                                   \
  { 5, 5, 6, 5 }
#define CULTIVO_CRECIMIENTO_MAXIMO 3

// Caverna: golpes restantes de un mineral
#define CAVERNA_GOLPES_GOLPEADO 2
#define CAVERNA_GOLPES_CASI_ROTO 1

// Pueblo: tiendas (el índice es el mismo para puesto, NPC, título y fondo)
#define TIENDA_PIERRE 0
#define TIENDA_CLINT 1
#define TIENDA_ROBIN 2
#define TIENDA_MARNIE 3
#define TIENDA_CERRADA (-1)
#define PUEBLO_PUESTOS                                                         \
  {                                                                            \
    {10, 20, TIENDA_PIERRE}, {30, 36, TIENDA_CLINT}, {29, 3, TIENDA_ROBIN}, {  \
      52, 18, TIENDA_MARNIE                                                    \
    }                                                                          \
  }
#define PUEBLO_NPCS                                                            \
  {                                                                            \
    {15, 29, TIENDA_PIERRE}, {34, 44, TIENDA_CLINT}, {37, 13, TIENDA_ROBIN}, { \
      57, 29, TIENDA_MARNIE                                                    \
    }                                                                          \
  }
#define NPC_CUADROS_ANIMACION 4
#define NPC_VUELTAS_POR_CUADRO 12
#define TIENDA_TAMANIO_LETRA 20
#define TIENDA_CANTIDAD_BOTONES 4
#define TIENDA_ALTO_BOTON 36
#define TIENDA_SEPARACION_BOTONES 12
#define TIENDA_RELLENO_BOTON 12
#define TIENDA_LADO_PERSONAJES 48
#define TIENDA_MARGEN_ANCHO 40
#define TIENDA_MARGEN_ALTO 140
#define TIENDA_MARGEN_TITULO 10
#define TIENDA_MARGEN_BOTONES 10

// Personaje: ropa inicial, caminar y picar
#define PERSONAJE_PANTALON_INICIAL 0
#define PERSONAJE_REMERA_INICIAL 5
#define PERSONAJE_PELO_INICIAL 3
#define PERSONAJE_SOMBRERO_INICIAL 2
#define PERSONAJE_COLOR_PANTALON_INICIAL 0
#define PERSONAJE_COLOR_PELO_INICIAL 1
#define PERSONAJE_VUELTAS_POR_PASO 16
#define PERSONAJE_CUADROS_CAMINAR 4
#define PERSONAJE_VUELTAS_POR_CUADRO 9 // 9 x 16 ms = 0,15 s
#define PERSONAJE_REBOTE 1
#define PERSONAJE_CUADROS_PICAR 5
#define PERSONAJE_VUELTAS_POR_CUADRO_PICAR 5
#define PERSONAJE_DURACION_PICAR                                               \
  (PERSONAJE_CUADROS_PICAR * PERSONAJE_VUELTAS_POR_CUADRO_PICAR)

// Ropa elegida en el lobby: índice de Qt -> índice en las hojas de SDL
#define ROPA_SOMBREROS_SDL                                                     \
  { 45, 4, 40, 61, 121, 99 }
#define ROPA_PELOS_SDL                                                         \
  { 9, 10, 33, 69, 21, 27 }
#define ROPA_PANTALONES_SDL                                                    \
  { 0, 2, 5, 6 }
#define ROPA_REMERAS_SDL                                                       \
  { 9, 19, 36, 27, 104 }

// Barras de vida y energía (px)
#define BARRA_VALOR_MAXIMO 100.0
#define BARRA_ANCHO 48
#define BARRA_ALTO 6
#define BARRA_SEPARACION 2
#define BARRA_BORDE 1

// Día y noche
#define DIA_HORA_INICIO 6
#define MINUTOS_POR_HORA 60
#define NOCHE_HORA_ATARDECER 18
#define NOCHE_HORA_OSCURA 22
#define NOCHE_OSCURIDAD_MAXIMA 170
#define RELOJ_MINIMO_DOS_CIFRAS 10

// HUD (px)
#define HUD_TAMANIO_LETRA 16
#define HUD_MARGEN 16
#define HUD_ALTO_BOTON 32
#define HUD_RELLENO 8
#define HUD_SEPARACION_CAJAS 8
#define HUD_ANCHO_BOTON_MUSICA 90
#define HUD_BOTON_MENOS_X 114
#define HUD_BOTON_MAS_X 254
#define HUD_RAYITAS_VOLUMEN 8 // MIX_MAX_VOLUME / AUDIO_INCREMENTO_VOLUMEN
#define HUD_RAYITA_X 152
#define HUD_RAYITA_PASO 12
#define HUD_RAYITA_Y 22
#define HUD_RAYITA_ANCHO 8
#define HUD_RAYITA_ALTO 20

// Teclas
#define TECLA_SALIR SDLK_ESCAPE
#define TECLA_MAPA SDLK_m
#define TECLA_PRIMER_CASILLERO SDLK_1
#define TECLA_ULTIMO_CASILLERO SDLK_9
#define TECLA_ACEPTAR_REGALO SDLK_y
#define TECLA_RECHAZAR_REGALO SDLK_n
#define TECLA_CHEAT_RIEGO SDLK_c
#define TECLA_CHEAT_CRECIMIENTO SDLK_COMMA
#define TECLA_ACCION SDLK_SPACE
#define TECLA_ARRIBA SDLK_UP
#define TECLA_ABAJO SDLK_DOWN
#define TECLA_IZQUIERDA SDLK_LEFT
#define TECLA_DERECHA SDLK_RIGHT

// Cartel de regalo (px)
#define REGALO_ANCHO 280
#define REGALO_ALTO 140
#define REGALO_MARGEN_TITULO 10
#define REGALO_ICONO_Y 40
#define REGALO_MARGEN_BOTONES 20
#define REGALO_BOTONES_DESDE_ABAJO 44
#define REGALO_ANCHO_BOTON 110

// Inventario (px)
#define INVENTARIO_HERRAMIENTAS 4
#define INVENTARIO_ITEMS 9
#define INVENTARIO_CASILLEROS (INVENTARIO_HERRAMIENTAS + INVENTARIO_ITEMS)
#define INVENTARIO_LADO_CASILLERO 44
#define INVENTARIO_SEPARACION 12
#define INVENTARIO_MARGEN_ABAJO 10
#define INVENTARIO_LADO_ICONO 32
#define INVENTARIO_TAMANIO_LETRA 11
#define INVENTARIO_NUMERO_MARGEN_X 3
#define INVENTARIO_NUMERO_MARGEN_Y 1
#define INVENTARIO_ESTRELLA_MARGEN 3
#define DIGITOS_DECIMALES 10

// Paleta de colores de la ropa
#define COLOR_ROPA_AZUL                                                        \
  { 60, 90, 200 }
#define COLOR_ROPA_MARRON                                                      \
  { 150, 80, 30 }
#define COLOR_ROPA_NEGRO                                                       \
  { 40, 30, 20 }
#define COLOR_ROPA_RUBIO                                                       \
  { 230, 190, 90 }
#define COLOR_ROPA_ROJO                                                        \
  { 200, 60, 40 }
#define COLOR_ROPA_VERDE                                                       \
  { 70, 150, 70 }
#define COLOR_ROPA_BLANCO                                                      \
  { 230, 230, 230 }
#define COLOR_ROPA_VIOLETA                                                     \
  { 150, 80, 200 }
#define PALETA_ROPA                                                            \
  {                                                                            \
    COLOR_ROPA_AZUL, COLOR_ROPA_MARRON, COLOR_ROPA_NEGRO, COLOR_ROPA_RUBIO,    \
        COLOR_ROPA_ROJO, COLOR_ROPA_VERDE, COLOR_ROPA_BLANCO,                  \
        COLOR_ROPA_VIOLETA                                                     \
  }
#define PALETA_ROPA_CANTIDAD 8

// Rutas de assets
//#define RUTA_ASSETS "assets/"
#define RUTA_FUENTE_JUEGO "assets/fuentes/DejaVuSans-Bold.ttf"
#define RUTA_ARBOL "assets/mapas/tree1.png"
#define RUTA_PINO "assets/mapas/tree1_2.png"
#define RUTA_TILESET_GRANJA "assets/mapas/ground_01_16x16.png"
#define RUTA_TILESET_CAVERNA "assets/mapas/Dungeon_Tileset.png"
#define RUTA_TILESET_PUEBLO "assets/mapas/PelicanTown_Buildings.png"
#define RUTA_MUEBLES "assets/mapas/Tilesets_Furniture.png"
#define RUTA_OFRENDAS_CENTRO_COMUNITARIO "assets/mapas/ComunityCenter_Offerings.png"
#define RUTA_MINERALES "assets/caverna/ore.png"
#define RUTA_CASAS "assets/edificios/House.png"
#define RUTA_EDIFICIOS_PUEBLO "assets/edificios/PelicanTown_Buildings.png"
#define RUTA_VACA "assets/animales/Female Cow Brown.png"
#define RUTA_GALLINA "assets/animales/Chicken Blonde  Green.png"
#define RUTA_CULTIVOS "assets/cultivos/Spring Crops.png"
#define RUTA_ICONOS_MINERALES "assets/inventario/ore.png"
#define RUTA_ICONOS_CULTIVOS "assets/inventario/Spring Crops.png"
#define RUTA_HUEVO "assets/inventario/egg.png"
#define RUTA_LECHE "assets/inventario/milk.png"
#define RUTA_ESPADA "assets/inventario/sword.png"
#define RUTA_PICO "assets/inventario/pickaxe.png"
#define RUTA_PALA "assets/inventario/shovel.png"
#define RUTA_REGADERA "assets/inventario/watering_can.png"
#define RUTA_PERSONAJE_CUERPO "assets/personaje/StardewValley_Character_Farmer Base.png"
#define RUTA_PERSONAJE_PANTALONES "assets/personaje/StardewValley_Character_Pants.png"
#define RUTA_PERSONAJE_REMERAS "assets/personaje/StardewValley_Character_Shirts.png"
#define RUTA_PERSONAJE_PELOS "assets/personaje/StardewValley_Character_Hairstyles.png"
#define RUTA_PERSONAJE_SOMBREROS "assets/personaje/StardewValley_Character_Hats.png"
#define RUTA_NPC_PIERRE "assets/npcs/pierre.png"
#define RUTA_NPC_CLINT "assets/npcs/clint.png"
#define RUTA_NPC_ROBIN "assets/npcs/robin.png"
#define RUTA_NPC_MARNIE "assets/npcs/marnie.png"
#define RUTA_TIENDA_PIERRE "assets/tiendas/pierre.png"
#define RUTA_TIENDA_CLINT "assets/tiendas/clint.jpeg"
#define RUTA_TIENDA_ROBIN "assets/tiendas/robin.jpg"
#define RUTA_TIENDA_MARNIE "assets/tiendas/marnie.jpg"
#define RUTAS_FONDOS_TIENDAS {RUTA_TIENDA_PIERRE, RUTA_TIENDA_CLINT, RUTA_TIENDA_ROBIN,RUTA_TIENDA_MARNIE}
#define RUTA_MUSICA_GRANJA "assets/sonidos/musica_granja.ogg"
#define RUTA_MUSICA_CAVERNA "assets/sonidos/musica_caverna.ogg"
#define RUTA_MUSICA_PUEBLO "assets/sonidos/musica_pueblo.mp3"
#define RUTA_SONIDO_PASO "assets/sonidos/paso.wav"

// rutas para los enemigos
//#define "assets/enemigos/assets/enemigos/"
#define RUTA_ESQUELETO_QUIETO "assets/enemigos/esqueleto/enemies-skeleton1_idle.png"
#define RUTA_ESQUELETO_CAMINANDO "assets/enemigos/esqueleto/enemies-skeleton1_movement.png"
#define RUTA_ESQUELETO_ATACA "assets/enemigos/esqueleto/enemies-skeleton1_attack.png"
#define RUTA_ESQUELETO_DANIADO "assets/enemigos/esqueleto/enemies-skeleton1_take_damage.png"
#define RUTA_ESQUELETO_MUERTO "assets/enemigos/esqueleto/enemies-skeleton1_death.png"
#define RUTA_ORCO_QUIETO "assets/enemigos/orco/Orc_Idle.png"
#define RUTA_ORCO_CAMINANDO "assets/enemigos/orco/Orc_Walk.png"
#define RUTA_ORCO_ATACA "assets/enemigos/orco/Orc_Attack01.png"
#define RUTA_ORCO_DANIADO "assets/enemigos/orco/Orc_Hurt.png"
#define RUTA_ORCO_MUERTO "assets/enemigos/orco/Orc_Death.png"
#define RUTA_VAMPIRO_QUIETO "assets/enemigos/vampiro/enemies-vampire_idle.png"
#define RUTA_VAMPIRO_CAMINANDO "assets/enemigos/vampiro/enemies-vampire_movement.png"
#define RUTA_VAMPIRO_ATACA "assets/enemigos/vampiro/enemies-vampire_attack.png"
#define RUTA_VAMPIRO_DANIADO "assets/enemigos/vampiro/enemies-vampire_take_damage.png"
#define RUTA_VAMPIRO_MUERTO "assets/enemigos/vampiro/enemies-vampire_death.png"

#define CAVERNA_ENEMIGO_DISTANCIA_PASO 1
#define CAVERNA_ENEMIGO_VUELTAS_CAMINANDO 30
#define CAVERNA_ENEMIGO_DISTANCIA_ATAQUE 1

// Sprites: suelo (columna y fila en tiles del tileset)
#define SUELO_DEFECTO_COLUMNA 4
#define SUELO_DEFECTO_FILA 9
#define SUELO_BORDE_CAVERNA_COLUMNA 8
#define SUELO_BORDE_CAVERNA_FILA 7
#define SUELO_BORDE_COLUMNA 1
#define SUELO_BORDE_FILA 9
#define SUELO_TIERRA_COLUMNA 1
#define SUELO_TIERRA_FILA 4
#define SUELO_ARADO_COLUMNA 4
#define SUELO_ARADO_FILA 4
#define SUELO_PISO_CAVERNA_COLUMNA 6
#define SUELO_PISO_CAVERNA_FILA 1
#define SUELO_CAVERNA_DECORACION_1_COLUMNA 7
#define SUELO_CAVERNA_DECORACION_1_FILA 0
#define SUELO_CAVERNA_DECORACION_2_COLUMNA 9
#define SUELO_CAVERNA_DECORACION_2_FILA 2
#define SUELO_PARED_COLUMNA 2
#define SUELO_PARED_FILA 0

// Sprites: recortes del mapa (px)
#define SPRITE_PUERTA_X 514
#define SPRITE_PUERTA_Y 370
#define SPRITE_PUERTA_ANCHO 30
#define SPRITE_PUERTA_ALTO 36
#define SPRITE_PISO_PUEBLO_X 0
#define SPRITE_PISO_PUEBLO_Y 368
#define SPRITE_FLORES_X 160
#define SPRITE_FLORES_Y 276
#define SPRITE_PASTO_OSCURO_X 16
#define SPRITE_PASTO_OSCURO_Y 144

// Sprites: minerales (px)
#define SPRITE_ORCO_CENTRO_X 55
#define SPRITE_MINERAL_CELDA 32
#define SPRITE_MINERAL_ANCHO 32
#define SPRITE_MINERAL_ALTO 28
#define SPRITE_MINERAL_ETAPA_ENTERO 0
#define SPRITE_MINERAL_ETAPA_GOLPEADO 1
#define SPRITE_MINERAL_ETAPA_CASI_ROTO 2

// Sprites: granja (px)
#define SPRITE_MODELOS_CASAS                                                   \
  {                                                                            \
    {144, 0, 80, 104}, { 0, 0, 80, 96 }                                        \
  }
#define SPRITE_VACA_LADO 32
#define SPRITE_GALLINA_LADO 16
#define SPRITE_CULTIVO_LADO 16
#define SPRITE_CULTIVO_FILAS_POR_TIPO 2
#define SPRITE_CULTIVO_FILA_PLANTA 1

// Sprites: pueblo (px)
#define SPRITE_PUESTO_PIERRE                                                   \
  { 240, 176, 112, 144 }
#define SPRITE_PUESTO_CLINT                                                    \
  { 80, 320, 144, 128 }
#define SPRITE_PUESTO_ROBIN                                                    \
  { 192, 640, 192, 160 }
#define SPRITE_PUESTO_MARNIE                                                   \
  { 256, 0, 144, 176 }
#define SPRITE_MODELOS_PUESTOS                                                 \
  {                                                                            \
    SPRITE_PUESTO_PIERRE, SPRITE_PUESTO_CLINT, SPRITE_PUESTO_ROBIN,            \
        SPRITE_PUESTO_MARNIE                                                   \
  }
#define SPRITE_NPC_PIERRE                                                      \
  { RUTA_NPC_PIERRE, 32, 32 }
#define SPRITE_NPC_CLINT                                                       \
  { RUTA_NPC_CLINT, 32, 32 }
#define SPRITE_NPC_ROBIN                                                       \
  { RUTA_NPC_ROBIN, 64, 48 }
#define SPRITE_NPC_MARNIE                                                      \
  { RUTA_NPC_MARNIE, 64, 48 }
#define SPRITE_MODELOS_NPCS                                                    \
  { SPRITE_NPC_PIERRE, SPRITE_NPC_CLINT, SPRITE_NPC_ROBIN, SPRITE_NPC_MARNIE }

// Sprites: personaje (px)
#define SPRITE_PERSONAJE_ANCHO 16
#define SPRITE_PERSONAJE_ALTO 32
#define SPRITE_PERSONAJE_PASOS                                                 \
  { 0, 1, 0, 2 }
#define SPRITE_PERSONAJE_FILAS_PICAR                                           \
  { 11, 8, 6 }
#define SPRITE_BRAZOS_X 96
#define SPRITE_PANTALONES_POR_FILA 10
#define SPRITE_PANTALONES_ANCHO_BLOQUE 192
#define SPRITE_PANTALONES_ALTO_BLOQUE 688
#define SPRITE_REMERAS_POR_FILA 16
#define SPRITE_REMERA_LADO 8
#define SPRITE_REMERA_ALTO_BLOQUE 32
#define SPRITE_REMERA_FILA_ABAJO 0
#define SPRITE_REMERA_FILA_DERECHA 8
#define SPRITE_REMERA_FILA_IZQUIERDA 16
#define SPRITE_REMERA_FILA_ARRIBA 24
#define SPRITE_REMERA_X 4
#define SPRITE_REMERA_Y 15
#define SPRITE_PELOS_POR_FILA 16
#define SPRITE_PELO_ALTO_BLOQUE 96
#define SPRITE_SOMBREROS_POR_FILA 12
#define SPRITE_SOMBRERO_LADO 20
#define SPRITE_SOMBRERO_ALTO_BLOQUE 80
#define SPRITE_SOMBRERO_FILA_ABAJO 0
#define SPRITE_SOMBRERO_FILA_DERECHA 20
#define SPRITE_SOMBRERO_FILA_IZQUIERDA 40
#define SPRITE_SOMBRERO_FILA_ARRIBA 60
#define SPRITE_SOMBRERO_X (-2)
#define SPRITE_SOMBRERO_Y (-4)
#define SPRITE_MANO_DERECHA_X 9
#define SPRITE_MANO_IZQUIERDA_X 7
#define SPRITE_MANO_Y 16
#define ICONO_PIXELES_POR_TILE 24

// Sprites: íconos del inventario (px)
#define ICONO_MINERAL_X 100
#define ICONO_MINERAL_Y 17
#define ICONO_MINERAL_LADO 10
#define ICONO_MINERAL_CELDA 32
#define ICONO_MINERAL_FILA_HIERRO 0
#define ICONO_MINERAL_FILA_CARBON 1
#define ICONO_MINERAL_FILA_LAPISLAZULI 2
#define ICONO_MINERAL_FILA_ORO 3
#define ICONO_CULTIVO_LADO 16
#define ICONO_SEMILLA_COLUMNA 7
#define ICONO_COSECHA_COLUMNA 8
#define ICONO_CULTIVO_FILA_FRUTILLA 1
#define ICONO_CULTIVO_FILA_CEBOLLA 3
#define ICONO_CULTIVO_FILA_PAPA 5
#define ICONO_CULTIVO_FILA_CALABAZA 7
#define SPRITE_ESTRELLA_BORDE                                                  \
  {                                                                            \
    {-1, 2, 10, 4}, { 2, -1, 4, 10 }                                           \
  }
#define SPRITE_ESTRELLA_RELLENO                                                \
  {                                                                            \
    {0, 3, 8, 2}, {3, 0, 2, 8}, { 2, 2, 4, 4 }                                 \
  }

// Colores
#define COLOR_ALFA_OPACO 255
#define COLOR_SOMBRA_MARGEN 150
#define COLOR_SIN_TINTE 255
#define COLOR_TEXTO                                                            \
  { 255, 255, 255, COLOR_ALFA_OPACO }
#define COLOR_BOTON_FONDO                                                      \
  { 30, 30, 30, COLOR_ALFA_OPACO }
#define COLOR_BOTON_BORDE                                                      \
  { 230, 230, 230, COLOR_ALFA_OPACO }
#define COLOR_RAYITA_ENCENDIDA                                                 \
  { 230, 190, 190, COLOR_ALFA_OPACO }
#define COLOR_RAYITA_APAGADA                                                   \
  { 80, 80, 80, COLOR_ALFA_OPACO }
#define COLOR_NOCHE                                                            \
  { 10, 10, 40, COLOR_ALFA_OPACO }
#define COLOR_CAJA_REGALO                                                      \
  { 40, 30, 20, 240 }
#define COLOR_TIENDA_OSCURECER                                                 \
  { 0, 0, 0, 200 }
#define COLOR_CASILLERO                                                        \
  { 60, 40, 30, 230 }
#define COLOR_CASILLERO_SELECCIONADO                                           \
  { 255, 200, 40, COLOR_ALFA_OPACO }
#define COLOR_CASILLERO_BORDE                                                  \
  { 140, 100, 60, COLOR_ALFA_OPACO }
#define COLOR_ESTRELLA_BORDE                                                   \
  { 0, 0, 0, COLOR_ALFA_OPACO }
#define COLOR_CALIDAD_BUENA                                                    \
  { 205, 127, 50, COLOR_ALFA_OPACO }
#define COLOR_CALIDAD_EXCELENTE                                                \
  { 200, 200, 215, COLOR_ALFA_OPACO }
#define COLOR_CALIDAD_INCREIBLE                                                \
  { 240, 200, 40, COLOR_ALFA_OPACO }
#define COLOR_CALIDAD_PERFECTA                                                 \
  { 170, 90, 220, COLOR_ALFA_OPACO }
#define COLOR_MUNDO_FONDO                                                      \
  { 18, 22, 18, COLOR_ALFA_OPACO }
#define COLOR_MUNDO_DIFUMINADO                                                 \
  { 54, 124, 66, COLOR_ALFA_OPACO }
#define COLOR_BARRA_VIDA                                                       \
  { 240, 200, 40, COLOR_ALFA_OPACO }
#define COLOR_BARRA_ENERGIA                                                    \
  { 70, 190, 70, COLOR_ALFA_OPACO }
#define COLOR_BARRA_BORDE                                                      \
  { 0, 0, 0, COLOR_ALFA_OPACO }
#define COLOR_BARRA_FONDO                                                      \
  { 70, 70, 70, COLOR_ALFA_OPACO }
#define COLOR_FONDO_JUEGO                                                      \
  { 0, 0, 0, COLOR_ALFA_OPACO }

// Textos visibles
#define TEXTO_JUEGO_MUSICA "Música"
#define TEXTO_JUEGO_MENOS "-"
#define TEXTO_JUEGO_MAS "+"
#define TEXTO_JUEGO_BOTON_CODIGO "Código Multiplayer"
#define TEXTO_JUEGO_CODIGO "Código: "
#define TEXTO_JUEGO_COPIADO "  (copiado)"
#define TEXTO_JUEGO_DIA "Día "
#define TEXTO_JUEGO_SEPARADOR_DIA " "
#define TEXTO_JUEGO_SEPARADOR_HORA ":"
#define TEXTO_JUEGO_CERO "0"
#define TEXTO_JUEGO_TIEMPO_INICIAL TEXTO_JUEGO_DIA "1 06:00"
#define TEXTO_JUEGO_MONEDAS "Monedas: "
#define TEXTO_JUEGO_MONEDAS_INICIAL TEXTO_JUEGO_MONEDAS "0"
#define TEXTO_JUEGO_REGALO "¡Te ofrecen un regalo!"
#define TEXTO_JUEGO_ACEPTAR "Aceptar"
#define TEXTO_JUEGO_RECHAZAR "Rechazar"
#define TEXTO_JUEGO_TIENDA_PIERRE "Tienda de Pierre"
#define TEXTO_JUEGO_TIENDA_CLINT "Herrería de Clint"
#define TEXTO_JUEGO_TIENDA_ROBIN "Carpintería de Robin"
#define TEXTO_JUEGO_TIENDA_MARNIE "Rancho de Marnie"
#define TITULOS_TIENDAS                                                        \
  {                                                                            \
    TEXTO_JUEGO_TIENDA_PIERRE, TEXTO_JUEGO_TIENDA_CLINT,                       \
        TEXTO_JUEGO_TIENDA_ROBIN, TEXTO_JUEGO_TIENDA_MARNIE                    \
  }
#define TEXTO_JUEGO_COMPRAR "Comprar"
#define TEXTO_JUEGO_VENDER "Vender"
#define TEXTO_JUEGO_HABLAR "Hablar"
#define TEXTO_JUEGO_SALIR "Salir"
#define TEXTOS_BOTONES_TIENDA                                                  \
  {                                                                            \
    TEXTO_JUEGO_COMPRAR, TEXTO_JUEGO_VENDER, TEXTO_JUEGO_HABLAR,               \
        TEXTO_JUEGO_SALIR                                                      \
  }
#define TEXTO_JUEGO_USO "Uso: "
#define TEXTO_JUEGO_ARGUMENTOS " <host> <puerto>"
#define TEXTO_JUEGO_TITULO_VENTANA "Stardew Valley - Partida "
#define TEXTO_JUEGO_CONEXION_PERDIDA "Se perdió la conexión con el servidor."

// Audio
#define AUDIO_TAMANIO_BUFFER 1024
#define AUDIO_INCREMENTO_VOLUMEN 16
#define AUDIO_VOLUMEN_INICIAL (MIX_MAX_VOLUME / 2)
#define AUDIO_REPETIR_SIEMPRE (-1)
#define AUDIO_CANAL_LIBRE (-1)
#define AUDIO_SIN_REPETIR 0
#define AUDIO_MUSICA_GRANJA 0
#define AUDIO_MUSICA_CAVERNA 1
#define AUDIO_MUSICA_PUEBLO 2
#define AUDIO_CANTIDAD_MUSICAS 3

#define REGALO_DISTANCIA 1

#endif // CONSTANTES_SDL_H_
