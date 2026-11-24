#include "controlador_nueva_partida.h"
#include "constantes_pantallas.h"
#include "ui_pantalla.h"
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>

ControladorNuevaPartida::ControladorNuevaPartida(
    QWidget &ventana, Ui::Pantalla &ui, NavegadorPaginas &navegador,
    DatosPartida &datosPartida, ServicioLobby &servicio, QObject *parent)
    : ControladorPagina(ventana, ui, navegador, parent),
      datosPartida(datosPartida), servicio(servicio) {

  listaMundos = new ListaSeleccionable(ui.contenedorMundos, this);

  connect(&navegador, &NavegadorPaginas::seAbrioPagina, this,
          [this](QWidget *pagina) {
            if (pagina == this->ui.pageNuevaPartida && !mundosCargados)
              pedirYMostrarMundos();
          });

  ui.botonSiguienteNuevaPartida->setEnabled(false);

  conectarBotonVolver(ui.botonVolverNuevaPartida);

  connect(ui.campoNombrePartida, &QLineEdit::textChanged, this,
          [this]() { actualizarEstadoBotonAvanzar(); });

  listaMundos->setAccionAlSeleccionarTarjeta(
      [this]() { actualizarEstadoBotonAvanzar(); });

  connect(ui.botonSiguienteNuevaPartida, &QPushButton::clicked, this, [this]() {
    this->datosPartida.modo = ModoPartida::Nueva;
    this->datosPartida.nombrePartida =
        this->ui.campoNombrePartida->text().trimmed();
    this->datosPartida.idMundo = listaMundos->idTarjetaSeleccionada();
    for (const MundoMock &mundo : mundosDisponibles) {
      if (mundo.nombreMundo == this->datosPartida.idMundo) {
        this->datosPartida.rutaMapa = mundo.rutaMapa;
        break;
      }
    }
    this->navegador.irAPagina(this->ui.pageCustomizarPersonaje);
  });
}

void ControladorNuevaPartida::actualizarEstadoBotonAvanzar() {
  bool tieneNombre = !ui.campoNombrePartida->text().trimmed().isEmpty();
  bool tieneMundo = listaMundos->hayTarjetaSeleccionada();
  ui.botonSiguienteNuevaPartida->setEnabled(tieneNombre && tieneMundo);
}

void ControladorNuevaPartida::pedirYMostrarMundos() {
  mundosDisponibles = servicio.pedirMundosDisponibles();

  QList<DatosTarjeta> tarjetas;
  for (const MundoMock &mundo : mundosDisponibles) {
    tarjetas.append(DatosTarjeta{mundo.nombreMundo, QPixmap(),
                                 mundo.nombreMundo, QString(), QString(),
                                 TEXTO_ELEGIR_MUNDO});
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
