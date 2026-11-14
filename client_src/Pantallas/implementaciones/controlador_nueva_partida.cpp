#include "controlador_nueva_partida.h"
#include "constantes_pantallas.h"
#include "ui_pantalla.h"
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>

ControladorNuevaPartida::ControladorNuevaPartida(
    QWidget &ventana, Ui::Pantalla &ui, Navegador &navegador,
    DatosPartida &datosPartida, ServicioLobby &servicio, QObject *parent)
    : ControladorPagina(ventana, ui, navegador, parent),
      datosPartida(datosPartida), servicio(servicio) {

  mundos = new ListaSeleccionable(ui.scrollAreaWidgetContents_2, this);

  cargarMundos();
  ocultarMapa();

  ui.botSiguiente->setEnabled(false);

  conectarVolver(ui.botVolver);

  connect(ui.campoNOmbrePartida, &QLineEdit::textChanged, this,
          [this]() { actualizarBotonAvanzar(); });

  mundos->setAlSeleccionar([this]() {
    actualizarBotonAvanzar();
    mostrarMapaSeleccionado();
  });

  connect(ui.botSiguiente, &QPushButton::clicked, this, [this]() {
    this->datosPartida.modo = ModoPartida::Nueva;
    this->datosPartida.nombrePartida =
        this->ui.campoNOmbrePartida->text().trimmed();
    this->datosPartida.idMundo = mundos->seleccionado();
    this->navegador.irA(this->ui.pageCustomizarPersonaje);
  });
}

void ControladorNuevaPartida::actualizarBotonAvanzar() {
  bool tieneNombre = !ui.campoNOmbrePartida->text().trimmed().isEmpty();
  bool tieneMundo = mundos->haySeleccion();
  ui.botSiguiente->setEnabled(tieneNombre && tieneMundo);
}

void ControladorNuevaPartida::cargarMundos() {
  datosMundos = servicio.mundos();
  QList<DatosTarjeta> tarjetas;
  for (const MundoMock &mundo : datosMundos)
    tarjetas.append(DatosTarjeta{mundo.nombreMundo, QPixmap(),
                                 mundo.nombreMundo, QString(), QString(),
                                 ELEGIR_MAPA});
  mundos->cargar(tarjetas);
}

void ControladorNuevaPartida::mostrarMapaSeleccionado() {
  QString id = mundos->seleccionado();
  for (const MundoMock &mundo : datosMundos) {
    if (mundo.nombreMundo == id) {
      QPixmap mapa(mundo.rutaImagen);
      ui.mapasAMostrar->setPixmap(
          mapa.scaled(ui.mapasAMostrar->contentsRect().size(),
                      Qt::KeepAspectRatio, Qt::SmoothTransformation));
      ui.mapasAMostrar->setVisible(true);
      return;
    }
  }
  ocultarMapa();
}

void ControladorNuevaPartida::ocultarMapa() {
  ui.mapasAMostrar->clear();
  ui.mapasAMostrar->setVisible(false);
}

void ControladorNuevaPartida::limpiarPagina() {
  mundos->deseleccionar();
  ocultarMapa();
  ui.campoNOmbrePartida->clear();
  actualizarBotonAvanzar();
  datosPartida = DatosPartida{};
}
