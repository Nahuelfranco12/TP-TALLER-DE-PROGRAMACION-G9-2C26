#ifndef CONSTANTES_H
#define CONSTANTES_H

#define BASE_COORDENADAS 1

// lo agrego para hacer responsive toda la parte de QT
#define ANCHO_DISENIO 1280
#define ALTO_DISENIO 720

// estos los uso en el customizar personaje
#define ANCHO_GORRO 20
#define ALTO_GORRO 20
#define ANCHO_PELO 16
#define ALTO_PELO 32
#define ANCHO_REMERA 8
#define ALTO_REMERA 8
#define ANCHO_PANTALON 16
#define ALTO_PANTALON 32

// estas son para escalar los sprites y que se vean bien
#define ESCALA_PREVISUALIZACION 6

// esto es para el recorte y que ocupen bien los tamaños
#define ALTO_RECORTE_PELO 16
#define ALTO_RECORTE_PANTALON 16
#define OFFSET_Y_PANTALON 16

#define DIRECCION_ANTERIOR -1
#define DIRECCION_SIGUIENTE 1

// Rutas de las ropas para los outfits
#define TIPOS_PELO ":/ropas/assets/ropas/StardewValley_Character_Hairstyles.png"
#define TIPOS_GORRO ":/ropas/assets/ropas/StardewValley_Character_Hats.png"
#define TIPOS_PANTALON ":/ropas/assets/ropas/StardewValley_Character_Pants.png"
#define TIPOS_REMERA ":/ropas/assets/ropas/StardewValley_Character_Shirts.png"

#define TIPOS_CUERPO                                                           \
  ":/ropas/assets/ropas/StardewValley_Character_Farmer Base.png"

#define ANCHO_CUERPO 16
#define ALTO_CUERPO 32
#define X_BRAZOS 96
#define ANCHO_LIENZO 20
#define ALTO_LIENZO 36
#define X_CUERPO_EN_LIENZO 2
#define Y_CUERPO_EN_LIENZO 4
#define X_REMERA_EN_CUERPO 4
#define Y_REMERA_EN_CUERPO 15
#define ESCALA_TARJETA 4

// LOS USO EN CONTROLADOR NUEVA PARTIDA
#define ELEGIR_MAPA "Elegir Mapa"

// estos son los otros textos para multplayer y eso
#define TEXTO_MULTIPLAYER "Multiplayer"
#define TEXTO_SINGLEPLAYER "Singleplayer"
#define TEXTO_SELECCIONAR "Seleccionar"

#endif // CONSTANTES_H
