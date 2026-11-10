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

#define CANTIDAD_NIVELES_CAVERNA 10
#define PRIMER_NIVEL_CAVERNA 1
#define ANCHO_PREDETERMINADO 20
#define ALTO_PREDETERMINADO 15
#define DIMENSION_MINIMA 10
#define DIMENSION_MAXIMA 50

#define RUTA_SUELO ":/Mapas/suelo.png"
#define RUTA_CAVERNA ":/Mapas/dungeon.png"
#define RUTA_PISO_PIEDRA ":/Mapas/cam_piedras.png"
#define RUTA_OBJETOS ":/Mapas/objetos.png"
#define RUTA_CERCO_FRENTE ":/Mapas/cerco_frente.png"
#define RUTA_CERCO_COSTADO ":/Mapas/cerco_costado.png"
#define RUTA_PIEDRAS ":/Mapas/piedras.png"
#define RUTA_ARBOL1 ":/Mapas/arbol1.png"
#define RUTA_ARBOL2 ":/Mapas/arbol2.png"
#define RUTA_CENTRO_COMUNITARIO ":/Mapas/centro_comunitario.png"
#define RUTA_CASA ":/Edificios/casa.png"
#define SIN_ASSET ""
#define RUTA_MARNIE ":/Npcs/marnie.png"
#define RUTA_CLINT ":/Npcs/clint.png"
#define RUTA_PIERRE ":/Npcs/pierre.png"
#define RUTA_ROBIN ":/Npcs/robin.png"

#define RECORTE_MERNIE_ROBIN                                                   \
  { 24, 16, 16, 32 }
#define RECORTE_PC                                                             \
  { 0, 0, 32, 32 }
#define RECORTE_CABANIA                                                        \
  { 144, 0, 80, 104 }
#define RECORTE_PIEDRA                                                         \
  { 32, 0, 16, 16 }
#define RECORTE_CERCO_FRENTE                                                   \
  { 16, 32, 16, 16 }
#define RECORTE_CERCO_COSTADO                                                  \
  { 0, 16, 16, 16 }
#define RECORTE_ENTRADA_MINA                                                   \
  { 144, 48, 16, 16 }
#define RECORTE_SALIDA_PUEBLO                                                  \
  { 0, 128, 16, 16 }
#define RECORTE_CENTRO_COMUNITARIO                                             \
  { 17, 181, 190, 123 }
#define RECORTE_PASTO                                                          \
  { 64, 144, 16, 16 }
#define RECORTE_TIERRA                                                         \
  { 16, 64, 16, 16 }
#define RECORTE_PISO_CAVERNA                                                   \
  { 96, 16, 16, 16 }
#define RECORTE_PARED_CAVERNA                                                  \
  { 32, 0, 16, 16 }
#define RECORTE_ESCALERA                                                       \
  { 144, 48, 16, 16 }
#define RECORTE_PISO_PUEBLO                                                    \
  { 144, 32, 16, 16 }

#define TEXTO_PASTO "Pasto"
#define TEXTO_TIERRA "Tierra"
#define TEXTO_PISO "Piso"
#define TEXTO_PARED "Pared"
#define TEXTO_CABANIA "Cabaña"
#define TEXTO_ARBOL "Árbol"
#define TEXTO_PIEDRA "Piedra"
//#define TEXTO_CERCO "Cerco"
#define TEXTO_ENTRADA_MINA "Entrada a la mina"
#define TEXTO_SALIDA_PUEBLO "Salida al pueblo"
#define TEXTO_PISO_PUEBLO "Piso"
#define TEXTO_ESCALERA "Escalera"
#define TEXTO_SALIDA_CAVERNA "Salida"
#define TEXTO_MARNIE "Marnie"
#define TEXTO_CLINT "Clint"
#define TEXTO_PIERRE "Pierre"
#define TEXTO_ROBIN "Robin"
#define TEXTO_CENTRO_COMUNITARIO "Centro comunitario"
#define TEXTO_SALIDA_GRANJA "Salida a la granja"

#define TAMANIO_CELDA_MAPA 32
#define COLOR_LINEAS_GRILLA QColor(0, 0, 0, 60)
#define TEXTO_DESCONOCIDO "?"

#define TAMANIO_OCUPADO_ASSET_NORMAL 1
#define TAMANIO_OCUPADO_CABANIA_ANCHO 3
#define TAMANIO_OCUPADO_CABANIA_ALTO 4

#define TAMANIO_OCUPADO_CENTROCOM_ANCHO 6
#define TAMANIO_OCUPADO_CENTROCOM_ALTO 4

#define TAMANIO_OCUPADO_ARBOL2 2

#endif // CONSTANTES_H
