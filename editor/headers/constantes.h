#ifndef CONSTANTES_H
#define CONSTANTES_H

#define TITULO_ABRIR "Abrir mapa"
#define FILTRO_MAPAS "Mapas (*.toml)"

#define TAMANIO_ICONO 48
#define ROL_VALOR Qt::UserRole
#define ROL_ES_TERRENO (Qt::UserRole + 1)
#define COLOR_GRIS_FALTA_ASSET QColor(120, 120, 120)

#define ANCHO_DISENIO 1366
#define ALTO_DISENIO 768

#define TAMANIO_TILE_ORIGINAL 16

#define CANTIDAD_NIVELES_CAVERNA 10
#define PRIMER_NIVEL_CAVERNA 1
#define ANCHO_PREDETERMINADO 35
#define ALTO_PREDETERMINADO 25
#define DIMENSION_MINIMA 10
#define DIMENSION_MAXIMA 50
#define MAX_LARGO_NOMBRE_MUNDO 50
#define NOMBRE_PREDETERMINADO_AYUDA "Nombre del mundo"

// Rutas
#define RUTA_SUELO ":/Mapas/suelo.png"
#define RUTA_CAVERNA ":/Mapas/dungeon.png"
#define RUTA_PISO_PIEDRA ":/Mapas/cam_piedras.png"
#define RUTA_OBJETOS ":/Mapas/objetos.png"
#define RUTA_PIEDRAS ":/Mapas/piedras.png"
#define RUTA_ARBOL1 ":/Mapas/arbol1.png"
#define RUTA_ARBOL2 ":/Mapas/arbol2.png"
// #define RUTA_ARBOL3 ":/Mapas/arbol3.png"
// #define RUTA_ARBOL4 ":/Mapas/arbol4.png"
// #define RUTA_ARBOL5 ":/Mapas/arbol5.png"
#define RUTA_AGUA ":/Mapas/naturaleza.png"
#define RUTA_CABANIAS ":/Mapas/cabanias.png"
#define RUTA_CASAS ":/Mapas/casas.png"
#define RUTA_CENTRO_COMUNITARIO ":/Mapas/centro_comunitario.png"
#define RUTA_CASA_NPC ":/Mapas/casas_npcs.png"
//#define RUTA_CASA ":/Edificios/casa.png"
#define SIN_ASSET ""
#define RUTA_MARNIE ":/Npcs/marnie.png"
#define RUTA_CLINT ":/Npcs/clint.png"
#define RUTA_PIERRE ":/Npcs/pierre.png"
#define RUTA_ROBIN ":/Npcs/robin.png"

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
//#define RECORTE_CASA_CHICA {33, 37, 95, 124}
//#define RECORTE_CASA_MEDIANA {161, 29, 159, 132}
#define RECORTE_CASA_ROBIN                                                     \
  { 192, 640, 192, 160 }
#define RECORTE_CASA_MARNIE                                                    \
  { 256, 16, 142, 160 }
#define RECORTE_CASA_PIERRE                                                    \
  { 240, 176, 112, 144 }
#define RECORTE_CASA_CLINT                                                     \
  { 80, 320, 144, 128 }

// Recortes Granja
//#define RECORTE_CABANIA {144, 0, 80, 104}
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
//#define RECORTE_CABANIA6 {160, 112, 80, 112}
#define RECORTE_PIEDRA                                                         \
  { 32, 0, 16, 16 }
#define RECORTE_ENTRADA_MINA                                                   \
  { 144, 48, 16, 16 }
#define RECORTE_PASTO                                                          \
  { 64, 144, 16, 16 }
#define RECORTE_TIERRA                                                         \
  { 16, 64, 16, 16 }
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
#define RECORTE_TOCON                                                 \
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
#define TEXTO_TIERRA "Tierra"
#define TEXTO_PISO "Piso"
#define TEXTO_PARED "Pared"
#define TEXTO_PISO_PUEBLO "Piso"

// Textos Granja
#define TEXTO_CABANIA1 "Cabaña 1"
#define TEXTO_CABANIA2 "Cabaña 2"
#define TEXTO_CABANIA3 "Cabaña 3"
#define TEXTO_CABANIA4 "Cabaña 4"
#define TEXTO_CABANIA5 "Cabaña 5"
//#define TEXTO_CABANIA6 "Cabaña 6"
#define TEXTO_ARBOL1 "Arbol1"
#define TEXTO_ARBOL2 "Arbol2"
#define TEXTO_ARBOL3 "Arbol3"
#define TEXTO_ARBOL4 "Arbol4"
#define TEXTO_ARBOL5 "Arbol5"
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
#define TEXTO_ENTRADA_MINA "Entrada a la mina"
#define TEXTO_SALIDA_PUEBLO "Salida al pueblo"

// Textos Caverna
#define TEXTO_ESCALERA "Escalera"
#define TEXTO_SALIDA_CAVERNA "Salida"
#define TEXTO_BARRIL "Barril"
#define TEXTO_CALAVERA "Calavera"
#define TEXTO_HUESO "Hueso"
#define TEXTO_ESCOMBROS "Escombros"
#define TEXTO_ANTORCHA "Antorcha"
#define TEXTO_CANDELABRO "Candelabro"
#define TEXTO_ESCUDO "Escudo"

