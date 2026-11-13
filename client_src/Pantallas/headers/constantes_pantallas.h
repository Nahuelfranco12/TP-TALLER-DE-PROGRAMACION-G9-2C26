#ifndef CONSTANTES_PANTALLAS_H_
#define CONSTANTES_PANTALLAS_H_

#define BASE_COORDENADAS 1

// lo agrego para hacer responsive toda la parte de QT
#define ANCHO_DISENIO 1360
#define ALTO_DISENIO 768

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

#define DIRECCION_ANTERIOR -1
#define DIRECCION_SIGUIENTE 1

// Rutas de las ropas para los outfits
#define TIPOS_PELO ":/ropas/assets/ropas/StardewValley_Character_Hairstyles.png"
#define TIPOS_GORRO ":/ropas/assets/ropas/StardewValley_Character_Hats.png"
#define TIPOS_PANTALON ":/ropas/assets/ropas/StardewValley_Character_Pants.png"
#define TIPOS_REMERA ":/ropas/assets/ropas/StardewValley_Character_Shirts.png"

#define TIPOS_CUERPO                                                           \
  ":/ropas/assets/ropas/StardewValley_Character_Farmer Base.png"

#define RUTA_FUENTE ":/fuentes/assets/fuentes/Stardew_Valley.otf"

// estas son las coordenadas de las ropas y demas que usa el personaje
#define COORDENADAS_PELOS {{1, 10}, {1, 11}, {7, 2}, {13, 6}, {4, 6}, {4, 12}}
#define COORDENADAS_GORROS {{13, 10}, {1, 5}, {13, 5}, {21, 2}, {41, 2}, {33, 4}}
#define COORDENADAS_PANTALONES {{1, 1}, {1, 25}, {1, 61}, {1, 73}}
#define COORDENADAS_REMERAS {{1, 10}, {5, 4}, {9, 5}, {5, 12}, {25, 9}}

// estos son los colores con los que pinto el pelo y los pantalones
#define COLOR_PANTALON QColor(60, 90, 200)
#define COLOR_PELO QColor(150, 80, 30)

#define X_CUERPO_EN_HOJA 0
#define Y_CUERPO_EN_HOJA 0
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

// Tarjetas de las listas de mundos y partidas
#define ALTO_TARJETA 80
#define TAMANIO_IMAGEN_TARJETA 64
#define ESTILO_TARJETA_TITULO                                                  \
  "color: #f1b356; font-family: 'Stardew Valley'; font-size: 18px; border: none;"
#define ESTILO_TARJETA_SUBTITULO                                               \
  "color: white; font-family: 'Stardew Valley'; font-size: 14px; border: none;"
#define ESTILO_TARJETA_EXTRA                                                   \
  "color: #f1b356; font-family: 'Stardew Valley'; font-size: 14px; border: none;"
#define ESTILO_TARJETA_BOTON                                                   \
  "background-color: #f1b356; color: #3b2010; font-weight: bold; "             \
  "border-radius: 3px; padding: 5px;"
#define ESTILO_TARJETA_SELECCIONADA                                            \
  "background-color: #5c341a; border: 2px solid #f1b356; border-radius: 5px;"
#define ESTILO_TARJETA_NO_SELECCIONADA                                         \
  "background-color: #3b2010; border: 2px solid #6b4020; border-radius: 5px;"
#define ESTILO_SIN_BORDE "border: none;"

// mensajes de error cuando quiero jugar y no puedo
#define TITULO_ERROR_JUGAR "No se pudo entrar"
#define ERROR_LOBBY_CODIGO "No existe una partida con ese código."
#define ERROR_LOBBY_NO_DISPONIBLE "Esta opción todavía no está disponible."
#define ERROR_LOBBY_CONEXION "Se perdió la conexión con el servidor: "

#endif // CONSTANTES_PANTALLAS_H_
