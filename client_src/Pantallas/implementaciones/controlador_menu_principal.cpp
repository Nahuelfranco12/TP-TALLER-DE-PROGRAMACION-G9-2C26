#include "controlador_menu_principal.h"
#include "ui_pantalla.h"

ControladorMenuPrincipal::ControladorMenuPrincipal(Ui::Pantalla &ui,
                                                   Navegador &navegador,
                                                   QObject *parent)
    : ControladorPagina(ui, navegador, parent) {
  connect(ui.botNuevaPartida, &QPushButton::clicked, this,
          [this]() { this->navegador.irA(this->ui.pageNuevaPartida); });
  connect(ui.botUnirsePartida, &QPushButton::clicked, this,
          [this]() { this->navegador.irA(this->ui.pageUnirsePartida); });
  connect(ui.botRetomarPartida, &QPushButton::clicked, this,
          [this]() { this->navegador.irA(this->ui.pageRetomarPartida); });
}

void ControladorMenuPrincipal::reiniciar() {}
void ControladorMenuPrincipal::validarFormulario() {}