#ifndef DIBUJAR_PERSONAJE_H_
#define DIBUJAR_PERSONAJE_H_

#include <QList>
#include <QPixmap>

#include "dtos_pantallas.h"

struct CoordenadaSprite {
  int fila{};
  int columna{};
};

struct HojaPrenda {
  QPixmap hoja;
  QList<CoordenadaSprite> opciones;
  int ancho{};
  int alto{};

  QPixmap recortar(int indice) const;
};

class DibujarPersonaje {
public:
  DibujarPersonaje();

  QPixmap dibujar(const DatosPersonaje &personaje, int escala) const;

  const QList<CoordenadaSprite> &opcionesPelo() const;
  const QList<CoordenadaSprite> &opcionesGorro() const;
  const QList<CoordenadaSprite> &opcionesPantalon() const;
  const QList<CoordenadaSprite> &opcionesRemera() const;

private:
  QPixmap hojaSpritesCuerpo;
  HojaPrenda pelo;
  HojaPrenda gorro;
  HojaPrenda pantalon;
  HojaPrenda remera;
};

#endif // DIBUJAR_PERSONAJE_H_
