#include "controlador_customizar_personaje.h"
#include "constantes_pantallas.h"
#include "ui_pantalla.h"
#include <QLabel>
#include <QLineEdit>

ControladorCustomizarPersonaje::ControladorCustomizarPersonaje(
    QWidget &ventana, Ui::Pantalla &ui, NavegadorPaginas &navegador,
    DatosPartida &datosPartida, const DibujarPersonaje &dibujar,
    ServicioLobby &servicio, QObject *parent)
    : ControladorPagina(ventana, ui, navegador, parent), dibujar(dibujar),
      datosPartida(datosPartida), servicio(servicio) {
  ui.botonJugarCustomizarPersonaje->setEnabled(false);
  conectarBotonVolver(ui.botonVolverCustomizarPersonaje);
  connect(ui.campoNombrePersonaje, &QLineEdit::textChanged, this,
          [this]() { actualizarEstadoBotonAvanzar(); });
  connect(ui.botonJugarCustomizarPersonaje, &QPushButton::clicked, this,
          &ControladorCustomizarPersonaje::jugarConPersonajeElegido);
  conectarFlechasDeTodasLasPrendas();
  redibujarPrevisualizacionPersonaje();
}

void ControladorCustomizarPersonaje::actualizarEstadoBotonAvanzar() {
  bool tieneNombre = !ui.campoNombrePersonaje->text().trimmed().isEmpty();
  ui.botonJugarCustomizarPersonaje->setEnabled(tieneNombre);
}

void ControladorCustomizarPersonaje::reiniciarPagina() {
  ui.campoNombrePersonaje->clear();
  indicePelo = 0;
  indiceGorro = 0;
  indicePantalon = 0;
  indiceRemera = 0;
  redibujarPrevisualizacionPersonaje();
  actualizarEstadoBotonAvanzar();
  datosPartida.personaje = DatosPersonaje{};
}

void ControladorCustomizarPersonaje::cambiarOpcionPrenda(
    int &indiceActual, const QList<CoordenadaSprite> &opciones,
    int direccion) {
  int cantidadOpciones = static_cast<int>(opciones.size());
  if (cantidadOpciones <= 0)
    return;
  indiceActual =
      (indiceActual + direccion + cantidadOpciones) % cantidadOpciones;
  redibujarPrevisualizacionPersonaje();
}

DatosPersonaje ControladorCustomizarPersonaje::armarPersonajeElegido() const {
  return DatosPersonaje{ui.campoNombrePersonaje->text().trimmed(), indiceGorro,
                        indicePelo, indicePantalon, indiceRemera};
}

void ControladorCustomizarPersonaje::conectarFlechasDeTodasLasPrendas() {
  connect(ui.botonAnteriorGorroCustomizarPersonaje, &QPushButton::clicked,
          this, &ControladorCustomizarPersonaje::gorroAnterior);
  connect(ui.botonSiguienteGorroCustomizarPersonaje, &QPushButton::clicked,
          this, &ControladorCustomizarPersonaje::gorroSiguiente);
  connect(ui.botonAnteriorPeloCustomizarPersonaje, &QPushButton::clicked,
          this, &ControladorCustomizarPersonaje::peloAnterior);
  connect(ui.botonSiguientePeloCustomizarPersonaje, &QPushButton::clicked,
          this, &ControladorCustomizarPersonaje::peloSiguiente);
  connect(ui.botonAnteriorRemeraCustomizarPersonaje, &QPushButton::clicked,
          this, &ControladorCustomizarPersonaje::remeraAnterior);
  connect(ui.botonSiguienteRemeraCustomizarPersonaje, &QPushButton::clicked,
          this, &ControladorCustomizarPersonaje::remeraSiguiente);
  connect(ui.botonAnteriorPantalonCustomizarPersonaje, &QPushButton::clicked,
          this, &ControladorCustomizarPersonaje::pantalonAnterior);
  connect(ui.botonSiguientePantalonCustomizarPersonaje, &QPushButton::clicked,
          this, &ControladorCustomizarPersonaje::pantalonSiguiente);
}

void ControladorCustomizarPersonaje::gorroAnterior() {
  cambiarOpcionPrenda(indiceGorro, dibujar.opcionesGorro(), DIRECCION_ANTERIOR);
}

void ControladorCustomizarPersonaje::gorroSiguiente() {
  cambiarOpcionPrenda(indiceGorro, dibujar.opcionesGorro(),
                      DIRECCION_SIGUIENTE);
}

void ControladorCustomizarPersonaje::peloAnterior() {
  cambiarOpcionPrenda(indicePelo, dibujar.opcionesPelo(), DIRECCION_ANTERIOR);
}

void ControladorCustomizarPersonaje::peloSiguiente() {
  cambiarOpcionPrenda(indicePelo, dibujar.opcionesPelo(), DIRECCION_SIGUIENTE);
}

void ControladorCustomizarPersonaje::remeraAnterior() {
  cambiarOpcionPrenda(indiceRemera, dibujar.opcionesRemera(),
                      DIRECCION_ANTERIOR);
}

void ControladorCustomizarPersonaje::remeraSiguiente() {
  cambiarOpcionPrenda(indiceRemera, dibujar.opcionesRemera(),
                      DIRECCION_SIGUIENTE);
}

void ControladorCustomizarPersonaje::pantalonAnterior() {
  cambiarOpcionPrenda(indicePantalon, dibujar.opcionesPantalon(),
                      DIRECCION_ANTERIOR);
}

void ControladorCustomizarPersonaje::pantalonSiguiente() {
  cambiarOpcionPrenda(indicePantalon, dibujar.opcionesPantalon(),
                      DIRECCION_SIGUIENTE);
}

void ControladorCustomizarPersonaje::jugarConPersonajeElegido() {
  datosPartida.personaje = armarPersonajeElegido();
  intentarEntrarAJugar(servicio, datosPartida,
                       ui.botonJugarCustomizarPersonaje);
}

void ControladorCustomizarPersonaje::redibujarPrevisualizacionPersonaje() {
  ui.mostrarPersonaje->setPixmap(dibujar.dibujarPersonaje(
      armarPersonajeElegido(), ESCALA_PREVISUALIZACION));
}
