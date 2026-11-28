#ifndef CONSTANTES_SDL_H_
#define CONSTANTES_SDL_H_

// ACLARACION: las constantes estan centralizadas en este archivo, y agrupadas por tema
// indico con un comentario que hace ese grupo y donde estan de la forma:
// tema -> archivo1.cpp, archivoN.cpp

// Ventana, argumentos y loop -> main.cpp
#define CANTIDAD_ARGUMENTOS 3
#define ARGUMENTO_HOST 1
#define ARGUMENTO_PUERTO 2
#define VENTANA_ANCHO 640
#define VENTANA_ALTO 480
#define RENDERER_DRIVER_POR_DEFECTO (-1)
#define LOOP_PERIODO_MS 16

// Escalas y tamaños -> alrededores.cpp, animacion.cpp, caverna.h, caverna.cpp,
// granja.h, granja.cpp, main.cpp, mapa.cpp, mapa_mundo.cpp, personaje.cpp,
// pueblo.h, pueblo.cpp
#define PIXELES_POR_TILE 16
#define ESCALA_SPRITES 4
#define TAMANIO_TILE (PIXELES_POR_TILE * ESCALA_SPRITES)

#define CABANA_ANCHO 30
#define CABANA_ALTO 15

// Mapa: márgenes y decoración -> mapa.cpp
#define MAPA_MARGEN 30
#define MAPA_DADO_DECORACION_MAXIMO 9

// Semillas de los mapas -> main.cpp
#define SEMILLA_GRANJA 42
#define SEMILLA_CAVERNA 7
#define SEMILLA_PUEBLO 42
#define SEMILLA_ALREDEDORES 42

// Letras de la grilla del mapa -> mapa.cpp
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
#define LETRA_VACIO ' '
#define LETRA_PISO_MADERA 'm'
#define LETRA_PUERTA_CARTEL 'g'
#define LETRA_PUERTA_ESCALERA 'h'

// Bosque alrededor de la granja (en tiles) -> alrededores.cpp
#define BOSQUE_ZONA 30
#define BOSQUE_SEPARACION 3
#define BOSQUE_DESPLAZAMIENTO_MAXIMO (BOSQUE_SEPARACION - 2)
#define BOSQUE_PORCENTAJE 50
#define BOSQUE_DADO_MAXIMO 99
#define BOSQUE_DISTANCIA_GRANJA 1
#define BOSQUE_MARGEN 4
#define BOSQUE_SOMBRA 200

// Mapa general, tecla M (en tiles salvo que diga px) -> mapa_mundo.cpp
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

// Granja: casa, animales, productos y cultivos -> granja.cpp
#define ANIMAL_CUADROS_ANIMACION 4
#define ANIMAL_VUELTAS_POR_CUADRO 20 // 20 x 16 ms = 0,3 s
#define PRODUCTO_VUELTAS_POR_SALTO 20
#define PRODUCTO_SALTO 1
#define CULTIVO_ULTIMA_ETAPA                                                   \
  { 5, 5, 6, 5 }
#define CULTIVO_CRECIMIENTO_MAXIMO 3

// Caverna: minerales y enemigos -> animacion_enemigos.cpp, caverna.cpp
#define CAVERNA_GOLPES_GOLPEADO 2
#define CAVERNA_GOLPES_CASI_ROTO 1
#define CAVERNA_ENEMIGO_DISTANCIA_PASO 1
#define CAVERNA_ENEMIGO_VUELTAS_CAMINANDO 30
#define CAVERNA_ENEMIGO_DISTANCIA_ATAQUE 1
#define VUELTAS_POR_CUADRO_ENEMIGO 6

// Pueblo y tiendas (el índice es el mismo para puesto, NPC, título y fondo) ->
// pueblo.cpp
#define TIENDA_PIERRE 0
#define TIENDA_CLINT 1
#define TIENDA_ROBIN 2
#define TIENDA_MARNIE 3
#define TIENDA_CERRADA (-1)

#define PUEBLO_MODELO_CENTRO 4

#define PUEBLO_NPCS                                                            \
  {                                                                            \
    {7, 28, TIENDA_PIERRE}, {22, 27, TIENDA_CLINT}, {10, 11, TIENDA_ROBIN}, { \
      21, 12, TIENDA_MARNIE                                                    \
    }                                                                          \
  }
