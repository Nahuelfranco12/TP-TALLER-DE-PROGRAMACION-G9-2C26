#include "personaje.h"

#include <SDL2/SDL.h>

using namespace SDL2pp;

namespace {
	// Cuántas prendas trae cada sheet
	const int CANTIDAD_PANTALONES = 16;
	const int CANTIDAD_REMERAS = 128;
	const int CANTIDAD_PELOS = 63;
	const int CANTIDAD_SOMBREROS = 122;

	// Paleta de colores
	const Uint8 COLORES[8][3] = {
		{60, 90, 200},    // azul
		{150, 80, 30},    // marrón
		{40, 30, 20},     // negro
		{230, 190, 90},   // rubio
		{200, 60, 40},    // rojo
		{70, 150, 70},    // verde
		{230, 230, 230},  // blanco
		{150, 80, 200},   // violeta
	};
	const int CANTIDAD_COLORES = 8;

	const int ESCALA = 4;
	const int TILE = 16 * ESCALA;

	const long VUELTAS_POR_PASO = 16;

	// Animación
	const int PASOS_ANIMACION[4] = {0, 1, 0, 2};  // columnas
	const long VUELTAS_POR_CUADRO = 9;        // 9 x 16 ms = 0.15 s
}

// Carga las texturas y deja la ropa y la posición iniciales
Personaje::Personaje(SDL2pp::Renderer& renderer)
	: cuerpo(renderer, "assets/personaje/StardewValley_Character_Farmer Base.png"),
	  pantalones(renderer, "assets/personaje/StardewValley_Character_Pants.png"),
	  remeras(renderer, "assets/personaje/StardewValley_Character_Shirts.png"),
	  pelos(renderer, "assets/personaje/StardewValley_Character_Hairstyles.png"),
	  sombreros(renderer, "assets/personaje/StardewValley_Character_Hats.png"),
	  pantalon(0),
	  remera(5),
	  pelo(3),
	  sombrero(2),
	  color_pantalon(0),
	  color_pelo(1),
	  tile_x(0),
	  tile_y(0),
	  mirando(ABAJO),
	  vueltas_caminando(0),
	  vueltas_restantes_paso(0) {
	// Colores iniciales
	pantalones.SetColorMod(COLORES[color_pantalon][0], COLORES[color_pantalon][1], COLORES[color_pantalon][2]);
	pelos.SetColorMod(COLORES[color_pelo][0], COLORES[color_pelo][1], COLORES[color_pelo][2]);
}

void Personaje::cambiar_pantalon() {
	pantalon = (pantalon + 1) % CANTIDAD_PANTALONES;
}

void Personaje::cambiar_remera() {
	remera = (remera + 1) % CANTIDAD_REMERAS;
}

void Personaje::cambiar_pelo() {
	pelo = (pelo + 1) % CANTIDAD_PELOS;
}

void Personaje::cambiar_sombrero() {
	sombrero = sombrero + 1;
    if (sombrero >= CANTIDAD_SOMBREROS) {
        sombrero = -1;
    }
}

void Personaje::cambiar_color_pantalon() {
	color_pantalon = (color_pantalon + 1) % CANTIDAD_COLORES;
	pantalones.SetColorMod(COLORES[color_pantalon][0], COLORES[color_pantalon][1], COLORES[color_pantalon][2]);
}

void Personaje::cambiar_color_pelo() {
	color_pelo = (color_pelo + 1) % CANTIDAD_COLORES;
	pelos.SetColorMod(COLORES[color_pelo][0], COLORES[color_pelo][1], COLORES[color_pelo][2]);
}

bool Personaje::aplicar(int nuevo_x, int nuevo_y) {
	if (nuevo_x == tile_x && nuevo_y == tile_y) {
		return false;
	}
	
	if (nuevo_x > tile_x) {
		mirando = DERECHA;
	} else if (nuevo_x < tile_x) {
		mirando = IZQUIERDA;
	} else if (nuevo_y > tile_y) {
		mirando = ABAJO;
	} else if (nuevo_y < tile_y) {
		mirando = ARRIBA;
	}

	tile_x = nuevo_x;
	tile_y = nuevo_y;
	vueltas_restantes_paso = VUELTAS_POR_PASO;
	return true;
}

