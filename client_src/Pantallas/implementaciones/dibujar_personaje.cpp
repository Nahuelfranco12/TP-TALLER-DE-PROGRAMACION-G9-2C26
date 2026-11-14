#include "dibujar_personaje.h"
#include "constantes_pantallas.h"
#include <QColor>
#include <QImage>
#include <QPainter>

namespace {
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
  pintor.drawImage(QPoint(), original);
  pintor.end();
  return QPixmap::fromImage(coloreada);
}

const CoordenadaSprite &opcionValida(const QList<CoordenadaSprite> &opciones,
                                     int indice) {
  if (indice < 0 || indice >= opciones.size())
    return opciones[OPCION_POR_DEFECTO];
  return opciones[indice];
}
} // namespace

DibujarPersonaje::DibujarPersonaje()
    : pelos(COORDENADAS_PELOS), gorros(COORDENADAS_GORROS),
      pantalones(COORDENADAS_PANTALONES), remeras(COORDENADAS_REMERAS) {
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

  pintor.drawPixmap(cuerpo, hojaCuerpo.copy(X_CUERPO_EN_HOJA, Y_CUERPO_EN_HOJA,
                                            ANCHO_CUERPO, ALTO_CUERPO));
  pintor.drawPixmap(
      cuerpo,
      colorear(recortarCelda(hojaPantalon,
                             opcionValida(pantalones, personaje.ropa.pantalon),
                             ANCHO_PANTALON, ALTO_PANTALON),
               COLOR_PANTALON));
  pintor.drawPixmap(cuerpo + QPoint(X_REMERA_EN_CUERPO, Y_REMERA_EN_CUERPO),
                    recortarCelda(hojaRemera,
                                  opcionValida(remeras, personaje.ropa.remera),
                                  ANCHO_REMERA, ALTO_REMERA));
  pintor.drawPixmap(cuerpo, hojaCuerpo.copy(X_BRAZOS, Y_CUERPO_EN_HOJA,
                                            ANCHO_CUERPO, ALTO_CUERPO));
  pintor.drawPixmap(
      cuerpo,
      colorear(recortarCelda(hojaPelo, opcionValida(pelos, personaje.ropa.pelo),
                             ANCHO_PELO, ALTO_PELO),
               COLOR_PELO));
  pintor.drawPixmap(QPoint(),
                    recortarCelda(hojaGorro,
                                  opcionValida(gorros, personaje.ropa.gorro),
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
