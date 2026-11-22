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

  mundos = new ListaSeleccionable(ui.contenedorMundos, this);

  connect(&navegador, &NavegadorPaginas::seAbrioPagina, this,
          [this](QWidget *pagina) {
            if (pagina == this->ui.pageNuevaPartida && !mundosCargados)
              cargarMundos();
          });

  ui.botonSiguienteNuevaPartida->setEnabled(false);

  conectarVolver(ui.botonVolverNuevaPartida);

  connect(ui.campoNombrePartida, &QLineEdit::textChanged, this,
          [this]() { actualizarBotonAvanzar(); });

  mundos->setAlSeleccionar([this]() {
    actualizarBotonAvanzar();
  });

  connect(ui.botonSiguienteNuevaPartida, &QPushButton::clicked, this, [this]() {
    this->datosPartida.modo = ModoPartida::Nueva;
    this->datosPartida.nombrePartida =
        this->ui.campoNombrePartida->text().trimmed();
    this->datosPartida.idMundo = mundos->seleccionado();
    for (const MundoMock &mundo : datosMundos) {
      if (mundo.nombreMundo == this->datosPartida.idMundo) {
        this->datosPartida.rutaMapa = mundo.rutaMapa;
        break;
      }
    }
    this->navegador.irAPagina(this->ui.pageCustomizarPersonaje);
  });
}

void ControladorNuevaPartida::actualizarBotonAvanzar() {
  bool tieneNombre = !ui.campoNombrePartida->text().trimmed().isEmpty();
  bool tieneMundo = mundos->haySeleccion();
  ui.botonSiguienteNuevaPartida->setEnabled(tieneNombre && tieneMundo);
}

void ControladorNuevaPartida::cargarMundos() {
  datosMundos = servicio.mundosCrearPartida();

  QList<DatosTarjeta> tarjetas;
  for (const MundoMock &mundo : datosMundos) {
    tarjetas.append(DatosTarjeta{mundo.nombreMundo, QPixmap(),
                                 mundo.nombreMundo, QString(), QString(),
                                 TEXTO_ELEGIR_MUNDO});
  }

  mundos->cargar(tarjetas);
  mundosCargados = true;
}

void ControladorNuevaPartida::limpiarPagina() {
  mundos->deseleccionar();
  ui.campoNombrePartida->clear();
  actualizarBotonAvanzar();
  datosPartida = DatosPartida{};
}
