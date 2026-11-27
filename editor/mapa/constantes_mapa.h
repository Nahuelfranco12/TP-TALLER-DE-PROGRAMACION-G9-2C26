#ifndef CONSTANTES_MAPA_H_
#define CONSTANTES_MAPA_H_

// Niveles de caverna -> mapa_editor.cpp, archivo_mapa.cpp,
// validacion_mapas.cpp, controlador_mapas.cpp
#define CANTIDAD_NIVELES_CAVERNA 10
#define PRIMER_NIVEL_CAVERNA 1

// Dimensiones de zona -> mapa_editor.h, controlador_mapas.cpp
#define ANCHO_PREDETERMINADO 35
#define ALTO_PREDETERMINADO 25
#define DIMENSION_MINIMA 10
#define DIMENSION_MAXIMA 50

// Nombres de elementos -> validacion_mapas.cpp,
// catalogo_elementos.cpp
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
#define TEXTO_POZO "Pozo"

// Celdas que ocupa cada elemento (ancho x alto) ->
// mapa_editor.cpp
#define TAMANIO_OCUPADO_ASSET_NORMAL 1
#define TAMANIO_OCUPADO_CABANIA_ANCHO 3
#define TAMANIO_OCUPADO_CABANIA_ALTO 4
#define TAMANIO_OCUPADO_CENTRO_COMUNITARIO_ANCHO 8
#define TAMANIO_OCUPADO_CENTRO_COMUNITARIO_ALTO 6
#define TAMANIO_OCUPADO_ARBOL_ALTO 2
#define TAMANIO_OCUPADO_AGUA_ANCHO 4
#define TAMANIO_OCUPADO_AGUA_ALTO 4
#define TAMANIO_OCUPADO_FAROL_ALTO 2
#define TAMANIO_OCUPADO_BANCO_ANCHO 2
#define TAMANIO_OCUPADO_PUERTA_CAVERNA_ANCHO 2
#define TAMANIO_OCUPADO_CASA_NPC_ANCHO 5
#define TAMANIO_OCUPADO_CASA_NPC_ALTO 4
#define TAMANIO_OCUPADO_NPC_ANCHO_ALTO 2
#define TAMANIO_OCUPADO_POZO_ANCHO 2
#define TAMANIO_OCUPADO_POZO_ALTO 2

// Errores del modelo -> mapa_editor.h, mapa_editor.cpp
#define TEXTO_ERROR_DIMENSIONES_ZONA "Dimensiones de zona fuera de rango"
#define TEXTO_ERROR_CELDA_FUERA_DE_ZONA "Celda fuera de la zona"

// Validación para poder exportar -> validacion_mapas.cpp
#define VALIDACION_CABANIAS_MINIMAS 3
#define VALIDACION_TEXTO_ZONA_GRANJA "Granja"
#define VALIDACION_TEXTO_ZONA_PUEBLO "Pueblo"
#define VALIDACION_TEXTO_ZONA_CAVERNA "Caverna"
#define VALIDACION_TEXTO_SEPARADOR ": "
#define VALIDACION_TEXTO_FALTA "falta "
#define VALIDACION_TEXTO_NIVEL ", nivel "
#define VALIDACION_TEXTO_CABANIAS_INICIO "tenes que colocar al menos "
#define VALIDACION_TEXTO_CABANIAS_FIN " cabañas"
#define VALIDACION_TEXTO_ERROR_NOMBRE "No le pusiste nombre al mundo!"
#define VALIDACION_TEXTO_ESCALERA_PARED "la escalera tiene que estar en la pared de arriba, sin tocar las esquinas"
#define VALIDACION_TEXTO_SOBRA "no puede haber "

// Archivo TOML: versión y claves -> archivo_mapa.cpp
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

