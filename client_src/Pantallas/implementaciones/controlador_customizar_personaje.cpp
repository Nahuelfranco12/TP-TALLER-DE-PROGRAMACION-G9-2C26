#include "controlador_customizar_personaje.h"
#include "constantes.h"
#include "ui_pantalla.h"
//#include <QDebug>

ControladorCustomizarPersonaje::ControladorCustomizarPersonaje(
    Ui::Pantalla &ui, Navegador &navegador, DatosPartida &datosPartida,
    const DibujarPersonaje &dibujar, ServicioLobby &servicio, QObject *parent)
    : ControladorPagina(ui, navegador, parent), dibujar(dibujar),
    datosPartida(datosPartida), servicio(servicio) {
  ui.botJugar->setEnabled(false);
  connect(ui.botVolverPersonaje, &QPushButton::clicked, this, [this]() {
    limpiarPagina();
    this->navegador.volver();
  });
  connect(ui.campoNombrePersonaje, &QLineEdit::textChanged, this,
          [this]() { actualizarBotonAvanzar(); });
  conectarBotonesFlechas();
  actualizarPrevisualizacion();
}

void ControladorCustomizarPersonaje::actualizarBotonAvanzar() {
  bool tieneNombre = !ui.campoNombrePersonaje->text().trimmed().isEmpty();
  ui.botJugar->setEnabled(tieneNombre);
}

void ControladorCustomizarPersonaje::limpiarPagina() {
  ui.campoNombrePersonaje->clear();
  indicePelo = 0;
  indiceGorro = 0;
  indicePantalon = 0;
  indiceRemera = 0;
  actualizarPrevisualizacion();
  actualizarBotonAvanzar();
  datosPartida.personaje = DatosPersonaje{};
}

void ControladorCustomizarPersonaje::cambiarOpcion(int &indiceActual,
                                                   int cantidadOpciones,
                                                   int direccion) {
  indiceActual =
      (indiceActual + direccion + cantidadOpciones) % cantidadOpciones;
  actualizarPrevisualizacion();
}

DatosPersonaje ControladorCustomizarPersonaje::personajeElegido() const {
  return DatosPersonaje{ui.campoNombrePersonaje->text().trimmed(), indiceGorro,
                        indicePelo, indicePantalon, indiceRemera};
}

void ControladorCustomizarPersonaje::conectarBotonesFlechas() {
  connect(ui.botAntGorro, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indiceGorro, dibujar.opcionesGorro().size(),
                  DIRECCION_ANTERIOR);
  });
  connect(ui.botSigGorro, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indiceGorro, dibujar.opcionesGorro().size(),
                  DIRECCION_SIGUIENTE);
  });

  connect(ui.botAntPelo, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indicePelo, dibujar.opcionesPelo().size(),
                  DIRECCION_ANTERIOR);
  });
  connect(ui.botSigPelo, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indicePelo, dibujar.opcionesPelo().size(),
                  DIRECCION_SIGUIENTE);
  });

  connect(ui.botAntRemera, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indiceRemera, dibujar.opcionesRemera().size(),
                  DIRECCION_ANTERIOR);
  });
  connect(ui.botSigRemera, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indiceRemera, dibujar.opcionesRemera().size(),
                  DIRECCION_SIGUIENTE);
  });

  connect(ui.botAntPantalon, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indicePantalon, dibujar.opcionesPantalon().size(),
                  DIRECCION_ANTERIOR);
  });
  connect(ui.botSigPantalon, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indicePantalon, dibujar.opcionesPantalon().size(),
                  DIRECCION_SIGUIENTE);
  });
  connect(ui.botJugar, &QPushButton::clicked, this, [this]() {
    this->datosPartida.personaje = personajeElegido();
    //const DatosPersonaje &p = this->datosPartida.personaje;
    intentarJugar(servicio, this->datosPartida, this->ui.botJugar);
  });
}

void ControladorCustomizarPersonaje::actualizarPrevisualizacion() {
  ui.mostrarPersonaje->setPixmap(
      dibujar.dibujar(personajeElegido(), ESCALA_PREVISUALIZACION));
}