#define NPC_CUADROS_ANIMACION 4
#define NPC_VUELTAS_POR_CUADRO 12
#define TIENDA_TAMANIO_LETRA 20
#define TIENDA_CANTIDAD_BOTONES 1
#define TIENDA_ALTO_BOTON 36
#define TIENDA_SEPARACION_BOTONES 12
#define TIENDA_RELLENO_BOTON 12
#define TIENDA_LADO_PERSONAJES 48
#define TIENDA_MARGEN_ANCHO 40
#define TIENDA_MARGEN_ALTO 140
#define TIENDA_MARGEN_TITULO 10
#define TIENDA_MARGEN_BOTONES 10

// Centro comunitario
#define SET_CULTIVOS 0
#define SET_METALES 1
#define SET_ANIMALES 2
#define SET_PELEA 3
#define SET_DINERO 4
#define SET_CANTIDAD 5
#define SET_CERRADO (-1)

// Figurines dentro del centro
#define CENTRO_SETS                                                           \
{                                                                             \
  {4, 3, SET_CULTIVOS}, {7, 3, SET_METALES}, {10, 3, SET_ANIMALES},           \
  {13, 3, SET_PELEA}, {16, 3, SET_DINERO}                                     \
}

// Titulo de un set
#define CENTRO_TITULO_DIVISOR 16
#define CENTRO_CONTENIDO_DIVISOR 8

// Caja de un set
#define CENTRO_TAMANIO_LETRA 40
#define CENTRO_TAMANIO_LETRA_CHICA 30
#define CENTRO_LADO_FIGURIN_CAJA 64
#define CENTRO_MARGEN_ANCHO 40
#define CENTRO_MARGEN_ALTO 100
#define CENTRO_SEPARACION_LINEAS 40
#define CENTRO_MARGEN_BOTONES 10
#define CENTRO_MONEDAS_SET 10000

// Personaje: ropa inicial, caminar y picar -> personaje.cpp
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
#define PERSONAJE_FACTOR_LENTO 2
#define PERSONAJE_VIDA_LENTO (BARRA_VALOR_MAXIMO * 20 / 100)
#define PERSONAJE_DURACION_MORIR 40
#define PERSONAJE_ANGULO_CAIDA 90.0
#define PERSONAJE_DURACION_ROJO 20
#define PERSONAJE_ROJO_VERDE_AZUL 70

// Ropa elegida en el lobby -> índice en las hojas de SDL -> main.cpp
#define ROPA_SOMBREROS_SDL                                                     \
  { 45, 4, 40, 61, 121, 99 }
#define ROPA_PELOS_SDL                                                         \
  { 9, 10, 33, 69, 21, 27 }
#define ROPA_PANTALONES_SDL                                                    \
  { 0, 2, 5, 6 }
#define ROPA_REMERAS_SDL                                                       \
  { 9, 19, 36, 27, 104 }

// Barras de vida y energía (px) -> personaje.cpp
#define BARRA_VALOR_MAXIMO 100.0
#define BARRA_ANCHO 48
#define BARRA_ALTO 6
#define BARRA_SEPARACION 2
#define BARRA_BORDE 1

// Día y noche -> interfaz.h, interfaz.cpp
#define DIA_HORA_INICIO 6
#define MINUTOS_POR_HORA 60
#define NOCHE_HORA_ATARDECER 18
#define NOCHE_HORA_OSCURA 22
#define NOCHE_OSCURIDAD_MAXIMA 170
#define RELOJ_MINIMO_DOS_CIFRAS 10

// HUD (px) -> interfaz.cpp
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
#define HUD_FILA_PASOS_Y (HUD_MARGEN + HUD_ALTO_BOTON + HUD_SEPARACION_CAJAS)
#define HUD_RAYITA_PASOS_Y (HUD_RAYITA_Y + HUD_ALTO_BOTON + HUD_SEPARACION_CAJAS)
#define TEXTO_JUEGO_PASOS "Pasos"

