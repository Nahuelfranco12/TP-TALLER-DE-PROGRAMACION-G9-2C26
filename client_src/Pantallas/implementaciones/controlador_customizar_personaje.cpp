#include "controlador_customizar_personaje.h"
#include "ui_pantalla.h"

ControladorCustomizarPersonaje::ControladorCustomizarPersonaje(
    Ui::Pantalla &ui, Navegador &navegador, QObject *parent)
    : ControladorPagina(ui, navegador, parent) {
  ui.botJugar->setEnabled(false);
  connect(ui.botVolverPersonaje, &QPushButton::clicked, this, [this]() {
    reiniciar();
    this->navegador.volver();
  });
  connect(ui.campoNombrePersonaje, &QLineEdit::textChanged, this,
          [this]() { validarFormulario(); });
}

void ControladorCustomizarPersonaje::validarFormulario() {
  bool tieneNombre = !ui.campoNombrePersonaje->text().trimmed().isEmpty();
  ui.botJugar->setEnabled(tieneNombre);
}

void ControladorCustomizarPersonaje::reiniciar() {
  ui.campoNombrePersonaje->clear();
  validarFormulario();
}