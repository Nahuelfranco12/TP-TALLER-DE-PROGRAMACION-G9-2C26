#include "controlador_retomar_partida.h"
#include "constantes_pantallas.h"
#include "dtos_pantallas.h"
#include "ui_pantalla.h"


ControladorRetomarPartida::ControladorRetomarPartida(
    Ui::Pantalla &ui, Navegador &navegador, DatosPartida &datosPartida,
    const DibujarPersonaje &dibujante, ServicioLobby &servicio, QObject *parent)
    : ControladorPagina(ui, navegador, parent), datosPartida(datosPartida),
      dibujante(dibujante), servicio(servicio) {

  partidas = new ListaSeleccionable(ui.scrollAreaWidgetContents, this);

  cargarPartidas();

  ui.botJugarRP->setEnabled(false);

  connect(ui.botVolverRP, &QPushButton::clicked, this, [this]() {
    limpiarPagina();
    this->navegador.volver();
  });

  partidas->setAlSeleccionar([this]() { actualizarBotonAvanzar(); });

  connect(ui.botJugarRP, &QPushButton::clicked, this, [this]() {
    this->datosPartida.modo = ModoPartida::Retomar;
    this->datosPartida.idRetomarPartida = partidas->seleccionado();
    intentarJugar(this->servicio, this->datosPartida, this->ui.botJugarRP);
  });
}

void ControladorRetomarPartida::actualizarBotonAvanzar() {
  bool tienePartida = partidas->haySeleccion();

  ui.botJugarRP->setEnabled(tienePartida);
}

void ControladorRetomarPartida::cargarPartidas() {
  QList<DatosTarjeta> tarjetas;
  for (const PartidaGuardada &partida : servicio.partidasGuardadas()) {
    QString modo = TEXTO_SINGLEPLAYER;
    if (partida.esMultiplayer)
      modo = TEXTO_MULTIPLAYER;
    tarjetas.append(DatosTarjeta{
        partida.id, dibujante.dibujar(partida.personaje, ESCALA_TARJETA),
        partida.nombrePartida, partida.personaje.nombre, modo,
        TEXTO_SELECCIONAR});
  }
  partidas->cargar(tarjetas);
}

void ControladorRetomarPartida::limpiarPagina() {
  partidas->deseleccionar();
  actualizarBotonAvanzar();
  datosPartida = DatosPartida{};
}