// Teclas -> main.cpp
#define TECLA_SALIR SDLK_ESCAPE
#define TECLA_MAPA SDLK_m
#define TECLA_PRIMER_CASILLERO SDLK_1
#define TECLA_ULTIMO_CASILLERO SDLK_9
#define TECLA_ACEPTAR_REGALO SDLK_y
#define TECLA_RECHAZAR_REGALO SDLK_n
#define TECLA_CHEAT_RIEGO SDLK_c
#define TECLA_CHEAT_CRECIMIENTO SDLK_COMMA
#define TECLA_CHEAT_DIA SDLK_0
#define TECLA_ACCION SDLK_SPACE
#define TECLA_ARRIBA SDLK_UP
#define TECLA_ABAJO SDLK_DOWN
#define TECLA_IZQUIERDA SDLK_LEFT
#define TECLA_DERECHA SDLK_RIGHT

#define BOTONES_DESDE_ABAJO 120;

// Regalos -> interfaz.cpp, main.cpp
#define REGALO_ANCHO 280
#define REGALO_ALTO 140
#define REGALO_MARGEN_TITULO 10
#define REGALO_ICONO_Y 40
#define REGALO_MARGEN_BOTONES 20
#define REGALO_BOTONES_DESDE_ABAJO 44
#define REGALO_ANCHO_BOTON 110
#define REGALO_DISTANCIA 1

// Inventario (px) -> interfaz.cpp, inventario.cpp
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
#define DIGITOS_DECIMALES 10

// Muebles: cofre y cama -> granja.cpp, inventario.cpp, ventana_cofre.cpp
#define SPRITE_COFRE_X 8
#define SPRITE_COFRE_CERRADO_Y 0
#define SPRITE_COFRE_ABIERTO_Y 16
#define SPRITE_COFRE_LADO 16
#define COFRE_SEPARACION 8

#define COFRE_COLUMNAS 10
#define COFRE_FILAS 3
#define COFRE_CASILLEROS (COFRE_COLUMNAS * COFRE_FILAS)

#define SPRITE_CAMA {87, 8, 18, 34}

// Decoraciones {x, y, ancho, alto}

#define SPRITE_SILLA {2, 125, 11, 18}
#define SPRITE_MESA {68, 120, 24, 23}
#define SPRITE_MESITA {96, 120, 16, 18}
#define SPRITE_CHIMENEA {115, 8, 26, 40}
#define SPRITE_JARRON {17, 17, 15, 15}
#define SPRITE_CAJA {0, 0, 16, 21}
#define SPRITE_BARRIL {0, 0, 13, 16}
#define SPRITE_MACETA {0, 0, 8, 18}
#define SPRITE_GIRASOL {0, 0, 12, 19}
#define SPRITE_ALJIBE {0, 0, 20, 25}

// Rutas de assets -> alrededores.cpp, audio.cpp, caverna.cpp, granja.cpp,
// interfaz.cpp, inventario.cpp, mapa.cpp, mapa_mundo.cpp, personaje.cpp,
// pueblo.cpp
#define RUTA_FUENTE_JUEGO "assets/fuentes/DejaVuSans-Bold.ttf"
#define RUTA_ARBOL "assets/mapas/tree1.png"
#define RUTA_PINO "assets/mapas/tree1_2.png"
#define RUTA_TILESET_GRANJA "assets/mapas/ground_01_16x16.png"
#define RUTA_TILESET_CAVERNA "assets/mapas/Dungeon_Tileset.png"
#define RUTA_TILESET_PUEBLO "assets/mapas/PelicanTown_Buildings.png"
#define RUTA_TILESET_CABANA "assets/mapas/Tilesets_Farmhouse.png"
#define RUTA_MUEBLES "assets/mapas/Tilesets_Furniture.png"
#define RUTA_OFRENDAS_CENTRO_COMUNITARIO "assets/mapas/ComunityCenter_Offerings.png"
#define RUTA_EDIFICIO_CENTRO_COMUNITARIO "assets/mapas/centro_com.png"
#define RUTA_COFRE "assets/muebles/chest.png"
#define RUTA_INTERIOR "assets/muebles/Interior.png"
#define RUTA_CAJA "assets/muebles/spr_deco_crate_01.png"
#define RUTA_BARRIL "assets/muebles/spr_deco_barrel_closed.png"
#define RUTA_MACETA "assets/muebles/spr_deco_flowers_house_01.png"
#define RUTA_GIRASOL "assets/muebles/spr_deco_flowers_house_02.png"
#define RUTA_ALJIBE "assets/muebles/spr_deco_well.png"
#define RUTA_OFRENDAS_CENTRO_COMUNITARIO                                       \
  "assets/mapas/ComunityCenter_Offerings.png"
