#ifndef CONTROLADOR_PAGINA_H
#define CONTROLADOR_PAGINA_H

#include "navegador.h"
#include <QObject>

namespace Ui {
class Pantalla;
}

class ControladorPagina : public QObject {
public:
  ControladorPagina(Ui::Pantalla &ui, Navegador &navegador, QObject *parent)
      : QObject(parent), ui(ui), navegador(navegador) {}
  virtual void reiniciar() = 0;
  virtual void validarFormulario() = 0;

protected:
  Ui::Pantalla &ui;
  Navegador &navegador;
};

#endif // CONTROLADOR_PAGINA_H