void Personaje::animar(long vueltas) {
	if (vueltas_restantes_paso > 0) {
		vueltas_caminando += vueltas;
		vueltas_restantes_paso -= vueltas;
	} else {
		vueltas_caminando = 0;
	}
}

int Personaje::obtener_tile_x() const {
	return tile_x;
}

Direccion Personaje::obtener_direccion() const {
	return mirando;
}

int Personaje::obtener_tile_y() const {
	return tile_y;
}

// Dibuja todas las capas del granjero, una arriba de la otra
void Personaje::dibujar(Renderer& renderer, int camara_x, int camara_y) {
	// ¿Qué cuadro de la animación toca?
	int columna = 0;
	if (vueltas_restantes_paso > 0) {
		long paso = (vueltas_caminando / VUELTAS_POR_CUADRO) % 4;
		columna = PASOS_ANIMACION[paso];
	}

	// Saber si dibujarlo dado vuelta
	bool espejo = false;
	if (mirando == IZQUIERDA) {
		espejo = true;
	}

	// ¿Qué fila dibujar?
	int fila;
	if (mirando == IZQUIERDA) {
		fila = DERECHA;
	} else {
		fila = mirando;
	}

	// ¿Le pongo espejo?
	int flip;
	if (espejo) {
		flip = SDL_FLIP_HORIZONTAL;
	} else {
		flip = SDL_FLIP_NONE;
	}

	int x = tile_x * TILE - camara_x;
	int y = tile_y * TILE - TILE - camara_y;

	Rect destino(x, y, 16 * 4, 32 * 4);

	// Rebote: al caminar el cuerpo baja y la ropa baja con él
	int rebote = 0;
	if (columna != 0) {
		rebote = 1 * 4;
	}

	// Cuerpo
	Rect origen_cuerpo(columna * 16, fila * 32, 16, 32);
	renderer.Copy(cuerpo, origen_cuerpo, destino, 0.0, NullOpt, flip);

	// Pantalones
	Rect origen_pantalon((pantalon % 10) * 192 + columna * 16, (pantalon / 10) * 688 + fila * 32, 16, 32);
	renderer.Copy(pantalones, origen_pantalon, destino, 0.0, NullOpt, flip);

	// Remera
	int fila_remera = 0;  // abajo
	if (mirando == DERECHA) fila_remera = 8;
	if (mirando == IZQUIERDA) fila_remera = 16;
	if (mirando == ARRIBA) fila_remera = 24;
	Rect origen_remera((remera % 16) * 8, (remera / 16) * 32 + fila_remera, 8, 8);
	Rect destino_remera(x + 4 * 4, y + 15 * 4 + rebote, 8 * 4, 8 * 4);
	renderer.Copy(remeras, origen_remera, destino_remera);

	// Brazos
	Rect origen_brazos(96 + columna * 16, fila * 32, 16, 32);
	renderer.Copy(cuerpo, origen_brazos, destino, 0.0, NullOpt, flip);

	// Pelo
	Rect origen_pelo((pelo % 16) * 16, (pelo / 16) * 96 + fila * 32, 16, 32);
	Rect destino_pelo(static_cast<int>(x), static_cast<int>(y) + rebote, 16 * 4, 32 * 4);
	renderer.Copy(pelos, origen_pelo, destino_pelo, 0.0, NullOpt, flip);

	// Sombrero (-1 = sin sombrero)
	if (sombrero >= 0) {
		int fila_sombrero = 0;  // abajo
		if (mirando == DERECHA) fila_sombrero = 20;
		if (mirando == IZQUIERDA) fila_sombrero = 40;
		if (mirando == ARRIBA) fila_sombrero = 60;
		Rect origen_sombrero((sombrero % 12) * 20, (sombrero / 12) * 80 + fila_sombrero, 20, 20);
		Rect destino_sombrero(static_cast<int>(x) - 2 * 4, static_cast<int>(y) - 4 * 4 + rebote, 20 * 4, 20 * 4);
		renderer.Copy(sombreros, origen_sombrero, destino_sombrero);
	}
}