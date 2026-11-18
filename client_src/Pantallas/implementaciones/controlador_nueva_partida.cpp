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

  mundos = new ListaSeleccionable(ui.contenedorMundos, this);

  cargarMundos();
  ocultarMapa();

  ui.botonSiguienteNuevaPartida->setEnabled(false);

  conectarVolver(ui.botonVolverNuevaPartida);

  connect(ui.campoNombrePartida, &QLineEdit::textChanged, this,
          [this]() { actualizarBotonAvanzar(); });

  mundos->setAlSeleccionar([this]() {
    actualizarBotonAvanzar();
    mostrarMapaSeleccionado();
  });

  connect(ui.botonSiguienteNuevaPartida, &QPushButton::clicked, this, [this]() {
    this->datosPartida.modo = ModoPartida::Nueva;
    this->datosPartida.nombrePartida =
        this->ui.campoNombrePartida->text().trimmed();
    this->datosPartida.idMundo = mundos->seleccionado();
    this->navegador.irA(this->ui.pageCustomizarPersonaje);
  });
}

void ControladorNuevaPartida::actualizarBotonAvanzar() {
  bool tieneNombre = !ui.campoNombrePartida->text().trimmed().isEmpty();
  bool tieneMundo = mundos->haySeleccion();
  ui.botonSiguienteNuevaPartida->setEnabled(tieneNombre && tieneMundo);
}

void ControladorNuevaPartida::cargarMundos() {
  datosMundos = servicio.mundos();
  QList<DatosTarjeta> tarjetas;
  for (const MundoMock &mundo : datosMundos)
    tarjetas.append(DatosTarjeta{mundo.nombreMundo, QPixmap(),
                                 mundo.nombreMundo, QString(), QString(),
                                 TEXTO_ELEGIR_MUNDO});
  mundos->cargar(tarjetas);
}

void ControladorNuevaPartida::mostrarMapaSeleccionado() {
  QString id = mundos->seleccionado();
  for (const MundoMock &mundo : datosMundos) {
    if (mundo.nombreMundo == id) {
      QPixmap mapa(mundo.rutaImagen);
      ui.infoMundo->setPixmap(
          mapa.scaled(ui.infoMundo->contentsRect().size(),
                      Qt::KeepAspectRatio, Qt::SmoothTransformation));
      ui.infoMundo->setVisible(true);
      return;
    }
  }
  ocultarMapa();
}

void ControladorNuevaPartida::ocultarMapa() {
  ui.infoMundo->clear();
  ui.infoMundo->setVisible(false);
}

void ControladorNuevaPartida::limpiarPagina() {
  mundos->deseleccionar();
  ocultarMapa();
  ui.campoNombrePartida->clear();
  actualizarBotonAvanzar();
  datosPartida = DatosPartida{};
}
