#ifndef VISTA_RESPONSIVE_H_
#define VISTA_RESPONSIVE_H_

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

#endif // VISTA_RESPONSIVE_H_
