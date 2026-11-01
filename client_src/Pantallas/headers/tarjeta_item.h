#ifndef TARJETA_ITEM_H
#define TARJETA_ITEM_H

#include <QFrame>
#include <QPixmap>
#include <QString>

#include "dtos_pantallas.h"

class TarjetaItem : public QFrame {
  Q_OBJECT

public:
  explicit TarjetaItem(const DatosTarjeta &datos, QWidget *parent = nullptr);

  void setSeleccionada(bool estado);
  QString getId() const;

signals:
  void clickeada(TarjetaItem *tarjeta);

protected:
  void mousePressEvent(QMouseEvent *event) override;

private:
  QString m_id;
};

#endif // TARJETA_ITEM_H
