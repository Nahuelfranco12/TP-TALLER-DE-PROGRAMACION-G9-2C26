#include "dibujar_personaje.h"
#include "constantes.h"
#include <QImage>
#include <QPainter>

namespace {
const QColor COLOR_PANTALON(60, 90, 200);
const QColor COLOR_PELO(150, 80, 30);

QPixmap recortarCelda(const QPixmap &hoja, const CoordenadaSprite &coord,
                      int ancho, int alto) {
  int x = (coord.columna - BASE_COORDENADAS) * ancho;
  int y = (coord.fila - BASE_COORDENADAS) * alto;
  return hoja.copy(x, y, ancho, alto);
}

QPixmap colorear(const QPixmap &pieza, const QColor &color) {
  QImage original =
      pieza.toImage().convertToFormat(QImage::Format_ARGB32_Premultiplied);
  QImage coloreada = original;
  QPainter pintor(&coloreada);
  pintor.setCompositionMode(QPainter::CompositionMode_Multiply);
  pintor.fillRect(coloreada.rect(), color);
  pintor.setCompositionMode(QPainter::CompositionMode_DestinationIn);
  pintor.drawImage(0, 0, original);
  pintor.end();
  return QPixmap::fromImage(coloreada);
}
} // namespace

DibujarPersonaje::DibujarPersonaje()
    : pelos{{1, 10}, {1, 11}, {7, 2}, {13, 6}, {4, 6}, {4, 12}},
      gorros{{13, 10}, {1, 5}, {13, 5}, {21, 2}, {41, 2}, {33, 4}},
      pantalones{{1, 1}, {1, 25}, {1, 61}, {1, 73}}, remeras{{1, 10},
                                                             {5, 4},
                                                             {9, 5},
                                                             {5, 12},
                                                             {25, 9}} {
  hojaCuerpo.load(TIPOS_CUERPO);
  hojaPelo.load(TIPOS_PELO);
  hojaGorro.load(TIPOS_GORRO);
  hojaPantalon.load(TIPOS_PANTALON);
  hojaRemera.load(TIPOS_REMERA);
}

QPixmap DibujarPersonaje::dibujar(const DatosPersonaje &personaje,
                                  int escala) const {
  QPixmap lienzo(ANCHO_LIENZO, ALTO_LIENZO);
  lienzo.fill(Qt::transparent);

  QPainter pintor(&lienzo);
  const QPoint cuerpo(X_CUERPO_EN_LIENZO, Y_CUERPO_EN_LIENZO);

  pintor.drawPixmap(cuerpo, hojaCuerpo.copy(0, 0, ANCHO_CUERPO, ALTO_CUERPO));
  pintor.drawPixmap(
      cuerpo,
      colorear(recortarCelda(hojaPantalon, pantalones[personaje.ropa.pantalon],
                             ANCHO_PANTALON, ALTO_PANTALON),
               COLOR_PANTALON));
  pintor.drawPixmap(cuerpo + QPoint(X_REMERA_EN_CUERPO, Y_REMERA_EN_CUERPO),
                    recortarCelda(hojaRemera, remeras[personaje.ropa.remera],
                                  ANCHO_REMERA, ALTO_REMERA));
  pintor.drawPixmap(cuerpo,
                    hojaCuerpo.copy(X_BRAZOS, 0, ANCHO_CUERPO, ALTO_CUERPO));
  pintor.drawPixmap(cuerpo,
                    colorear(recortarCelda(hojaPelo, pelos[personaje.ropa.pelo],
                                           ANCHO_PELO, ALTO_PELO),
                             COLOR_PELO));
  pintor.drawPixmap(QPoint(0, 0),
                    recortarCelda(hojaGorro, gorros[personaje.ropa.gorro],
                                  ANCHO_GORRO, ALTO_GORRO));
  pintor.end();

  return lienzo.scaled(ANCHO_LIENZO * escala, ALTO_LIENZO * escala,
                       Qt::KeepAspectRatio, Qt::FastTransformation);
}

const QList<CoordenadaSprite> &DibujarPersonaje::opcionesPelo() const {
  return pelos;
}
const QList<CoordenadaSprite> &DibujarPersonaje::opcionesGorro() const {
  return gorros;
}
const QList<CoordenadaSprite> &DibujarPersonaje::opcionesPantalon() const {
  return pantalones;
}
const QList<CoordenadaSprite> &DibujarPersonaje::opcionesRemera() const {
  return remeras;
}
