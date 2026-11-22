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

void VistaZona::limpiarEscena() { escena->clear(); }

QPixmap VistaZona::cargarImagenDeTerreno(Terreno terreno) const {
  const InfoElemento<Terreno> *info = buscarInfoTerreno(terreno);
  if (info == nullptr)
    return cargarSpriteTratado("", Recorte{}, TEXTO_DESCONOCIDO, TAMANIO_CELDA_MAPA,
                          TAMANIO_CELDA_MAPA);
  return cargarSpriteTratado(info->rutaSprite, info->recorte,
                        QString::fromUtf8(info->nombre), TAMANIO_CELDA_MAPA,
                        TAMANIO_CELDA_MAPA);
}

void VistaZona::dibujarLineasCuadricula(int ancho, int alto) {
  QPen lapiz(COLOR_LINEAS_GRILLA);
  lapiz.setCosmetic(true);
  for (int x = 0; x <= ancho; ++x)
    escena->addLine(x * TAMANIO_CELDA_MAPA, 0, x * TAMANIO_CELDA_MAPA,
                    alto * TAMANIO_CELDA_MAPA, lapiz);
  for (int y = 0; y <= alto; ++y)
    escena->addLine(0, y * TAMANIO_CELDA_MAPA, ancho * TAMANIO_CELDA_MAPA,
                    y * TAMANIO_CELDA_MAPA, lapiz);
}

void VistaZona::setAccionAlClickearCelda(
    std::function<void(int, int, Qt::MouseButton)> accion) {
  accionAlClickear = std::move(accion);
}

void VistaZona::mousePressEvent(QMouseEvent *evento) {
  QPointF punto = mapToScene(evento->position().toPoint());
  if (!accionAlClickear || !sceneRect().contains(punto))
    return;
  int x = static_cast<int>(punto.x()) / TAMANIO_CELDA_MAPA;
  int y = static_cast<int>(punto.y()) / TAMANIO_CELDA_MAPA;
  accionAlClickear(x, y, evento->button());
}
