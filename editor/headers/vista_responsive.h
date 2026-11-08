#ifndef VISTA_RESPONSIVE_H
#define VISTA_RESPONSIVE_H

#include <QGraphicsView>

class QGraphicsProxyWidget;

class VistaEscalada : public QGraphicsView {
public:
  VistaEscalada(QWidget *contenido, const QSize &tamanioDisenio,
                QWidget *parent = nullptr);

protected:
  void resizeEvent(QResizeEvent *evento) override;

private:
  QGraphicsProxyWidget *proxy;
};

#endif // VISTA_RESPONSIVE_H
