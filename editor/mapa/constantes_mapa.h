#ifndef CONSTANTES_MAPA_H_
#define CONSTANTES_MAPA_H_

// Caverna y dimensiones
#define CANTIDAD_NIVELES_CAVERNA 10
#define PRIMER_NIVEL_CAVERNA 1
#define ANCHO_PREDETERMINADO 35
#define ALTO_PREDETERMINADO 25
#define DIMENSION_MINIMA 10
#define DIMENSION_MAXIMA 50
#define MAX_LARGO_NOMBRE_MUNDO 50

// Nombres de elementos que usa la validación
#define TEXTO_ENTRADA_MINA "Entrada a la mina"
#define TEXTO_SALIDA_PUEBLO "Salida al pueblo"
#define TEXTO_ESCALERA "Escalera"
#define TEXTO_SALIDA_CAVERNA "Salida"
#define TEXTO_MARNIE "Marnie"
#define TEXTO_CLINT "Clint"
#define TEXTO_PIERRE "Pierre"
#define TEXTO_ROBIN "Robin"
#define TEXTO_CENTRO_COMUNITARIO "Centro comunitario"
#define TEXTO_SALIDA_GRANJA "Salida a la granja"
#define TEXTO_CASA_ROBIN "Casa Robin"
#define TEXTO_CASA_CLINT "Casa Clint"
#define TEXTO_CASA_PIERRE "Casa Pierre"
#define TEXTO_CASA_MARNIE "Casa Marnie"

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
#define TAMANIO_OCUPADO_PUERTA_CAVERNA_ANCHO 2
#define TAMANIO_ANCHO_CASA_NPC 5
#define TAMANIO_ALTO_CASA_NPC 4
#define TAMANIO_ALTO_ANCHO_NPC 2

// Validaciones para que se pueda exportar el archivo
#define VALIDACION_CABANIAS_MINIMAS 3
#define VALIDACION_TEXTO_ZONA_GRANJA "Granja"
#define VALIDACION_TEXTO_ZONA_PUEBLO "Pueblo"
#define VALIDACION_TEXTO_ZONA_CAVERMA "Caverna"
#define VALIDACION_TEXTO_SEPARADOR ": "
#define VALIDACION_TEXTO_FALTA "falta "
#define VALIDACION_TEXTO_NIVEL ", nivel "
#define VALIDACION_TEXTO_CABANIAS_INICIO "tenes que colocar al menos "
#define VALIDACION_TEXTO_CABANIAS_FIN " cabañas"
#define VALIDACION_TEXTO_ERROR_NOMBRE "No le pusiste nombre al mundo!"

// Archivo del mapa
#define EXTENSION_MAPA ".toml"
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
#define TEXTO_ERROR_LEER "No se pudo leer el archivo: "
#define TEXTO_ERROR_VERSION "Version de archivo no soportada."
#define TEXTO_ERROR_CAMPO "Falta un dato o es invalido: "
#define TEXTO_ERROR_TIPO "Elemento desconocido: "
#define TEXTO_ERROR_DIMENSIONES "Dimensiones fuera de rango en: "
#define TEXTO_ERROR_OBJETO "Un objeto no entra o pisa a otro en: "
#define TEXTO_ERROR_NIVELES                                                    \
  "La caverna no tiene la cantidad de niveles esperada."
#define TEXTO_NIVEL_ARCHIVO " nivel "

#endif // CONSTANTES_MAPA_H_
