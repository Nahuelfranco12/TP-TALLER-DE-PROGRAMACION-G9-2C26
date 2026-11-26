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
          &ControladorUnirsePartida::avanzarACustomizarPersonaje);
}

void ControladorUnirsePartida::avanzarACustomizarPersonaje() {
  datosPartida.modo = ModoPartida::Unirse;
  datosPartida.codigoUnirsePartida = ui.campoCodigoPartida->text().trimmed();
  navegador.irAPagina(ui.pageCustomizarPersonaje);
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
