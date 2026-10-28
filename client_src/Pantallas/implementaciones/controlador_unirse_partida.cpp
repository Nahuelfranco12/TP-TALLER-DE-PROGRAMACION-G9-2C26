#include "controlador_unirse_partida.h"
#include "ui_pantalla.h"

ControladorUnirsePartida::ControladorUnirsePartida(Ui::Pantalla &ui,
                                                   Navegador &navegador,
                                                   QObject *parent)
    : ControladorPagina(ui, navegador, parent) {
  ui.botSiguienteUP->setEnabled(false);
  connect(ui.botVolverUP, &QPushButton::clicked, this, [this]() {
    reiniciar();
    this->navegador.volver();
  });
  connect(ui.campoCodigoPartida, &QLineEdit::textChanged, this,
          [this]() { validarFormulario(); });
  connect(ui.botSiguienteUP, &QPushButton::clicked, this,
          [this]() { this->navegador.irA(this->ui.pageCustomizarPersonaje); });
}

void ControladorUnirsePartida::validarFormulario() {
  bool tieneCodigo = !ui.campoCodigoPartida->text().trimmed().isEmpty();
  ui.botSiguienteUP->setEnabled(tieneCodigo);
}

void ControladorUnirsePartida::reiniciar() {
  ui.campoCodigoPartida->clear();
  validarFormulario();
}
