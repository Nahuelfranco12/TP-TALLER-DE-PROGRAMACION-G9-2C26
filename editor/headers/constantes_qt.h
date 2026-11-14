#ifndef CONSTANTES_QT_H_
#define CONSTANTES_QT_H_

#define TITULO_ABRIR "Abrir mapa"
#define FILTRO_MAPAS "Mapas (*.toml)"

#define TAMANIO_ICONO 48
#define ROL_VALOR Qt::UserRole
#define COLOR_GRIS_FALTA_ASSET QColor(120, 120, 120)

#define ANCHO_DISENIO 1366
#define ALTO_DISENIO 768

#define NOMBRE_PREDETERMINADO_AYUDA "Nombre del mundo"

// Rutas
#define RUTA_SUELO ":/Mapas/suelo.png"
#define RUTA_CAVERNA ":/Mapas/dungeon.png"
#define RUTA_PISO_PIEDRA ":/Mapas/cam_piedras.png"
#define RUTA_OBJETOS ":/Mapas/objetos.png"
#define RUTA_PIEDRAS ":/Mapas/piedras.png"
#define RUTA_ARBOL1 ":/Mapas/arbol1.png"
#define RUTA_ARBOL2 ":/Mapas/arbol2.png"
#define RUTA_AGUA ":/Mapas/naturaleza.png"
#define RUTA_CABANIAS ":/Mapas/cabanias.png"
#define RUTA_CENTRO_COMUNITARIO ":/Mapas/centro_comunitario.png"
#define RUTA_CASA_NPC ":/Mapas/casas_npcs.png"
#define RUTA_MARNIE ":/Npcs/marnie.png"
#define RUTA_CLINT ":/Npcs/clint.png"
#define RUTA_PIERRE ":/Npcs/pierre.png"
#define RUTA_ROBIN ":/Npcs/robin.png"
#define CARPETA_MAPAS "maps"

// Recortes Pueblo
#define RECORTE_PISO_PUEBLO                                                    \
  { 0, 0, 16, 16 }
#define RECORTE_MERNIE_ROBIN                                                   \
  { 24, 16, 16, 32 }
#define RECORTE_PC                                                             \
  { 0, 0, 32, 32 }
#define RECORTE_SALIDA_PUEBLO                                                  \
  { 0, 128, 16, 16 }
#define RECORTE_CENTRO_COMUNITARIO                                             \
  { 17, 181, 190, 123 }
#define RECORTE_FAROL_NARANJA                                                  \
  { 51, 82, 11, 28 }
#define RECORTE_FAROL_AZUL                                                     \
  { 64, 82, 16, 28 }
#define RECORTE_BANCO_MADERA                                                   \
  { 36, 59, 25, 19 }
#define RECORTE_BUZON_GRIS                                                     \
  { 3, 91, 11, 20 }
#define RECORTE_BUZON_AZUL                                                     \
  { 35, 91, 11, 20 }
#define RECORTE_CASA_ROBIN                                                     \
  { 192, 640, 192, 160 }
#define RECORTE_CASA_MARNIE                                                    \
  { 256, 16, 142, 160 }
#define RECORTE_CASA_PIERRE                                                    \
  { 240, 176, 112, 144 }
#define RECORTE_CASA_CLINT                                                     \
  { 80, 320, 144, 128 }

// Recortes Granja
#define RECORTE_CABANIA1                                                       \
  { 160, 0, 80, 112 }
#define RECORTE_CABANIA2                                                       \
  { 160, 112, 80, 112 }
#define RECORTE_CABANIA3                                                       \
  { 160, 224, 80, 112 }
#define RECORTE_CABANIA4                                                       \
  { 160, 336, 80, 112 }
#define RECORTE_CABANIA5                                                       \
  { 160, 448, 80, 112 }
#define RECORTE_PIEDRA                                                         \
  { 32, 0, 16, 16 }
#define RECORTE_ENTRADA_MINA                                                   \
  { 144, 48, 16, 16 }
#define RECORTE_PASTO                                                          \
  { 64, 144, 16, 16 }
#define RECORTE_AGUA                                                           \
  { 0, 80, 64, 64 }
#define RECORTE_ARBUSTO_REDONDO                                                \
  { 112, 160, 16, 16 }
#define RECORTE_ARBUSTO_GRANDE                                                 \
  { 128, 176, 16, 16 }
#define RECORTE_PIEDRA_GRIS_GRANDE                                             \
  { 128, 144, 16, 16 }
#define RECORTE_PIEDRA_GRIS                                                    \
  { 160, 144, 16, 16 }
