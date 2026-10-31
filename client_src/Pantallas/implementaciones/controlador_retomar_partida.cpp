#include "controlador_retomar_partida.h"
#include "constantes.h"
#include "datos_partida.h"
#include "partidas_estaticas.h"
#include "ui_pantalla.h"

#include <QDebug>

ControladorRetomarPartida::ControladorRetomarPartida(
    Ui::Pantalla &ui, Navegador &navegador, DatosPartida &datosPartida,
    const DibujarPersonaje &dibujante, QObject *parent)
    : ControladorPagina(ui, navegador, parent), datosPartida(datosPartida),
      dibujante(dibujante) {

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

    qDebug() << "Modo:" << static_cast<int>(this->datosPartida.modo)
             << "| Partida guardada:" << this->datosPartida.idRetomarPartida;
  });
}

void ControladorRetomarPartida::actualizarBotonAvanzar() {
  bool tienePartida = partidas->haySeleccion();

  ui.botJugarRP->setEnabled(tienePartida);
}

void ControladorRetomarPartida::cargarPartidas() {
  QList<DatosTarjeta> tarjetas;
  for (const PartidaGuardada &partida : obtenerPartidasDePrueba()) {
    QString modo =
        partida.esMultiplayer ? TEXTO_MULTIPLAYER : TEXTO_SINGLEPLAYER;
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