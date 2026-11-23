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
          [this]() {
            this->datosPartida.personaje = armarPersonajeElegido();
            intentarEntrarAJugar(this->servicio, this->datosPartida,
                                 this->ui.botonJugarCustomizarPersonaje);
          });
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

void ControladorCustomizarPersonaje::cambiarOpcionPrenda(int &indiceActual,
                                                         int cantidadOpciones,
                                                         int direccion) {
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
  conectarFlechasPrenda(ui.botonAnteriorGorroCustomizarPersonaje,
                        ui.botonSiguienteGorroCustomizarPersonaje, indiceGorro,
                        dibujar.opcionesGorro());
  conectarFlechasPrenda(ui.botonAnteriorPeloCustomizarPersonaje,
                        ui.botonSiguientePeloCustomizarPersonaje, indicePelo,
                        dibujar.opcionesPelo());
  conectarFlechasPrenda(ui.botonAnteriorRemeraCustomizarPersonaje,
                        ui.botonSiguienteRemeraCustomizarPersonaje,
                        indiceRemera, dibujar.opcionesRemera());
  conectarFlechasPrenda(ui.botonAnteriorPantalonCustomizarPersonaje,
                        ui.botonSiguientePantalonCustomizarPersonaje,
                        indicePantalon, dibujar.opcionesPantalon());
}

void ControladorCustomizarPersonaje::redibujarPrevisualizacionPersonaje() {
  ui.mostrarPersonaje->setPixmap(dibujar.dibujarPersonaje(
      armarPersonajeElegido(), ESCALA_PREVISUALIZACION));
}

void ControladorCustomizarPersonaje::conectarFlechasPrenda(
    QPushButton *anterior, QPushButton *siguiente, int &indice,
    const QList<CoordenadaSprite> &opciones) {
  connect(anterior, &QPushButton::clicked, this, [this, &indice, &opciones]() {
    cambiarOpcionPrenda(indice, static_cast<int>(opciones.size()),
                        DIRECCION_ANTERIOR);
  });
  connect(siguiente, &QPushButton::clicked, this, [this, &indice, &opciones]() {
    cambiarOpcionPrenda(indice, static_cast<int>(opciones.size()),
                        DIRECCION_SIGUIENTE);
  });
}
