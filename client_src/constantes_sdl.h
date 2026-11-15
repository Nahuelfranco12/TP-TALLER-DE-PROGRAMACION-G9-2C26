#ifndef CONSTANTES_SDL_H_
#define CONSTANTES_SDL_H_

// Ventana y loop

// Mapa: tiles y escala
#define TAMANIO_TILE_ASSET 16
#define ESCALA_SPRITES 4
#define TAMANIO_TILE (TAMANIO_TILE_ASSET * ESCALA_SPRITES)

// Bosque alrededor de la granja (medidas en tiles)
#define BOSQUE_ZONA 30
#define BOSQUE_SEPARACION 3
#define BOSQUE_DESPLAZAMIENTO_MAXIMO (BOSQUE_SEPARACION - 2)
#define BOSQUE_PORCENTAJE 50
#define BOSQUE_DADO_MAXIMO 99
#define BOSQUE_DISTANCIA_GRANJA 1
#define BOSQUE_MARGEN 4
#define BOSQUE_SOMBRA 200

// Rutas de assets
#define RUTA_ASSETS "assets/"
#define RUTA_ARBOL RUTA_ASSETS "mapas/tree1.png"
#define RUTA_PINO RUTA_ASSETS "mapas/tree1_2.png"
#define RUTA_MUSICA_GRANJA RUTA_ASSETS "sonidos/musica_granja.ogg"
#define RUTA_MUSICA_CAVERNA RUTA_ASSETS "sonidos/musica_caverna.ogg"
#define RUTA_MUSICA_PUEBLO RUTA_ASSETS "sonidos/musica_pueblo.mp3"
#define RUTA_SONIDO_PASO RUTA_ASSETS "sonidos/paso.wav"

// Sprites: recortes, frames y velocidades de animación

// Colores

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
