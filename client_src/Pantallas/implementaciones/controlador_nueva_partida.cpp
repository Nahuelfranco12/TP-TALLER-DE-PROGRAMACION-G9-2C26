#include "controlador_nueva_partida.h"
#include "constantes_pantallas.h"
#include "ui_pantalla.h"
#include <QLineEdit>
#include <QPixmap>

ControladorNuevaPartida::ControladorNuevaPartida(
    QWidget &ventana, Ui::Pantalla &ui, NavegadorPaginas &navegador,
    DatosPartida &datosPartida, ServicioLobby &servicio, QObject *parent)
    : ControladorPagina(ventana, ui, navegador, parent),
      datosPartida(datosPartida), servicio(servicio) {

  listaMundos = new ListaSeleccionable(ui.contenedorMundos, this);

  connect(&navegador, &NavegadorPaginas::seAbrioPagina, this,
          &ControladorNuevaPartida::alAbrirPagina);

  ui.botonSiguienteNuevaPartida->setEnabled(false);

  conectarBotonVolver(ui.botonVolverNuevaPartida);

  connect(ui.campoNombrePartida, &QLineEdit::textChanged, this,
          [this]() { actualizarEstadoBotonAvanzar(); });

  listaMundos->setAccionAlSeleccionarTarjeta(
      [this]() { actualizarEstadoBotonAvanzar(); });

  connect(ui.botonSiguienteNuevaPartida, &QPushButton::clicked, this,
          &ControladorNuevaPartida::avanzarACustomizarPersonaje);
}

void ControladorNuevaPartida::alAbrirPagina(QWidget *pagina) {
  if (pagina == ui.pageNuevaPartida && !mundosCargados)
    pedirYMostrarMundos();
}

void ControladorNuevaPartida::avanzarACustomizarPersonaje() {
  datosPartida.modo = ModoPartida::Nueva;
  datosPartida.nombrePartida = ui.campoNombrePartida->text().trimmed();
  datosPartida.rutaMapa = listaMundos->idTarjetaSeleccionada();
  navegador.irAPagina(ui.pageCustomizarPersonaje);
}

void ControladorNuevaPartida::actualizarEstadoBotonAvanzar() {
  bool tieneNombre = !ui.campoNombrePartida->text().trimmed().isEmpty();
  bool tieneMundo = listaMundos->hayTarjetaSeleccionada();
  ui.botonSiguienteNuevaPartida->setEnabled(tieneNombre && tieneMundo);
}

void ControladorNuevaPartida::pedirYMostrarMundos() {
  QList<DatosTarjeta> tarjetas;
  for (const MundoMock &mundo : servicio.pedirMundosDisponibles()) {
    tarjetas.append(DatosTarjeta{mundo.rutaMapa, QPixmap(), mundo.nombreMundo,
                                 QString(), QString(), TEXTO_ELEGIR_MUNDO});
  }
  listaMundos->cargarTarjetas(tarjetas);
  mundosCargados = true;
}

void ControladorNuevaPartida::reiniciarPagina() {
  listaMundos->deseleccionarTarjeta();
  ui.campoNombrePartida->clear();
  actualizarEstadoBotonAvanzar();
  datosPartida = DatosPartida{};
}
