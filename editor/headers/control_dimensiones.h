#ifndef CONTROL_DIMENSIONES_H_
#define CONTROL_DIMENSIONES_H_

#include <QObject>
#include <functional>

#include "mapa_editor.h"

class QPushButton;
class QSpinBox;

class ControlDimensiones : public QObject {
 public:
  ControlDimensiones(QSpinBox *ancho, QSpinBox *alto, QPushButton *aplicar,
                     QObject *parent = nullptr);

  void mostrar(const Dimensiones &dimensiones);
  void setAlAplicar(std::function<void(Dimensiones)> accion);

 private:
  QSpinBox *ancho;
  QSpinBox *alto;
  std::function<void(Dimensiones)> accionAlAplicar;
};

#endif  // CONTROL_DIMENSIONES_H_
