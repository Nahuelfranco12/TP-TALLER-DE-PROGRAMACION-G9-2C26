#ifndef CONSTANTES_PERSISTENCIA_H_
#define CONSTANTES_PERSISTENCIA_H_

// Archivos de partidas -> archivo_partida.cpp
#define RUTA_PARTIDAS "partidas"
#define NOMBRE_ARCHIVO_PARTIDA "partida.toml"
#define NOMBRE_ARCHIVO_MAPA "mapa.toml"
#define EXTENSION_ARCHIVO_TEMPORAL ".tmp"

// Archivo TOML: versión y claves -> archivo_partida.cpp
#define VERSION_ARCHIVO_PARTIDA 1
#define CLAVE_PARTIDA_VERSION "version"
#define CLAVE_PARTIDA_NOMBRE "nombre"
#define CLAVE_PARTIDA_CODIGO "codigo"
#define CLAVE_PARTIDA_DIA "dia"
#define CLAVE_PARTIDA_MULTIPLAYER "multiplayer"
#define CLAVE_PARTIDA_JUGADORES "jugadores"
#define CLAVE_PARTIDA_INDICE "indice"
#define CLAVE_PARTIDA_OUTFIT "outfit"
#define CLAVE_PARTIDA_GORRO "gorro"
#define CLAVE_PARTIDA_PELO "pelo"
#define CLAVE_PARTIDA_REMERA "remera"
#define CLAVE_PARTIDA_PANTALON "pantalon"
#define CLAVE_PARTIDA_VIDA "vida"
#define CLAVE_PARTIDA_ENERGIA "energia"
#define CLAVE_PARTIDA_ORO "oro"
#define CLAVE_PARTIDA_INVENTARIO "inventario"
#define CLAVE_PARTIDA_TIPO "tipo"
#define CLAVE_PARTIDA_CALIDAD "calidad"
#define CLAVE_PARTIDA_CANTIDAD "cantidad"
#define CLAVE_PARTIDA_GRANJA "granja"
#define CLAVE_PARTIDA_ARADAS "aradas"
#define CLAVE_PARTIDA_CULTIVOS "cultivos"
#define CLAVE_PARTIDA_X "x"
#define CLAVE_PARTIDA_Y "y"
#define CLAVE_PARTIDA_CRECIMIENTO "crecimiento"
#define CLAVE_PARTIDA_DESDE_RIEGO "desde_riego"
#define CLAVE_PARTIDA_CON_SED "con_sed"
#define CLAVE_PARTIDA_MADURO "maduro"
#define CLAVE_PARTIDA_COSECHAS_EXTRA "cosechas_extra"
#define CLAVE_PARTIDA_SUERTE "suerte"
#define CLAVE_PARTIDA_COFRES "cofres"
#define CLAVE_PARTIDA_ANIMALES "animales"
#define CLAVE_PARTIDA_LISTO "listo"

// Archivo TOML: errores al escribir y leer -> archivo_partida.cpp
#define ERROR_PARTIDA_ESCRIBIR "No se pudo escribir la partida: "
#define ERROR_PARTIDA_COPIAR_MAPA "No se pudo copiar el mapa: "
#define ERROR_PARTIDA_LEER "No se pudo leer la partida: "
#define ERROR_PARTIDA_VERSION "Versión de partida no soportada."
#define ERROR_PARTIDA_IGNORADA "Se ignora la partida guardada en "
#define SEPARADOR_DETALLE_PARTIDA ": "

// Archivo TOML: errores de campos -> lectura_toml.h, lectura_toml.cpp
#define ERROR_PARTIDA_CAMPO "Falta un dato o es inválido: "
#define ERROR_PARTIDA_RANGO "Valor fuera de rango en "
#define SEPARADOR_CAMPO_PARTIDA "."
#define SEPARADOR_INDICE_PARTIDA " "
#define PRIMER_ELEMENTO_PARTIDA 1

// Archivo TOML: errores de ids -> ids_partida.h
#define ERROR_PARTIDA_SIN_ID "Hay un elemento sin identificador en la partida"
#define ERROR_PARTIDA_TIPO "Elemento desconocido: "

// Archivo TOML: ids de cultivos -> ids_partida.cpp
#define ID_CULTIVO_FRUTILLA "Frutilla"
#define ID_CULTIVO_CEBOLLA_DE_VERDEO "CebollaDeVerdeo"
#define ID_CULTIVO_PAPA "Papa"
#define ID_CULTIVO_CALABAZA "Calabaza"

// Archivo TOML: ids de calidades -> ids_partida.cpp
#define ID_CALIDAD_BASE "Base"
#define ID_CALIDAD_BUENA "Buena"
#define ID_CALIDAD_EXCELENTE "Excelente"
#define ID_CALIDAD_INCREIBLE "Increible"
#define ID_CALIDAD_PERFECTA "Perfecta"

// Archivo TOML: ids de minerales -> ids_partida.cpp
#define ID_MINERAL_ORO "Oro"
#define ID_MINERAL_PLATA "Plata"
#define ID_MINERAL_LAPISLAZULI "Lapislazuli"
#define ID_MINERAL_CARBON "Carbon"

// Archivo TOML: ids de ítems del inventario -> ids_partida.cpp
#define ID_ITEM_SEMILLA_FRUTILLA "SemillaFrutilla"
#define ID_ITEM_SEMILLA_CEBOLLA_DE_VERDEO "SemillaCebollaDeVerdeo"
#define ID_ITEM_SEMILLA_PAPA "SemillaPapa"
#define ID_ITEM_SEMILLA_CALABAZA "SemillaCalabaza"
#define ID_ITEM_LECHE "Leche"
#define ID_ITEM_HUEVO "Huevo"
#define ID_ITEM_VACA "vaca"
#define ID_ITEM_GALLINA "gallina"
#define ID_ITEM_COFRE "cofre"

// Adaptador del mundo -> adaptador_partida.cpp
#define MINIMO_JUGADORES_MULTIPLAYER 2
#define ERROR_ADAPTADOR_SIN_GRANJA "La partida no tiene granja"
#define ERROR_ADAPTADOR_ITEM_SIN_SUBTIPO "Hay un ítem sin subtipo para guardar"
#define ERROR_ADAPTADOR_COFRE_OCUPADO "No se pudo restaurar un cofre: la celda está ocupada"
#define ERROR_ADAPTADOR_ANIMAL_OCUPADO "No se pudo restaurar un animal: la celda está ocupada"
#define ERROR_ADAPTADOR_ITEM_SIN_PRECIO "Item sin precio"

#endif // CONSTANTES_PERSISTENCIA_H_
