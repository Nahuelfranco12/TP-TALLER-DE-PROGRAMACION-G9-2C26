#include "controlador_retomar_partida.h"
#include "partidas_estaticas.h"
#include "ui_pantalla.h"

ControladorRetomarPartida::ControladorRetomarPartida(Ui::Pantalla &ui,
                                                     Navegador &navegador,
                                                     QObject *parent)
    : ControladorPagina(ui, navegador, parent) {

  partidas = new ListaSeleccionable(ui.scrollAreaWidgetContents, this);

  cargarPartidas();

  ui.botJugarRP->setEnabled(false);

  // 4. Conectamos el botón Volver
  connect(ui.botVolverRP, &QPushButton::clicked, this, [this]() {
    reiniciar();
    this->navegador.volver();
  });

  // 5. Conectamos la validación a la lista de partidas
  partidas->setAlSeleccionar([this]() { validarFormulario(); });

  // 6. Conectamos el botón Siguiente para arrancar (o avanzar)
  connect(ui.botJugarRP, &QPushButton::clicked, this, [this]() {
    // Acá a futuro vas a agarrar el código de la partida y dárselo al protocolo
    // Por ahora lo dejamos listo para avanzar a donde necesites
  });
}

void ControladorRetomarPartida::validarFormulario() {
  bool tienePartida = partidas->haySeleccion();

  ui.botJugarRP->setEnabled(tienePartida);
}

void ControladorRetomarPartida::cargarPartidas() {
  QList<DatosTarjeta> tarjetas;
  for (const PartidaGuardada &partida : obtenerPartidasDePrueba()) {
    QString modo = partida.esMultiplayer ? "Multiplayer" : "Singleplayer";
    tarjetas.append(DatosTarjeta{partida.nombrePartida, partida.rutaImagen,
                                 partida.nombrePartida, partida.nombrePersonaje,
                                 modo, "Seleccionar"});
  }
  partidas->cargar(tarjetas);
}

void ControladorRetomarPartida::reiniciar() {
  partidas->deseleccionar();
  validarFormulario();
}