#include "vista_zona.h"

#include <QColor>
#include <QMouseEvent>
#include <QPen>
#include <utility>

VistaZona::VistaZona(QWidget *parent)
    : QGraphicsView(parent), escena(new QGraphicsScene(this)) {
  setScene(escena);
  setBackgroundBrush(Qt::black);
  setAlignment(Qt::AlignCenter);
}

void VistaZona::limpiar() { escena->clear(); }

QPixmap VistaZona::tileDe(Terreno terreno) const {
  const InfoElemento<Terreno> *info = infoTerreno(terreno);
  if (info == nullptr)
    return spriteDe("", Recorte{}, TEXTO_DESCONOCIDO, LADO_TILE, LADO_TILE);
  return spriteDe(info->recurso, info->recorte, QString::fromUtf8(info->nombre),
                  LADO_TILE, LADO_TILE);
}

void VistaZona::dibujarCuadricula(int ancho, int alto) {
  QPen lapiz(COLOR_CUADRICULA);
  lapiz.setCosmetic(true);
  for (int x = 0; x <= ancho; ++x)
    escena->addLine(x * LADO_TILE, 0, x * LADO_TILE, alto * LADO_TILE, lapiz);
  for (int y = 0; y <= alto; ++y)
    escena->addLine(0, y * LADO_TILE, ancho * LADO_TILE, y * LADO_TILE, lapiz);
}

void VistaZona::setAlClickear(
    std::function<void(int, int, Qt::MouseButton)> accion) {
  accionAlClickear = std::move(accion);
}

void VistaZona::mousePressEvent(QMouseEvent *evento) {
  QPointF punto = mapToScene(evento->position().toPoint());
  if (!accionAlClickear || !sceneRect().contains(punto))
    return;
  int x = static_cast<int>(punto.x()) / LADO_TILE;
  int y = static_cast<int>(punto.y()) / LADO_TILE;
  accionAlClickear(x, y, evento->button());
}
