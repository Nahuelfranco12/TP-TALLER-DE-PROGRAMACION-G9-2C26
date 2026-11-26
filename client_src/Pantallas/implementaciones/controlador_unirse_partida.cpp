#include "controlador_unirse_partida.h"
#include "ui_pantalla.h"
#include "constantes_pantallas.h"
#include <QLineEdit>
#include <QMessageBox>

ControladorUnirsePartida::ControladorUnirsePartida(
    QWidget &ventana, Ui::Pantalla &ui, NavegadorPaginas &navegador,
    DatosPartida &datosPartida, ServicioLobby &servicio, QObject *parent)
    : ControladorPagina(ventana, ui, navegador, parent),
      datosPartida(datosPartida), servicio(servicio) {
  ui.botonSiguienteUnirsePartida->setEnabled(false);
  conectarBotonVolver(ui.botonVolverUnirsePartida);
  connect(ui.campoCodigoPartida, &QLineEdit::textChanged, this,
          [this]() { actualizarEstadoBotonAvanzar(); });
  connect(ui.botonSiguienteUnirsePartida, &QPushButton::clicked, this,
          &ControladorUnirsePartida::avanzarACustomizarPersonaje);
}

void ControladorUnirsePartida::avanzarACustomizarPersonaje() {
  QString codigo = ui.campoCodigoPartida->text().trimmed();
  ResultadoLobby resultado = servicio.verificarCodigoPartida(codigo);
  if (!resultado.ok) {
    QMessageBox::warning(&ventana, TITULO_ERROR_JUGAR, resultado.mensajeError);
    return;
  }
  datosPartida.modo = ModoPartida::Unirse;
  datosPartida.codigoUnirsePartida = codigo;
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
