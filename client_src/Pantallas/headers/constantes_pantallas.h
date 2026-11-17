#ifndef CONSTANTES_PANTALLAS_H_
#define CONSTANTES_PANTALLAS_H_

// ACLARACION: las constantes estan centralizadas en este archivo, la idea es
// agruparlas en lo que es cada una, por ejemplo textos, cantidades, rutas, etc.
// Ese grupo se dice con un comentario arriba en que archivos se uso, esto para
// ser mas claro, por ejemplo grupo -> archivo1.cpp, archivoN.cpp

// Diseño responsive -> pantalla.cpp
#define ANCHO_DISENIO 1360
#define ALTO_DISENIO 768

// Rutas de recursos -> dibujar_personaje.cpp, pantalla.cpp
#define TIPOS_PELO ":/ropas/assets/ropas/StardewValley_Character_Hairstyles.png"
#define TIPOS_GORRO ":/ropas/assets/ropas/StardewValley_Character_Hats.png"
#define TIPOS_PANTALON ":/ropas/assets/ropas/StardewValley_Character_Pants.png"
#define TIPOS_REMERA ":/ropas/assets/ropas/StardewValley_Character_Shirts.png"
#define TIPOS_CUERPO ":/ropas/assets/ropas/StardewValley_Character_Farmer Base.png"
#define RUTA_FUENTE ":/fuentes/assets/fuentes/Stardew_Valley.otf"

// Escalas -> controlador_customizar_personaje.cpp, controlador_retomar_partida.cpp
#define ESCALA_PREVISUALIZACION 6
#define ESCALA_TARJETA 4

// Direcciones -> controlador_customizar_personaje.cpp
#define DIRECCION_ANTERIOR -1
#define DIRECCION_SIGUIENTE 1

// Coordenadas de las ropas en las hojas -> dibujar_personaje.cpp
#define BASE_COORDENADAS 1
#define COORDENADAS_PELOS {{1, 10}, {1, 11}, {7, 2}, {13, 6}, {4, 6}, { 4, 12 }}
#define COORDENADAS_GORROS {{13, 10}, {1, 5}, {13, 5}, {21, 2}, {41, 2}, { 33, 4 }}
#define COORDENADAS_PANTALONES {{1, 1}, {1, 25}, {1, 61}, { 1, 73 }}
#define COORDENADAS_REMERAS {{1, 10}, {5, 4}, {9, 5}, {5, 12}, { 25, 9 }}
#define OPCION_POR_DEFECTO 0

// Medidas de las ropas en las hojas -> dibujar_personaje.cpp
#define ANCHO_GORRO 20
#define ALTO_GORRO 20
#define ANCHO_PELO 16
#define ALTO_PELO 32
#define ANCHO_REMERA 8
#define ALTO_REMERA 8
#define ANCHO_PANTALON 16
#define ALTO_PANTALON 32

// Cuerpo y lienzo del personaje -> dibujar_personaje.cpp
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

// Colores -> dibujar_personaje.cpp
#define COLOR_PANTALON QColor(60, 90, 200)
#define COLOR_PELO QColor(150, 80, 30)

// Textos visibles -> controlador_nueva_partida.cpp, controlador_retomar_partida.cpp
#define ELEGIR_MAPA "Elegir Mapa"
#define TEXTO_MULTIPLAYER "Multiplayer"
#define TEXTO_SINGLEPLAYER "Singleplayer"
#define TEXTO_SELECCIONAR "Seleccionar"

// Tarjetas de mundos y partidas -> tarjeta_item.cpp
#define ALTO_TARJETA 80
#define TAMANIO_IMAGEN_TARJETA 64
#define ESTILO_TARJETA_TITULO "color: #f1b356; font-family: 'Stardew Valley'; font-size: 18px; border: " "none;"
#define ESTILO_TARJETA_SUBTITULO "color: white; font-family: 'Stardew Valley'; font-size: 14px; border: " "none;"
#define ESTILO_TARJETA_EXTRA "color: #f1b356; font-family: 'Stardew Valley'; font-size: 14px; border: " "none;"
#define ESTILO_TARJETA_BOTON "background-color: #f1b356; color: #3b2010; font-weight: bold; " "border-radius: 3px; padding: 5px;"
#define ESTILO_TARJETA_SELECCIONADA "background-color: #5c341a; border: 2px solid #f1b356; border-radius: 5px;"
#define ESTILO_TARJETA_NO_SELECCIONADA "background-color: #3b2010; border: 2px solid #6b4020; border-radius: 5px;"
#define ESTILO_SIN_BORDE "border: none;"

// Errores del lobby -> controlador_pagina.cpp, servicio_lobby_red.cpp
#define TITULO_ERROR_JUGAR "No se pudo entrar"
#define ERROR_LOBBY_CODIGO "No existe una partida con ese código."
#define ERROR_LOBBY_NO_DISPONIBLE "Esta opción todavía no está disponible."
#define ERROR_LOBBY_CONEXION "Se perdió la conexión con el servidor: "
#define ERROR_LOBBY_CREAR "No se pudo crear la partida."
#define ERROR_LOBBY_ENTRAR_CREADA "Se creó la partida, pero no se pudo entrar."
#define ERROR_LOBBY_SIN_MODO "No se eligió cómo jugar la partida."

#endif // CONSTANTES_PANTALLAS_H_
