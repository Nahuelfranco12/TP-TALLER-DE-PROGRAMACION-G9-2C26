#include "controlador_nueva_partida.h"
#include "partidas_estaticas.h"
#include "ui_pantalla.h"

ControladorNuevaPartida::ControladorNuevaPartida(Ui::Pantalla &ui,
                                                 Navegador &navegador,
                                                 QObject *parent)
    : ControladorPagina(ui, navegador, parent) {

  mundos = new ListaSeleccionable(ui.scrollAreaWidgetContents_2, this);

  cargarMundos();

  ui.botSiguiente->setEnabled(false);

  connect(ui.botVolver, &QPushButton::clicked, this, [this]() {
    reiniciar();
    this->navegador.volver();
  });

  connect(ui.campoNOmbrePartida, &QLineEdit::textChanged, this,
          [this]() { validarFormulario(); });

  mundos->setAlSeleccionar([this]() { validarFormulario(); });

  connect(ui.botSiguiente, &QPushButton::clicked, this,
          [this]() { this->navegador.irA(this->ui.pageCustomizarPersonaje); });
}

void ControladorNuevaPartida::validarFormulario() {
  bool tieneNombre = !ui.campoNOmbrePartida->text().trimmed().isEmpty();
  bool tieneMundo = mundos->haySeleccion();
  ui.botSiguiente->setEnabled(tieneNombre && tieneMundo);
}

void ControladorNuevaPartida::cargarMundos() {
  QList<DatosTarjeta> tarjetas;
  for (const MundoMock &mundo : obtenerMundosDePrueba())
    tarjetas.append(DatosTarjeta{mundo.nombreMundo, mundo.rutaImagen,
                                 mundo.nombreMundo, "", "", "Elegir Mapa"});
  mundos->cargar(tarjetas);
}

void ControladorNuevaPartida::reiniciar() {
  mundos->deseleccionar();
  ui.campoNOmbrePartida->clear();
  validarFormulario();
}
