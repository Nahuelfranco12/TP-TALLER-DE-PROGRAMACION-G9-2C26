#include "controlador_unirse_partida.h"
#include "ui_pantalla.h"
#include <QLineEdit>

ControladorUnirsePartida::ControladorUnirsePartida(QWidget &ventana,
                                                   Ui::Pantalla &ui,
                                                   NavegadorPaginas &navegador,
                                                   DatosPartida &datosPartida,
                                                   QObject *parent)
    : ControladorPagina(ventana, ui, navegador, parent),
      datosPartida(datosPartida) {
  ui.botonSiguienteUnirsePartida->setEnabled(false);
  conectarBotonVolver(ui.botonVolverUnirsePartida);
  connect(ui.campoCodigoPartida, &QLineEdit::textChanged, this,
          [this]() { actualizarEstadoBotonAvanzar(); });
  connect(ui.botonSiguienteUnirsePartida, &QPushButton::clicked, this,
          [this]() {
            this->datosPartida.modo = ModoPartida::Unirse;
            this->datosPartida.codigoUnirsePartida =
                this->ui.campoCodigoPartida->text().trimmed();
            this->navegador.irAPagina(this->ui.pageCustomizarPersonaje);
          });
}

void ControladorUnirsePartida::actualizarEstadoBotonAvanzar() {
  bool tieneCodigo = !ui.campoCodigoPartida->text().trimmed().isEmpty();
  ui.botonSiguienteUnirsePartida->setEnabled(tieneCodigo);
}

void ControladorUnirsePartida::reiniciarPagina() {
  ui.campoCodigoPartida->clear();
  actualizarEstadoBotonAvanzar();
  datosPartida = DatosPartida{};
}