#define RUTA_MINERALES "assets/caverna/ore.png"
#define RUTA_CASAS "assets/edificios/House.png"
#define RUTA_EDIFICIOS_PUEBLO "assets/edificios/PelicanTown_Buildings.png"
#define RUTA_VACA "assets/animales/Female Cow Brown.png"
#define RUTA_GALLINA "assets/animales/Chicken Blonde  Green.png"
#define RUTA_CULTIVOS "assets/cultivos/Spring Crops.png"
#define RUTA_EXCLAMACION "assets/simbolos/expression_alerted.png"
#define RUTA_ICONOS_MINERALES "assets/inventario/ore.png"
#define RUTA_ICONOS_CULTIVOS "assets/inventario/Spring Crops.png"
#define RUTA_HUEVO "assets/inventario/egg.png"
#define RUTA_LECHE "assets/inventario/milk.png"
#define RUTA_ESPADA "assets/inventario/sword.png"
#define RUTA_PICO "assets/inventario/pickaxe.png"
#define RUTA_PALA "assets/inventario/shovel.png"
#define RUTA_REGADERA "assets/inventario/watering_can.png"
#define RUTA_PERSONAJE_CUERPO                                                  \
  "assets/personaje/StardewValley_Character_Farmer Base.png"
#define RUTA_PERSONAJE_PANTALONES                                              \
  "assets/personaje/StardewValley_Character_Pants.png"
#define RUTA_PERSONAJE_REMERAS                                                 \
  "assets/personaje/StardewValley_Character_Shirts.png"
#define RUTA_PERSONAJE_PELOS                                                   \
  "assets/personaje/StardewValley_Character_Hairstyles.png"
#define RUTA_PERSONAJE_SOMBREROS                                               \
  "assets/personaje/StardewValley_Character_Hats.png"
#define RUTA_NPC_PIERRE "assets/npcs/pierre.png"
#define RUTA_NPC_CLINT "assets/npcs/clint.png"
#define RUTA_NPC_ROBIN "assets/npcs/robin.png"
#define RUTA_NPC_MARNIE "assets/npcs/marnie.png"
#define RUTA_TIENDA_PIERRE "assets/tiendas/pierre.png"
#define RUTA_TIENDA_CLINT "assets/tiendas/clint.png"
#define RUTA_TIENDA_ROBIN "assets/tiendas/robin.png"
#define RUTA_TIENDA_MARNIE "assets/tiendas/marnie.png"
#define RUTAS_FONDOS_TIENDAS                                                   \
  {                                                                            \
    RUTA_TIENDA_PIERRE, RUTA_TIENDA_CLINT, RUTA_TIENDA_ROBIN,                  \
        RUTA_TIENDA_MARNIE                                                     \
  }
#define RUTA_MUSICA_GRANJA "assets/sonidos/musica_granja.ogg"
#define RUTA_MUSICA_CAVERNA "assets/sonidos/musica_caverna.ogg"
#define RUTA_MUSICA_PUEBLO "assets/sonidos/musica_pueblo.mp3"
#define RUTA_SONIDO_PASO "assets/sonidos/paso.wav"
#define RUTA_ESQUELETO_QUIETO                                                  \
  "assets/enemigos/esqueleto/enemies-skeleton1_idle.png"
#define RUTA_ESQUELETO_CAMINANDO                                               \
  "assets/enemigos/esqueleto/enemies-skeleton1_movement.png"
#define RUTA_ESQUELETO_ATACA                                                   \
  "assets/enemigos/esqueleto/enemies-skeleton1_attack.png"
#define RUTA_ESQUELETO_DANIADO                                                 \
  "assets/enemigos/esqueleto/enemies-skeleton1_take_damage.png"
#define RUTA_ESQUELETO_MUERTO                                                  \
  "assets/enemigos/esqueleto/enemies-skeleton1_death.png"
