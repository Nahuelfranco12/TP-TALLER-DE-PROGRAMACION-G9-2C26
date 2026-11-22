#include "sprites.h"

#include <QColor>
#include <QPainter>

#include "constantes_qt.h"

namespace {
QPixmap placeholder(const QString &nombre, int ancho, int alto) {
  QPixmap pixmap(ancho, alto);
  pixmap.fill(COLOR_GRIS_FALTA_ASSET);
  QPainter pintor(&pixmap);
  pintor.setPen(Qt::white);
  pintor.drawText(pixmap.rect(), Qt::AlignCenter, nombre.left(1));
  pintor.end();
  return pixmap;
}
} // namespace

QPixmap cargarSpriteTratado(const char *rutaSprite, const Recorte &recorte,
                       const QString &nombre, int ancho, int alto) {
  QPixmap hoja(QString::fromUtf8(rutaSprite));
  if (hoja.isNull())
    return placeholder(nombre, ancho, alto);
  QPixmap imagen = hoja;
  if (recorte.ancho != 0)
    imagen = hoja.copy(recorte.x, recorte.y, recorte.ancho, recorte.alto);
  return imagen.scaled(ancho, alto, Qt::KeepAspectRatio,
                       Qt::FastTransformation);
}
