#ifndef TARJETA_SELECCIONABLE_H_
#define TARJETA_SELECCIONABLE_H_

#include <QFrame>
#include <QString>

#include "dtos_pantallas.h"

class TarjetaSeleccionable : public QFrame {
  Q_OBJECT

public:
  explicit TarjetaSeleccionable(const DatosTarjeta &datos, QWidget *parent = nullptr);

  void setSeleccionada(bool estado);
  QString getId() const;

signals:
  void tarjetaClickeada(TarjetaSeleccionable *tarjeta);

protected:
  void mousePressEvent(QMouseEvent *event) override;

private:
  QString id;
};

#endif // TARJETA_SELECCIONABLE_H_
