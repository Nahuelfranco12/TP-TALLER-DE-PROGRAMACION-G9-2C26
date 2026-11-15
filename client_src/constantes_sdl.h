#ifndef CONSTANTES_SDL_H_
#define CONSTANTES_SDL_H_

// Ventana y loop

// Mapa: tiles, escala y generación de decoración
#define TAMANIO_TILE_ASSET 16
#define ESCALA_SPRITES 4
#define TAMANIO_TILE (TAMANIO_TILE_ASSET * ESCALA_SPRITES)
#define MAPA_MARGEN 30
#define MAPA_DADO_DECORACION_MAXIMO 9

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

// Caverna: golpes restantes de un mineral
#define CAVERNA_GOLPES_GOLPEADO 2
#define CAVERNA_GOLPES_CASI_ROTO 1

// Rutas de assets
#define RUTA_ASSETS "assets/"
#define RUTA_ARBOL RUTA_ASSETS "mapas/tree1.png"
#define RUTA_PINO RUTA_ASSETS "mapas/tree1_2.png"
#define RUTA_TILESET_GRANJA RUTA_ASSETS "mapas/ground_01_16x16.png"
#define RUTA_TILESET_CAVERNA RUTA_ASSETS "mapas/Dungeon_Tileset.png"
#define RUTA_TILESET_PUEBLO RUTA_ASSETS "mapas/PelicanTown_Buildings.png"
#define RUTA_MUEBLES RUTA_ASSETS "mapas/Tilesets_Furniture.png"
#define RUTA_OFRENDAS_CENTRO_COMUNITARIO \
  RUTA_ASSETS "mapas/ComunityCenter_Offerings.png"
#define RUTA_MINERALES RUTA_ASSETS "caverna/ore.png"
#define RUTA_MUSICA_GRANJA RUTA_ASSETS "sonidos/musica_granja.ogg"
#define RUTA_MUSICA_CAVERNA RUTA_ASSETS "sonidos/musica_caverna.ogg"
#define RUTA_MUSICA_PUEBLO RUTA_ASSETS "sonidos/musica_pueblo.mp3"
#define RUTA_SONIDO_PASO RUTA_ASSETS "sonidos/paso.wav"

// Sprites: recortes en los tilesets (columna y fila en tiles, o píxeles)
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

#define SPRITE_PUERTA_X 514
#define SPRITE_PUERTA_Y 370
#define SPRITE_PUERTA_ANCHO 30
#define SPRITE_PUERTA_ALTO 36
#define SPRITE_PISO_PUEBLO_X 0
#define SPRITE_PISO_PUEBLO_Y 368
#define SPRITE_FLORES_X 160
#define SPRITE_FLORES_Y 276

#define SPRITE_MINERAL_CELDA 32
#define SPRITE_MINERAL_ANCHO 32
#define SPRITE_MINERAL_ALTO 28
#define SPRITE_MINERAL_ETAPA_ENTERO 0
#define SPRITE_MINERAL_ETAPA_GOLPEADO 1
#define SPRITE_MINERAL_ETAPA_CASI_ROTO 2

// Colores
#define COLOR_SOMBRA_MARGEN 150
#define COLOR_SIN_TINTE 255

// HUD: posiciones y tamaños

// Textos visibles

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

#endif  // CONSTANTES_SDL_H_
