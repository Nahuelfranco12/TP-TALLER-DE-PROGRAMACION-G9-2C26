#include "controlador_customizar_personaje.h"
#include "constantes_pantallas.h"
#include "ui_pantalla.h"
#include <QLabel>
#include <QLineEdit>

ControladorCustomizarPersonaje::ControladorCustomizarPersonaje(
    QWidget &ventana, Ui::Pantalla &ui, Navegador &navegador,
    DatosPartida &datosPartida, const DibujarPersonaje &dibujar,
    ServicioLobby &servicio, QObject *parent)
    : ControladorPagina(ventana, ui, navegador, parent), dibujar(dibujar),
      datosPartida(datosPartida), servicio(servicio) {
  ui.botJugar->setEnabled(false);
  conectarVolver(ui.botVolverPersonaje);
  connect(ui.campoNombrePersonaje, &QLineEdit::textChanged, this,
          [this]() { actualizarBotonAvanzar(); });
  connect(ui.botJugar, &QPushButton::clicked, this, [this]() {
    this->datosPartida.personaje = personajeElegido();
    intentarJugar(this->servicio, this->datosPartida, this->ui.botJugar);
  });
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
  if (cantidadOpciones <= 0)
    return;
  indiceActual =
      (indiceActual + direccion + cantidadOpciones) % cantidadOpciones;
  actualizarPrevisualizacion();
}

DatosPersonaje ControladorCustomizarPersonaje::personajeElegido() const {
  return DatosPersonaje{ui.campoNombrePersonaje->text().trimmed(), indiceGorro,
                        indicePelo, indicePantalon, indiceRemera};
}

void ControladorCustomizarPersonaje::conectarBotonesFlechas() {
  conectarFlechas(ui.botAntGorro, ui.botSigGorro, indiceGorro,
                  dibujar.opcionesGorro());
  conectarFlechas(ui.botAntPelo, ui.botSigPelo, indicePelo,
                  dibujar.opcionesPelo());
  conectarFlechas(ui.botAntRemera, ui.botSigRemera, indiceRemera,
                  dibujar.opcionesRemera());
  conectarFlechas(ui.botAntPantalon, ui.botSigPantalon, indicePantalon,
                  dibujar.opcionesPantalon());
}

void ControladorCustomizarPersonaje::actualizarPrevisualizacion() {
  ui.mostrarPersonaje->setPixmap(
      dibujar.dibujar(personajeElegido(), ESCALA_PREVISUALIZACION));
}

void ControladorCustomizarPersonaje::conectarFlechas(
    QPushButton *anterior, QPushButton *siguiente, int &indice,
    const QList<CoordenadaSprite> &opciones) {
  connect(anterior, &QPushButton::clicked, this, [this, &indice, &opciones]() {
    cambiarOpcion(indice, static_cast<int>(opciones.size()),
                  DIRECCION_ANTERIOR);
  });
  connect(siguiente, &QPushButton::clicked, this, [this, &indice, &opciones]() {
    cambiarOpcion(indice, static_cast<int>(opciones.size()),
                  DIRECCION_SIGUIENTE);
  });
}
