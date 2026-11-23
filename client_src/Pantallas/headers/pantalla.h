#ifndef PANTALLA_H_
#define PANTALLA_H_

#include "dibujar_personaje.h"
#include "dtos_pantallas.h"
#include <QMainWindow>
#include <memory>

class ServicioLobby;

namespace Ui {
class Pantalla;
}

class Pantalla : public QMainWindow {
  Q_OBJECT

public:
  explicit Pantalla(ServicioLobby &servicio, QWidget *parent = nullptr);
  ~Pantalla() override;

private:
  std::unique_ptr<Ui::Pantalla> ui;
  DatosPartida datosPartida;
  DibujarPersonaje dibujante;
};
#endif // PANTALLA_H_