#define RECORTE_TRONCO_CAIDO                                                   \
  { 144, 96, 16, 16 }
#define RECORTE_TOCON                                                          \
  { 128, 112, 16, 16 }
#define RECORTE_BUZON_ROJO                                                     \
  { 19, 91, 11, 20 }
#define RECORTE_CARTEL_VACIO                                                   \
  { 0, 112, 16, 16 }

// Recortes Caverna
#define RECORTE_PISO_CAVERNA                                                   \
  { 16, 16, 16, 16 }
#define RECORTE_PARED_CAVERNA                                                  \
  { 32, 0, 16, 16 }
#define RECORTE_ESCALERA                                                       \
  { 144, 48, 16, 16 }
#define RECORTE_PUERTA_CAVERNA                                                 \
  { 96, 96, 32, 16 }
#define RECORTE_BARRIL                                                         \
  { 128, 48, 16, 16 }
#define RECORTE_CALAVERA                                                       \
  { 112, 112, 16, 16 }
#define RECORTE_HUESO                                                          \
  { 128, 96, 16, 16 }
#define RECORTE_ESCOMBROS                                                      \
  { 144, 64, 16, 16 }
#define RECORTE_ANTORCHA                                                       \
  { 0, 144, 16, 16 }
#define RECORTE_CANDELABRO                                                     \
  { 48, 144, 16, 16 }
#define RECORTE_ESCUDO                                                         \
  { 64, 112, 16, 16 }

// Textos Terrenos
#define TEXTO_PASTO "Pasto"
#define TEXTO_PISO "Piso"
#define TEXTO_PARED "Pared"
#define TEXTO_PISO_PUEBLO "Piso"

// Textos Granja
#define TEXTO_CABANIA1 "Cabaña 1"
#define TEXTO_CABANIA2 "Cabaña 2"
#define TEXTO_CABANIA3 "Cabaña 3"
#define TEXTO_CABANIA4 "Cabaña 4"
#define TEXTO_CABANIA5 "Cabaña 5"
#define TEXTO_ARBOL1 "Arbol1"
#define TEXTO_ARBOL2 "Arbol2"
#define TEXTO_PIEDRA "Piedra"
#define TEXTO_AGUA "Agua"
#define TEXTO_ARBUSTO_REDONDO "Arbusto redondo"
#define TEXTO_ARBUSTO_GRANDE "Arbusto grande"
#define TEXTO_PIEDRA_GRIS_GRANDE "Piedra gris grande"
#define TEXTO_PIEDRA_GRIS "Piedra gris"
#define TEXTO_TRONCO_CAIDO "Tronco caído"
#define TEXTO_TOCON "Tronco cortado"
#define TEXTO_BUZON_ROJO "Buzon rojo"
#define TEXTO_CARTEL_VACIO "Cartel"

// Textos Caverna
#define TEXTO_BARRIL "Barril"
#define TEXTO_CALAVERA "Calavera"
#define TEXTO_HUESO "Hueso"
#define TEXTO_ESCOMBROS "Escombros"
#define TEXTO_ANTORCHA "Antorcha"
#define TEXTO_CANDELABRO "Candelabro"
#define TEXTO_ESCUDO "Escudo"

// Textos Pueblo
#define TEXTO_FAROL_NARANJA "Farol naranja"
#define TEXTO_FAROL_AZUL "Farol azul"
#define TEXTO_BANCO_MADERA "Banco"
#define TEXTO_BUZON_GRIS "Buzón gris"
#define TEXTO_BUZON_AZUL "Buzón azul"

// Grilla
#define TAMANIO_CELDA_MAPA 24
#define TEXTO_DESCONOCIDO "?"
#define COLOR_LINEAS_GRILLA QColor(0, 0, 0, 60)

// Validaciones para que se pueda exportar el archivo
#define VALIDACION_TEXTO_TITULO_MAPA_INVALIDO "El mapa no esta completo"

// estas son de interfaz
#define TITULO_GUARDAR "Guardar mapa"
#define TITULO_MAPA_GUARDADO "Mapa guardado"
#define TEXTO_MAPA_GUARDADO "El mapa se guardó en:\n"
#define TITULO_ERROR_GUARDAR "No se pudo guardar"

// sobre editar mapas
#define TITULO_ERROR_CARGAR "No se pudo abrir el mapa"

#define TEXTO_NO_SE_PUEDE_COLOCAR "No entra ahí o pisa otro objeto"
#define TEXTO_ELEGIR_ELEMENTO "Elegí un elemento de la paleta"

#endif // CONSTANTES_QT_H_
