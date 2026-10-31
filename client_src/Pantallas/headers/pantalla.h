#ifndef PANTALLA_H
#define PANTALLA_H

#include "datos_partida.h"
#include "dibujar_personaje.h"
#include <QMainWindow>

namespace Ui {
class Pantalla;
}

class Pantalla : public QMainWindow {
  Q_OBJECT

public:
  explicit Pantalla(QWidget *parent = nullptr);
  ~Pantalla() override;

private:
  Ui::Pantalla *ui;
  DatosPartida datosPartida;
  DibujarPersonaje dibujante;
};
#endif // PANTALLA_H
