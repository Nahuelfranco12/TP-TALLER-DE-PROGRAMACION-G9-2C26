#include "controlador_nueva_partida.h"
#include "constantes_pantallas.h"
#include "ui_pantalla.h"

ControladorNuevaPartida::ControladorNuevaPartida(Ui::Pantalla &ui,
                                                 Navegador &navegador,
                                                 DatosPartida &datosPartida,
                                                 ServicioLobby &servicio,
                                                 QObject *parent)
    : ControladorPagina(ui, navegador, parent), datosPartida(datosPartida),
      servicio(servicio) {

  mundos = new ListaSeleccionable(ui.scrollAreaWidgetContents_2, this);

  cargarMundos();

  ui.botSiguiente->setEnabled(false);

  connect(ui.botVolver, &QPushButton::clicked, this, [this]() {
    limpiarPagina();
    this->navegador.volver();
  });

  connect(ui.campoNOmbrePartida, &QLineEdit::textChanged, this,
          [this]() { actualizarBotonAvanzar(); });

  mundos->setAlSeleccionar([this]() { actualizarBotonAvanzar(); });

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
  QList<DatosTarjeta> tarjetas;
  for (const MundoMock &mundo : servicio.mundos())
    tarjetas.append(DatosTarjeta{mundo.nombreMundo, QPixmap(mundo.rutaImagen),
                                 mundo.nombreMundo, "", "", ELEGIR_MAPA});
  mundos->cargar(tarjetas);
}

void ControladorNuevaPartida::limpiarPagina() {
  mundos->deseleccionar();
  ui.campoNOmbrePartida->clear();
  actualizarBotonAvanzar();
  datosPartida = DatosPartida{};
}
