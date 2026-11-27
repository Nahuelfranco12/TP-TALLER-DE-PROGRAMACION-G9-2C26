#include "vista_responsive.h"

#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QtGlobal>

VistaEscalada::VistaEscalada(QWidget *contenido, const QSize &tamanioDisenio,
                             QWidget *parent)
    : QGraphicsView(parent) {
  QGraphicsScene *escena = new QGraphicsScene(this);
  contenido->setFixedSize(tamanioDisenio);
  escena->addWidget(contenido);
  escena->setSceneRect(QRectF(QPointF(0, 0), tamanioDisenio));
  setScene(escena);

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setFrameShape(QFrame::NoFrame);
  setBackgroundBrush(Qt::black);
  setAlignment(Qt::AlignCenter);
  setRenderHint(QPainter::TextAntialiasing);
}

void VistaEscalada::resizeEvent(QResizeEvent *evento) {
  QGraphicsView::resizeEvent(evento);
  const QRectF escena = sceneRect();
  const qreal escala = qMin(viewport()->width() / escena.width(),
                            viewport()->height() / escena.height());
  setTransform(QTransform::fromScale(escala, escala));
}
