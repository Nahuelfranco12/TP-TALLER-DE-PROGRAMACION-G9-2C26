#ifndef CONTROLADOR_PAGINA_EDITOR_H_
#define CONTROLADOR_PAGINA_EDITOR_H_

#include <QObject>

#include "navegador.h"

namespace Ui {
class VentanaEditor;
}

class ControladorPaginaEditor : public QObject {
 public:
  ControladorPaginaEditor(Ui::VentanaEditor &ui, Navegador &navegador,
                          QObject *parent)
      : QObject(parent), ui(ui), navegador(navegador) {}
  virtual void limpiarPagina() = 0;

 protected:
  Ui::VentanaEditor &ui;
  Navegador &navegador;
};

#endif  // CONTROLADOR_PAGINA_EDITOR_H_
