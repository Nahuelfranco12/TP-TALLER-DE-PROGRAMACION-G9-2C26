#include "controlador_retomar_partida.h"
#include "constantes.h"
#include "partidas_estaticas.h"
#include "ui_pantalla.h"

ControladorRetomarPartida::ControladorRetomarPartida(Ui::Pantalla &ui,
                                                     Navegador &navegador,
                                                     QObject *parent)
    : ControladorPagina(ui, navegador, parent) {

  partidas = new ListaSeleccionable(ui.scrollAreaWidgetContents, this);

  cargarPartidas();

  ui.botJugarRP->setEnabled(false);

  connect(ui.botVolverRP, &QPushButton::clicked, this, [this]() {
    reiniciar();
    this->navegador.volver();
  });

  partidas->setAlSeleccionar([this]() { validarFormulario(); });
}

void ControladorRetomarPartida::validarFormulario() {
  bool tienePartida = partidas->haySeleccion();

  ui.botJugarRP->setEnabled(tienePartida);
}

void ControladorRetomarPartida::cargarPartidas() {
  QList<DatosTarjeta> tarjetas;
  for (const PartidaGuardada &partida : obtenerPartidasDePrueba()) {
    QString modo =
        partida.esMultiplayer ? TEXTO_MULTIPLAYER : TEXTO_SINGLEPLAYER;
    tarjetas.append(DatosTarjeta{partida.nombrePartida, partida.rutaImagen,
                                 partida.nombrePartida, partida.nombrePersonaje,
                                 modo, TEXTO_SELECCIONAR});
  }
  partidas->cargar(tarjetas);
}

void ControladorRetomarPartida::reiniciar() {
  partidas->deseleccionar();
  validarFormulario();
}