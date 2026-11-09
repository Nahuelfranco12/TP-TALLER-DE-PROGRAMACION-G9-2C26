#include "control_dimensiones.h"

#include <QPushButton>
#include <QSpinBox>

#include "constantes.h"

ControlDimensiones::ControlDimensiones(QSpinBox *ancho, QSpinBox *alto,
                                       QPushButton *aplicar, QObject *parent)
    : QObject(parent), ancho(ancho), alto(alto) {
  ancho->setRange(DIMENSION_MINIMA, DIMENSION_MAXIMA);
  alto->setRange(DIMENSION_MINIMA, DIMENSION_MAXIMA);
  mostrar(Dimensiones{});

  connect(aplicar, &QPushButton::clicked, this, [this]() {
    if (accionAlAplicar)
      accionAlAplicar(Dimensiones{this->ancho->value(), this->alto->value()});
  });
}

void ControlDimensiones::mostrar(const Dimensiones &dimensiones) {
  ancho->setValue(dimensiones.ancho);
  alto->setValue(dimensiones.alto);
}

void ControlDimensiones::setAlAplicar(std::function<void(Dimensiones)> accion) {
  accionAlAplicar = std::move(accion);
}