#define RUTA_ORCO_QUIETO "assets/enemigos/orco/Orc_Idle.png"
#define RUTA_ORCO_CAMINANDO "assets/enemigos/orco/Orc_Walk.png"
#define RUTA_ORCO_ATACA "assets/enemigos/orco/Orc_Attack01.png"
#define RUTA_ORCO_DANIADO "assets/enemigos/orco/Orc_Hurt.png"
#define RUTA_ORCO_MUERTO "assets/enemigos/orco/Orc_Death.png"
#define RUTA_VAMPIRO_QUIETO "assets/enemigos/vampiro/enemies-vampire_idle.png"
#define RUTA_VAMPIRO_CAMINANDO                                                 \
  "assets/enemigos/vampiro/enemies-vampire_movement.png"
#define RUTA_VAMPIRO_ATACA "assets/enemigos/vampiro/enemies-vampire_attack.png"
#define RUTA_VAMPIRO_DANIADO                                                   \
  "assets/enemigos/vampiro/enemies-vampire_take_damage.png"
#define RUTA_VAMPIRO_MUERTO "assets/enemigos/vampiro/enemies-vampire_death.png"
#define RUTA_CALAVERA_AZUL_QUIETA "assets/enemigos/enemies-skull_blue_idle.png"
#define RUTA_CALAVERA_VERDE_QUIETA                                             \
  "assets/enemigos/enemies-skull_green_idle.png"
#define RUTA_PINCHES "assets/enemigos/enemies-peaks_1.png"
#define RUTA_LANZALLAMAS1 "assets/enemigos/enemies-flamethrower_1_1.png"
#define RUTA_LANZALLAMAS2 "assets/enemigos/enemies-flamethrower_2_1.png"

// Suelo: columna y fila en tiles del tileset -> granja.cpp, mapa.cpp
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
#define SPRITE_PISO_MADERA_X 32
#define SPRITE_PISO_MADERA_Y 128

// Sprites (px) -> caverna.cpp, granja.cpp, inventario.cpp, mapa.cpp,
// mapa_mundo.cpp, personaje.cpp, pueblo.cpp
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
#define SPRITE_ORCO_CENTRO_X 55
#define SPRITE_ESQUELETO_CENTRO_X 14
#define SPRITE_VAMPIRO_CENTRO_X 13
#define SPRITE_VAMPIRO_PIE_CAMINANDO 28
#define SPRITE_MINERAL_CELDA 32
#define SPRITE_MINERAL_ANCHO 32
#define SPRITE_MINERAL_ALTO 28
#define SPRITE_MINERAL_ETAPA_ENTERO 0
#define SPRITE_MINERAL_ETAPA_GOLPEADO 1
#define SPRITE_MINERAL_ETAPA_CASI_ROTO 2
#define SPRITE_ESQUELETO_LADO 32
#define SPRITE_ESQUELETO_PIE 29
#define SPRITE_ORCO_LADO 100
#define SPRITE_ORCO_PIE 57
#define SPRITE_VAMPIRO_LADO 32
#define SPRITE_VAMPIRO_PIE 29
#define SPRITE_CALAVERA_LADO 16
#define SPRITE_CALAVERA_PIE 16
#define SPRITE_TRAMPA_LADO 16
#define SPRITE_TRAMPA_PIE 16
#define RUTA_TILESET_CABANAS "assets/mapas/Tilesets_Cabins.png"
#define SPRITE_CABANA_1 {160, 0, 80, 112}
#define SPRITE_CABANA_2 {160, 112, 80, 112}
#define SPRITE_CABANA_3 {160, 224, 80, 112}
#define SPRITE_CABANA_4 {160, 336, 80, 112}
#define SPRITE_CABANA_5 {160, 448, 80, 112}
#define SPRITE_MODELOS_CASAS {SPRITE_CABANA_1, SPRITE_CABANA_2, SPRITE_CABANA_3, SPRITE_CABANA_4, SPRITE_CABANA_5}
#define SPRITE_VACA_LADO 32
#define SPRITE_GALLINA_LADO 16
#define SPRITE_CULTIVO_LADO 16
#define SPRITE_CULTIVO_FILAS_POR_TIPO 2
#define SPRITE_CULTIVO_FILA_PLANTA 1
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
#define SPRITE_PUERTA_CARTEL {0, 128, 16, 16}
#define SPRITE_PUERTA_ESCALERA {144, 48, 16, 16}