// Textos Pueblo
#define TEXTO_MARNIE "Marnie"
#define TEXTO_CLINT "Clint"
#define TEXTO_PIERRE "Pierre"
#define TEXTO_ROBIN "Robin"
#define TEXTO_CENTRO_COMUNITARIO "Centro comunitario"
#define TEXTO_SALIDA_GRANJA "Salida a la granja"
#define TEXTO_FAROL_NARANJA "Farol naranja"
#define TEXTO_FAROL_AZUL "Farol azul"
#define TEXTO_BANCO_MADERA "Banco"
#define TEXTO_BUZON_GRIS "Buzón gris"
#define TEXTO_BUZON_AZUL "Buzón azul"
#define TEXTO_CASA_CHICA "Casa chica"
#define TEXTO_CASA_MEDIANA "Casa mediana"
#define TEXTO_CASA_ROBIN "Casa Robin"
#define TEXTO_CASA_CLINT "Casa Clint"
#define TEXTO_CASA_PIERRE "Casa Pierre"
#define TEXTO_CASA_MARNIE "Casa Marnie"

// Grilla
#define TAMANIO_CELDA_MAPA 24
#define TEXTO_DESCONOCIDO "?"

// Celdas que ocupa cada elemento (ancho x alto)
#define TAMANIO_OCUPADO_ASSET_NORMAL 1
#define TAMANIO_OCUPADO_CABANIA_ANCHO 3
#define TAMANIO_OCUPADO_CABANIA_ALTO 4
#define TAMANIO_OCUPADO_CENTROCOM_ANCHO 8
#define TAMANIO_OCUPADO_CENTROCOM_ALTO 6
#define TAMANIO_OCUPADO_ARBOL_ALTO 2
#define TAMANIO_OCUPADO_AGUA_ANCHO 4
#define TAMANIO_OCUPADO_AGUA_ALTO 4
#define TAMANIO_OCUPADO_FAROL_ALTO 2
#define TAMANIO_OCUPADO_BANCO_ANCHO 2
#define TAMANIO_OCUPADO_CASA_CHICA_ANCHO 3
#define TAMANIO_OCUPADO_CASA_CHICA_ALTO 4
#define TAMANIO_OCUPADO_CASA_MEDIANA_ANCHO 5
#define TAMANIO_OCUPADO_CASA_MEDIANA_ALTO 4
#define TAMANIO_OCUPADO_PUERTA_CAVERNA_ANCHO 2
#define TAMANIO_ANCHO_CASA_NPC 5
#define TAMANIO_ALTO_CASA_NPC 4
#define TAMANIO_ALTO_ANCHO_NPC 2
#define COLOR_LINEAS_GRILLA QColor(0, 0, 0, 60)

// Validaciones para que se pueda exportar el archivo
#define VALIDACION_CABANIAS_MINIMAS 3
#define VALIDACION_TEXTO_ERROR_NOMBRE "No le pusiste nombre al mundo!"
#define VALIDACION_TEXTO_ERROR_FALTA " Falta"
#define VALIDACION_TEXTO_ERROR_CABANIAS "Tenes que colocar MINIMO "
#define VALIDACION_TEXTO_CABANIAS_PLURAL " cabañas"
#define VALIDACION_TEXTO_ZONA_GRANJA "Granja"
#define VALIDACION_TEXTO_ZONA_PUEBLO "Pueblo"
#define VALIDACION_TEXTO_NIVEL "Nivel "
#define VALIDACION_TEXTO_TITULO_MAPA_INVALIDO "El mapa no esta completo"
#define VALIDACION_TEXTO_TITULO_MAPA_VALIDO "Titulo del mapa valido"
#define VALIDACION_TEXTO_MAPA_VALIDO "El mapa tiene todo lo necesario"

// Claves para lo que es el mapa, osea la clave que los representa
#define VERSION_ARCHIVO_MAPA 1
#define CLAVE_VERSION "version"
#define CLAVE_NOMBRE "nombre"
#define CLAVE_GRANJA "granja"
#define CLAVE_CAVERNA "caverna"
#define CLAVE_PUEBLO "pueblo"
#define CLAVE_NIVELES "niveles"
#define CLAVE_ANCHO "ancho"
#define CLAVE_ALTO "alto"
#define CLAVE_OBJETOS "objetos"
#define CLAVE_TIPO "tipo"
#define CLAVE_X "x"
#define CLAVE_Y "y"
#define TEXTO_ERROR_ESCRIBIR "No se pudo escribir el archivo: "
#define TEXTO_ERROR_SIN_ID "Hay un elemento sin identificador en el archivo"

// estas son de interfaz
#define TITULO_GUARDAR "Guardar mapa"
#define EXTENSION_MAPA ".toml"
#define TITULO_MAPA_GUARDADO "Mapa guardado"
#define TEXTO_MAPA_GUARDADO "El mapa se guardó en:\n"
#define TITULO_ERROR_GUARDAR "No se pudo guardar"

//sobre editar mapas
#define TEXTO_ERROR_LEER "No se pudo leer el archivo: "
#define TEXTO_ERROR_VERSION "Version de archivo no soportada."
#define TEXTO_ERROR_CAMPO "Falta un dato o es invalido: "
#define TEXTO_ERROR_TIPO "Elemento desconocido: "
#define TEXTO_ERROR_DIMENSIONES "Dimensiones fuera de rango en: "
#define TEXTO_ERROR_OBJETO "Un objeto no entra o pisa a otro en: "
#define TEXTO_ERROR_NIVELES "La caverna no tiene la cantidad de niveles esperada."
#define TEXTO_NIVEL_ARCHIVO " nivel "
#define TITULO_ERROR_CARGAR "No se pudo abrir el mapa"


#endif // CONSTANTES_H
