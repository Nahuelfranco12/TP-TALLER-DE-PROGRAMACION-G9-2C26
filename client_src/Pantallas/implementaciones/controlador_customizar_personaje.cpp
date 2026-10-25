#include "controlador_customizar_personaje.h"
#include "ui_pantalla.h"

ControladorCustomizarPersonaje::ControladorCustomizarPersonaje(
    Ui::Pantalla &ui, Navegador &navegador, QObject *parent)
    : ControladorPagina(ui, navegador, parent) {
  connect(ui.botVolverPersonaje, &QPushButton::clicked, this,
          [this]() { this->navegador.volver(); });
}
