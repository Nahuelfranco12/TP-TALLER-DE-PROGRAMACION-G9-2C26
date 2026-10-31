#include "controlador_unirse_partida.h"
#include "ui_pantalla.h"

ControladorUnirsePartida::ControladorUnirsePartida(Ui::Pantalla &ui,
                                                   Navegador &navegador,
                                                   DatosPartida &datosPartida,
                                                   QObject *parent)
    : ControladorPagina(ui, navegador, parent), datosPartida(datosPartida) {
  ui.botSiguienteUP->setEnabled(false);
  connect(ui.botVolverUP, &QPushButton::clicked, this, [this]() {
    limpiarPagina();
    this->navegador.volver();
  });
  connect(ui.campoCodigoPartida, &QLineEdit::textChanged, this,
          [this]() { actualizarBotonAvanzar(); });
  connect(ui.botSiguienteUP, &QPushButton::clicked, this, [this]() {
    this->datosPartida.modo = ModoPartida::Unirse;
    this->datosPartida.codigoUnirsePartida =
        this->ui.campoCodigoPartida->text().trimmed();
    this->navegador.irA(this->ui.pageCustomizarPersonaje);
  });
}

void ControladorUnirsePartida::actualizarBotonAvanzar() {
  bool tieneCodigo = !ui.campoCodigoPartida->text().trimmed().isEmpty();
  ui.botSiguienteUP->setEnabled(tieneCodigo);
}

void ControladorUnirsePartida::limpiarPagina() {
  ui.campoCodigoPartida->clear();
  actualizarBotonAvanzar();
  datosPartida = DatosPartida{};
}

void ControladorUnirsePartida::validarFormulario() {
  bool tieneCodigo = !ui.campoCodigoPartida->text().trimmed().isEmpty();
  ui.botSiguienteUP->setEnabled(tieneCodigo);
}

void ControladorUnirsePartida::reiniciar() {
  ui.campoCodigoPartida->clear();
  validarFormulario();
}
