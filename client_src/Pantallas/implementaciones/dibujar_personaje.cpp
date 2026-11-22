#include "dibujar_personaje.h"

#include <QColor>
#include <QImage>
#include <QPainter>
#include <QPoint>

#include "constantes_pantallas.h"

namespace {
QPixmap recortarCeldaDeHoja(const QPixmap &hoja, const CoordenadaSprite &coord,
                            int ancho, int alto) {
  int x = (coord.columna - BASE_COORDENADAS) * ancho;
  int y = (coord.fila - BASE_COORDENADAS) * alto;
  return hoja.copy(x, y, ancho, alto);
}

QPixmap colorearPieza(const QPixmap &pieza, const QColor &color) {
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

const CoordenadaSprite &
opcionValidaOPorDefecto(const QList<CoordenadaSprite> &opciones, int indice) {
  if (indice < 0 || indice >= opciones.size())
    return opciones[OPCION_POR_DEFECTO];
  return opciones[indice];
}
} // namespace

QPixmap HojaPrenda::recortarOpcion(int indice) const {
  return recortarCeldaDeHoja(hoja, opcionValidaOPorDefecto(opciones, indice),
                             ancho, alto);
}

DibujarPersonaje::DibujarPersonaje()
    : hojaSpritesCuerpo(RUTA_TIPOS_CUERPO), pelo{QPixmap(RUTA_TIPOS_PELO),
                                                 COORDENADAS_PELOS, ANCHO_PELO,
                                                 ALTO_PELO},
      gorro{QPixmap(RUTA_TIPOS_GORRO), COORDENADAS_GORROS, ANCHO_GORRO,
            ALTO_GORRO},
      pantalon{QPixmap(RUTA_TIPOS_PANTALON), COORDENADAS_PANTALONES,
               ANCHO_PANTALON, ALTO_PANTALON},
      remera{QPixmap(RUTA_TIPOS_REMERA), COORDENADAS_REMERAS, ANCHO_REMERA,
             ALTO_REMERA} {
  pantalon.hoja = colorearPieza(pantalon.hoja, COLOR_PANTALON);
  pelo.hoja = colorearPieza(pelo.hoja, COLOR_PELO);
}

QPixmap DibujarPersonaje::dibujarPersonaje(const DatosPersonaje &personaje,
                                           int escala) const {
  QPixmap lienzo(ANCHO_LIENZO, ALTO_LIENZO);
  lienzo.fill(Qt::transparent);

  QPainter pintor(&lienzo);
  const QPoint cuerpo(X_CUERPO_EN_LIENZO, Y_CUERPO_EN_LIENZO);

  pintor.drawPixmap(cuerpo,
                    hojaSpritesCuerpo.copy(X_CUERPO_EN_HOJA, Y_CUERPO_EN_HOJA,
                                           ANCHO_CUERPO, ALTO_CUERPO));
  pintor.drawPixmap(cuerpo, pantalon.recortarOpcion(personaje.ropa.pantalon));
  pintor.drawPixmap(cuerpo + QPoint(X_REMERA_EN_CUERPO, Y_REMERA_EN_CUERPO),
                    remera.recortarOpcion(personaje.ropa.remera));
  pintor.drawPixmap(cuerpo, hojaSpritesCuerpo.copy(X_BRAZOS, Y_CUERPO_EN_HOJA,
                                                   ANCHO_CUERPO, ALTO_CUERPO));
  pintor.drawPixmap(cuerpo, pelo.recortarOpcion(personaje.ropa.pelo));
  pintor.drawPixmap(QPoint(), gorro.recortarOpcion(personaje.ropa.gorro));
  pintor.end();

  return lienzo.scaled(ANCHO_LIENZO * escala, ALTO_LIENZO * escala,
                       Qt::KeepAspectRatio, Qt::FastTransformation);
}

const QList<CoordenadaSprite> &DibujarPersonaje::opcionesPelo() const {
  return pelo.opciones;
}

const QList<CoordenadaSprite> &DibujarPersonaje::opcionesGorro() const {
  return gorro.opciones;
}

const QList<CoordenadaSprite> &DibujarPersonaje::opcionesPantalon() const {
  return pantalon.opciones;
}

const QList<CoordenadaSprite> &DibujarPersonaje::opcionesRemera() const {
  return remera.opciones;
}
