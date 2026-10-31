#ifndef DIBUJAR_PERSONAJE_H
#define DIBUJAR_PERSONAJE_H

#include "dtos_pantallas.h"
#include <QList>
#include <QPixmap>

struct CoordenadaSprite {
  int fila;
  int columna;
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
  QList<CoordenadaSprite> pelos;
  QList<CoordenadaSprite> gorros;
  QList<CoordenadaSprite> pantalones;
  QList<CoordenadaSprite> remeras;

  QPixmap hojaCuerpo;
  QPixmap hojaPelo;
  QPixmap hojaGorro;
  QPixmap hojaPantalon;
  QPixmap hojaRemera;
};

#endif // DIBUJAR_PERSONAJE_H