// Sprites: centro comunitario (px)
#define SPRITE_EDIFICIO_CENTRO {17, 181, 190, 123}
#define SPRITE_FONDO_CENTRO {0, 0, 320, 176}
#define SPRITE_FIGURIN_LADO 32
#define SPRITE_SET_CULTIVOS {64, 180, SPRITE_FIGURIN_LADO, SPRITE_FIGURIN_LADO}
#define SPRITE_SET_METALES {0, 212, SPRITE_FIGURIN_LADO, SPRITE_FIGURIN_LADO}
#define SPRITE_SET_ANIMALES {160, 180, SPRITE_FIGURIN_LADO, SPRITE_FIGURIN_LADO}
#define SPRITE_SET_PELEA {64, 212, SPRITE_FIGURIN_LADO, SPRITE_FIGURIN_LADO}
#define SPRITE_SET_DINERO {128, 212, SPRITE_FIGURIN_LADO, SPRITE_FIGURIN_LADO}
#define SPRITE_MODELOS_SETS                                                    \
  {SPRITE_SET_CULTIVOS, SPRITE_SET_METALES, SPRITE_SET_ANIMALES,               \
    SPRITE_SET_PELEA, SPRITE_SET_DINERO                                        \
  }

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

// Íconos del inventario (px) -> granja.cpp, inventario.cpp,
//   personaje.cpp
#define ICONO_PIXELES_POR_TILE 24
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
#define ICONO_COSECHA_PLATA_COLUMNA 9
#define ICONO_COSECHA_ORO_COLUMNA 10
#define ICONO_COSECHA_IRIDIO_COLUMNA 11
#define ICONO_CULTIVO_FILA_FRUTILLA 1
#define ICONO_CULTIVO_FILA_CEBOLLA 3
#define ICONO_CULTIVO_FILA_PAPA 5
#define ICONO_CULTIVO_FILA_CALABAZA 7

// Colores -> animacion.cpp, caverna.cpp, interfaz.cpp,
//   inventario.cpp, main.cpp, mapa.cpp, mapa_mundo.cpp, personaje.cpp,
//   pueblo.cpp
#define COLOR_ALFA_OPACO 255
#define COLOR_SIN_TINTE 255
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
#define COLOR_SOMBRA_MARGEN 150
#define COLOR_TINTE_NEUTRO                                                     \
  { COLOR_SIN_TINTE, COLOR_SIN_TINTE, COLOR_SIN_TINTE, COLOR_ALFA_OPACO }
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
#define COLOR_MUNDO_FONDO                                                      \
  { 18, 22, 18, COLOR_ALFA_OPACO }
#define COLOR_MUNDO_DIFUMINADO                                                 \
  { 54, 124, 66, COLOR_ALFA_OPACO }
#define COLOR_BARRA_VIDA                                                       \
  { 200, 40, 40, COLOR_ALFA_OPACO }
#define COLOR_BARRA_ENERGIA                                                    \
  { 70, 190, 70, COLOR_ALFA_OPACO }
#define COLOR_BARRA_BORDE                                                      \
  { 0, 0, 0, COLOR_ALFA_OPACO }
#define COLOR_BARRA_FONDO                                                      \
  { 70, 70, 70, COLOR_ALFA_OPACO }
#define COLOR_FONDO_JUEGO                                                      \
  { 0, 0, 0, COLOR_ALFA_OPACO }
#define COLOR_TEXTO_CENTRO                                                     \
 { 70, 40, 20, COLOR_ALFA_OPACO }
 #define COLOR_CABANA_OSCURECER                                                     \
 { 0, 0, 0, 170 }

// Textos visibles -> interfaz.cpp, main.cpp, pueblo.cpp
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
#define TEXTOS_BOTONES_TIENDA {TEXTO_JUEGO_SALIR}
#define TEXTO_JUEGO_USO "Uso: "
#define TEXTO_JUEGO_ARGUMENTOS " <host> <puerto>"
#define TEXTO_JUEGO_TITULO_VENTANA "Stardew Valley - Partida "
#define TEXTO_JUEGO_CONEXION_PERDIDA "Se perdió la conexión con el servidor."

