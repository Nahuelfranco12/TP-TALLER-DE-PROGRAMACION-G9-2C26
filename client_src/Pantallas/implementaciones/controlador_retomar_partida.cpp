#include "controlador_retomar_partida.h"
#include "constantes_pantallas.h"
#include "ui_pantalla.h"

ControladorRetomarPartida::ControladorRetomarPartida(
    QWidget &ventana, Ui::Pantalla &ui, NavegadorPaginas &navegador,
    DatosPartida &datosPartida, const DibujarPersonaje &dibujante,
    ServicioLobby &servicio, QObject *parent)
    : ControladorPagina(ventana, ui, navegador, parent),
      datosPartida(datosPartida), dibujante(dibujante), servicio(servicio) {

  listaPartidas = new ListaSeleccionable(ui.contenedorPartidas, this);

  pedirYMostrarPartidas();

  ui.botonJugarRetomarPartida->setEnabled(false);

  conectarBotonVolver(ui.botonVolverRetomarPartida);

  listaPartidas->setAccionAlSeleccionarTarjeta(
      [this]() { actualizarEstadoBotonAvanzar(); });

  connect(ui.botonJugarRetomarPartida, &QPushButton::clicked, this, [this]() {
    this->datosPartida.modo = ModoPartida::Retomar;
    this->datosPartida.idRetomarPartida =
        listaPartidas->idTarjetaSeleccionada();
    intentarEntrarAJugar(this->servicio, this->datosPartida,
                         this->ui.botonJugarRetomarPartida);
  });
}

void ControladorRetomarPartida::actualizarEstadoBotonAvanzar() {
  bool tienePartida = listaPartidas->hayTarjetaSeleccionada();

  ui.botonJugarRetomarPartida->setEnabled(tienePartida);
}

void ControladorRetomarPartida::pedirYMostrarPartidas() {
  QList<DatosTarjeta> tarjetas;
  for (const PartidaGuardada &partida : servicio.pedirPartidasGuardadas()) {
    QString modo = TEXTO_SINGLEPLAYER;
    if (partida.esMultiplayer)
      modo = TEXTO_MULTIPLAYER;
    tarjetas.append(DatosTarjeta{
        partida.id,
        dibujante.dibujarPersonaje(partida.personaje, ESCALA_TARJETA),
        partida.nombrePartida, partida.personaje.nombre, modo,
        TEXTO_SELECCIONAR});
  }
  listaPartidas->cargarTarjetas(tarjetas);
}

void ControladorRetomarPartida::reiniciarPagina() {
  listaPartidas->deseleccionarTarjeta();
  actualizarEstadoBotonAvanzar();
  datosPartida = DatosPartida{};
}
