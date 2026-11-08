#ifndef CONSTANTES_H
#define CONSTANTES_H

#define TITULO_ABRIR "Abrir mapa"
#define FILTRO_MAPAS "Mapas (*.toml *.json)"

#define TAMANIO_ICONO 48
#define ROL_VALOR Qt::UserRole
#define ROL_ES_TERRENO (Qt::UserRole + 1)
#define COLOR_PLACEHOLDER QColor(120, 120, 120)

#define ANCHO_DISENIO 1280
#define ALTO_DISENIO 720

#define SUELO ":/Mapas/suelo.png"
#define DUNGEON ":/Mapas/dungeon.png"
#define OBJETOS ":/Mapas/objetos.png"
#define CERCO ":/Mapas/cerco.png"
#define PIEDRAS ":/Mapas/piedras.png"
#define ARBOL ":/Mapas/arbol.png"
#define CASA ":/Edificios/casa.png"
#define CABANIAS ":/Mapas/cabanias.png"
#define SIN_ASSET ""
#define RUTA_MARNIE ":/Npcs/marnie.png"
#define RUTA_CLINT ":/Npcs/clint.png"
#define RUTA_PIERRE ":/Npcs/pierre.png"
#define RUTA_ROBIN ":/Npcs/robin.png"
#define RUTA_CENTRO_COMUNITARIO ":/Mapas/centro_comunitario.png"

// recortes para el tema de mostrar bien segun el asset
#define RECORTE_MR {24, 16, 16, 32}
#define RECORTE_PC {0, 0, 32, 32}
#define RECORTE_CABANIA {144, 0, 80, 104}
#define RECORTE_PIEDRA {32, 0, 16, 16}
#define RECORTE_CERCO {16, 32, 16, 16}
#define RECORTE_ENTRADA_MINA {144, 48, 16, 16}
#define RECORTE_SALIDA_PUEBLO {0, 128, 16, 16}
#define RECORTE_CENTRO_COMUNITARIO {17, 181, 190, 123}
#define RECORTE_PASTO {64, 144, 16, 16}
#define RECORTE_TIERRA {16, 64, 16, 16}
#define RECORTE_PISO_CAVERNA {96, 16, 16, 16}
#define RECORTE_PARED_CAVERNA {32, 0, 16, 16}
#define RECORTE_CENTRO_COMUNITARIO {17, 181, 190, 123}
#define RECORTE_ESCALERA {144, 48, 16, 16}

#define TEXTO_PASTO "Pasto"
#define TEXTO_TIERRA "Tierra"
#define TEXTO_CAMINO "Camino"
#define TEXTO_PISO "Piso"
#define TEXTO_PARED "Pared"

#define TEXTO_CABANIA "Cabaña"
#define TEXTO_ARBOL "Árbol"
#define TEXTO_PIEDRA "Piedra"
#define TEXTO_CERCO "Cerco"
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

#endif  // CONSTANTES_H