#define TEXTO_JUEGO_SET_CULTIVOS "Set de cultivos"
#define TEXTO_JUEGO_SET_METALES "Set de metales"
#define TEXTO_JUEGO_SET_ANIMALES "Set de productos animales"
#define TEXTO_JUEGO_SET_PELEA "Set de pelea"
#define TEXTO_JUEGO_SET_DINERO "Set de dinero"
#define TITULOS_SETS { TEXTO_JUEGO_SET_CULTIVOS, TEXTO_JUEGO_SET_METALES, TEXTO_JUEGO_SET_ANIMALES, TEXTO_JUEGO_SET_PELEA, TEXTO_JUEGO_SET_DINERO}
#define TEXTO_JUEGO_CANJEAR "Canjear"

// Audio -> audio.cpp, interfaz.cpp
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

// Decoraciones del editor (mismos archivos, recortes y tamaños que el editor de Qt)
#define RUTA_NATURALEZA "assets/mapas/water asset.png"
#define RUTA_PIEDRAS_CAMINO "assets/mapas/Road copiar.png"
#define RUTA_OBJETOS_MAPA "assets/mapas/objects_01_16x16.png"
#define RUTA_POZO "assets/caverna/pozo-sig-nivel.png"

// Índice de cada archivo en RUTAS_DECORACIONES
#define DECO_ARCHIVO_ARBOL1 0
#define DECO_ARCHIVO_ARBOL2 1
#define DECO_ARCHIVO_NATURALEZA 2
#define DECO_ARCHIVO_PIEDRAS 3
#define DECO_ARCHIVO_OBJETOS 4
#define DECO_ARCHIVO_CAVERNA 5
#define DECO_ARCHIVO_POZO 6
#define RUTAS_DECORACIONES { RUTA_ARBOL, RUTA_PINO, RUTA_NATURALEZA, RUTA_PIEDRAS_CAMINO, RUTA_OBJETOS_MAPA, RUTA_TILESET_CAVERNA, RUTA_POZO }

// Cuántos tiles ocupa cada una
#define DECO_TILES_NORMAL 1
#define DECO_TILES_ARBOL_ALTO 2
#define DECO_TILES_AGUA 4
#define DECO_TILES_FAROL_ALTO 2
#define DECO_TILES_BANCO_ANCHO 2
#define DECO_TILES_POZO 2

// Recortes (px)
#define SPRITE_DECO_ENTERA { 0, 0, 0, 0 }
#define SPRITE_DECO_ARBUSTO_REDONDO { 112, 160, 16, 16 }
#define SPRITE_DECO_ARBUSTO_GRANDE { 128, 176, 16, 16 }
#define SPRITE_DECO_TRONCO_CAIDO { 144, 96, 16, 16 }
#define SPRITE_DECO_TOCON { 128, 112, 16, 16 }
#define SPRITE_DECO_PIEDRA { 32, 0, 16, 16 }
#define SPRITE_DECO_PIEDRA_GRIS { 160, 144, 16, 16 }
#define SPRITE_DECO_PIEDRA_GRIS_GRANDE { 128, 144, 16, 16 }
#define SPRITE_DECO_AGUA { 0, 80, 64, 64 }
#define SPRITE_DECO_BUZON_ROJO { 19, 91, 11, 20 }
#define SPRITE_DECO_BUZON_AZUL { 35, 91, 11, 20 }
#define SPRITE_DECO_BUZON_GRIS { 3, 91, 11, 20 }
#define SPRITE_DECO_CARTEL_VACIO { 0, 112, 16, 16 }
#define SPRITE_DECO_BARRIL { 128, 48, 16, 16 }
#define SPRITE_DECO_CALAVERA { 112, 112, 16, 16 }
#define SPRITE_DECO_HUESO { 128, 96, 16, 16 }
#define SPRITE_DECO_ESCOMBROS { 144, 64, 16, 16 }
#define SPRITE_DECO_ANTORCHA { 0, 144, 16, 16 }
#define SPRITE_DECO_CANDELABRO { 48, 144, 16, 16 }
#define SPRITE_DECO_ESCUDO { 64, 112, 16, 16 }
#define SPRITE_DECO_POZO { 0, 0, 32, 32 }
#define SPRITE_DECO_FAROL_NARANJA { 51, 82, 11, 28 }
#define SPRITE_DECO_FAROL_AZUL { 64, 82, 16, 28 }
#define SPRITE_DECO_BANCO { 36, 59, 25, 19 }

#endif // CONSTANTES_SDL_H_