// Archivo TOML: errores al escribir y leer -> archivo_mapa.cpp
#define TEXTO_ERROR_ESCRIBIR "No se pudo escribir el archivo: "
#define TEXTO_ERROR_LEER "No se pudo leer el archivo: "
#define TEXTO_ERROR_VERSION "Version de archivo no soportada."
#define TEXTO_ERROR_DIMENSIONES "Dimensiones fuera de rango en: "
#define TEXTO_ERROR_OBJETO "Un objeto no entra o pisa a otro en: "
#define TEXTO_ERROR_NIVELES                                                    \
  "La caverna no tiene la cantidad de niveles esperada."
#define TEXTO_NIVEL_ARCHIVO " nivel "
#define TEXTO_ABRE_ID_MAPA " ("
#define TEXTO_CIERRA_ID_MAPA ")"
#define SEPARADOR_DETALLE_MAPA "\n"
#define FIN_ARCHIVO_MAPA "\n"

// Archivo TOML: errores de campos -> lectura_toml.h, lectura_toml.cpp,
// archivo_mapa.cpp
#define TEXTO_ERROR_CAMPO "Falta un dato o es invalido: "
#define TEXTO_ERROR_RANGO "Valor fuera de rango en "
#define SEPARADOR_CAMPO_MAPA "."

// Archivo TOML: errores de ids -> ids_mapa.h
#define TEXTO_ERROR_SIN_ID "Hay un elemento sin identificador en el archivo"
#define TEXTO_ERROR_TIPO "Elemento desconocido: "

// Archivo TOML: ids de la granja -> ids_mapa.cpp
#define ID_CABANIA1 "Cabania1"
#define ID_CABANIA2 "Cabania2"
#define ID_CABANIA3 "Cabania3"
#define ID_CABANIA4 "Cabania4"
#define ID_CABANIA5 "Cabania5"
#define ID_SALIDA_PUEBLO "SalidaPueblo"
#define ID_ARBOL1 "Arbol1"
#define ID_ARBOL2 "Arbol2"
#define ID_AGUA "Agua"
#define ID_PIEDRA "Piedra"
#define ID_PIEDRA_GRIS_GRANDE "PiedraGrisGrande"
#define ID_PIEDRA_GRIS "PiedraGris"
#define ID_ARBUSTO_REDONDO "ArbustoRedondo"
#define ID_ARBUSTO_GRANDE "ArbustoGrande"
#define ID_TRONCO_CAIDO "TroncoCaido"
#define ID_TOCON "Tocon"
#define ID_BUZON_ROJO "BuzonRojo"
#define ID_CARTEL_VACIO "CartelVacio"

// Archivo TOML: ids de la caverna -> ids_mapa.cpp
#define ID_ESCALERA "Escalera"
#define ID_SALIDA_CAVERNA "SalidaCaverna"
#define ID_BARRIL "Barril"
#define ID_CALAVERA "Calavera"
#define ID_HUESO "Hueso"
#define ID_ESCOMBROS "Escombros"
#define ID_ANTORCHA "Antorcha"
#define ID_CANDELABRO "Candelabro"
#define ID_ESCUDO "Escudo"
#define ID_POZO "Pozo"

// Archivo TOML: ids del pueblo -> ids_mapa.cpp
#define ID_NPC_MARNIE "NpcMarnie"
#define ID_NPC_CLINT "NpcClint"
#define ID_NPC_PIERRE "NpcPierre"
#define ID_NPC_ROBIN "NpcRobin"
#define ID_CASA_MARNIE "CasaMarnie"
#define ID_CASA_CLINT "CasaClint"
#define ID_CASA_PIERRE "CasaPierre"
#define ID_CASA_ROBIN "CasaRobin"
#define ID_CENTRO_COMUNITARIO "CentroComunitario"
#define ID_SALIDA_GRANJA "SalidaGranja"
#define ID_ENTRADA_MINA "EntradaMina"
#define ID_FAROL_NARANJA "FarolNaranja"
#define ID_FAROL_AZUL "FarolAzul"
#define ID_BANCO_MADERA "BancoMadera"
#define ID_BUZON_GRIS "BuzonGris"
#define ID_BUZON_AZUL "BuzonAzul"

#endif // CONSTANTES_MAPA_H_
