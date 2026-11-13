#ifndef CONTROLADOR_PAGINA_EDITOR_H_
#define CONTROLADOR_PAGINA_EDITOR_H_

#include <QObject>

#include "navegador.h"

class QWidget;

namespace Ui {
class VentanaEditor;
}

class ControladorPaginaEditor : public QObject {
public:
  ControladorPaginaEditor(QWidget &ventana, Ui::VentanaEditor &ui, Navegador &navegador,
                          QObject *parent)
      : QObject(parent), ventana(ventana), ui(ui), navegador(navegador) {}
  virtual void limpiarPagina() = 0;

protected:
  QWidget &ventana;
  Ui::VentanaEditor &ui;
  Navegador &navegador;
};

#endif // CONTROLADOR_PAGINA_EDITOR_H_
