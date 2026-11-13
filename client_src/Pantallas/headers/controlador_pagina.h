#ifndef CONTROLADOR_PAGINA_H
#define CONTROLADOR_PAGINA_H

#include "navegador.h"
#include "servicio_lobby.h"
#include <QObject>
#include <QPushButton>
#include <qpushbutton.h>

namespace Ui {
class Pantalla;
}

class ControladorPagina : public QObject {
public:
  ControladorPagina(QWidget &ventana, Ui::Pantalla &ui, Navegador &navegador, QObject *parent)
      : QObject(parent), ventana(ventana), ui(ui), navegador(navegador) {}
  virtual void limpiarPagina() = 0;
  virtual void actualizarBotonAvanzar() = 0;

protected:
  QWidget &ventana;
  Ui::Pantalla &ui;
  Navegador &navegador;
  void conectarVolver(QPushButton *boton);
  void intentarJugar(ServicioLobby &servicio, const DatosPartida &datos,
                     QPushButton *botonJugar);
};

#endif // CONTROLADOR_PAGINA_H
