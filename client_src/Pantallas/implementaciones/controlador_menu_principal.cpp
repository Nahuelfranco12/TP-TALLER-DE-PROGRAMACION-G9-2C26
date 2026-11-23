#include "controlador_menu_principal.h"
#include "ui_pantalla.h"

ControladorMenuPrincipal::ControladorMenuPrincipal(QWidget &ventana,
                                                   Ui::Pantalla &ui,
                                                   Navegador &navegador,
                                                   QObject *parent)
    : ControladorPagina(ventana, ui, navegador, parent) {
  connect(ui.botonNuevaPartidaMenuPrincipal, &QPushButton::clicked, this,
          [this]() { this->navegador.irA(this->ui.pageNuevaPartida); });
  connect(ui.botonUnirsePartidaMenuPrincipal, &QPushButton::clicked, this,
          [this]() { this->navegador.irA(this->ui.pageUnirsePartida); });
  connect(ui.botonRetomarPartidaMenuPrincipal, &QPushButton::clicked, this,
          [this]() { this->navegador.irA(this->ui.pageRetomarPartida); });
}

void ControladorMenuPrincipal::limpiarPagina() {}
void ControladorMenuPrincipal::actualizarBotonAvanzar() {}
