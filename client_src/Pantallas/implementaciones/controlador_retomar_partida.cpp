#include "controlador_retomar_partida.h"
#include "constantes_pantallas.h"
#include "ui_pantalla.h"

ControladorRetomarPartida::ControladorRetomarPartida(
    QWidget &ventana, Ui::Pantalla &ui, Navegador &navegador,
    DatosPartida &datosPartida, const DibujarPersonaje &dibujante,
    ServicioLobby &servicio, QObject *parent)
    : ControladorPagina(ventana, ui, navegador, parent),
      datosPartida(datosPartida), dibujante(dibujante), servicio(servicio) {

  partidas = new ListaSeleccionable(ui.contenedorPartidas, this);

  cargarPartidas();

  ui.botonJugarRetomarPartida->setEnabled(false);

  conectarVolver(ui.botonVolverRetomarPartida);

  partidas->setAlSeleccionar([this]() { actualizarBotonAvanzar(); });

  connect(ui.botonJugarRetomarPartida, &QPushButton::clicked, this, [this]() {
    this->datosPartida.modo = ModoPartida::Retomar;
    this->datosPartida.idRetomarPartida = partidas->seleccionado();
    intentarJugar(this->servicio, this->datosPartida, this->ui.botonJugarRetomarPartida);
  });
}

void ControladorRetomarPartida::actualizarBotonAvanzar() {
  bool tienePartida = partidas->haySeleccion();

  ui.botonJugarRetomarPartida->setEnabled(tienePartida);
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
