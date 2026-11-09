#include "sprites.h"

#include <QColor>
#include <QPainter>

#include "constantes.h"

namespace {
QPixmap placeholder(const QString &nombre, int lado) {
  QPixmap pixmap(lado, lado);
  pixmap.fill(COLOR_PLACEHOLDER);
  QPainter pintor(&pixmap);
  pintor.setPen(Qt::white);
  pintor.drawText(pixmap.rect(), Qt::AlignCenter, nombre.left(1));
  pintor.end();
  return pixmap;
}
}  // namespace

QPixmap spriteDe(const char *recurso, const Recorte &recorte,
                 const QString &nombre, int lado) {
  QPixmap hoja(QString::fromUtf8(recurso));
  if (hoja.isNull())
    return placeholder(nombre, lado);
  QPixmap imagen = hoja;
  if (recorte.ancho != 0)
    imagen = hoja.copy(recorte.x, recorte.y, recorte.ancho, recorte.alto);
  return imagen.scaled(lado, lado, Qt::KeepAspectRatio,
                       Qt::FastTransformation);
}
