#include "controlador_unirse_partida.h"
#include "ui_pantalla.h"
#include <QLineEdit>

ControladorUnirsePartida::ControladorUnirsePartida(QWidget &ventana,
                                                   Ui::Pantalla &ui,
                                                   Navegador &navegador,
                                                   DatosPartida &datosPartida,
                                                   QObject *parent)
    : ControladorPagina(ventana, ui, navegador, parent),
      datosPartida(datosPartida) {
  ui.botonSiguienteUnirsePartida->setEnabled(false);
  conectarVolver(ui.botonVolverUnirsePartida);
  connect(ui.campoCodigoPartida, &QLineEdit::textChanged, this,
          [this]() { actualizarBotonAvanzar(); });
  connect(ui.botonSiguienteUnirsePartida, &QPushButton::clicked, this, [this]() {
    this->datosPartida.modo = ModoPartida::Unirse;
    this->datosPartida.codigoUnirsePartida =
        this->ui.campoCodigoPartida->text().trimmed();
    this->navegador.irA(this->ui.pageCustomizarPersonaje);
  });
}

void ControladorUnirsePartida::actualizarBotonAvanzar() {
  bool tieneCodigo = !ui.campoCodigoPartida->text().trimmed().isEmpty();
  ui.botonSiguienteUnirsePartida->setEnabled(tieneCodigo);
}

void ControladorUnirsePartida::limpiarPagina() {
  ui.campoCodigoPartida->clear();
  actualizarBotonAvanzar();
  datosPartida = DatosPartida{};
}
