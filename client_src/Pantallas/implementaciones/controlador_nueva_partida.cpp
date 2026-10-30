#include "controlador_nueva_partida.h"
#include "constantes.h"
#include "partidas_estaticas.h"
#include "ui_pantalla.h"

ControladorNuevaPartida::ControladorNuevaPartida(Ui::Pantalla &ui,
                                                 Navegador &navegador,
                                                 DatosPartida &datosPartida,
                                                 QObject *parent)
    : ControladorPagina(ui, navegador, parent), datosPartida(datosPartida) {

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

  connect(ui.botSiguiente, &QPushButton::clicked, this, [this]() {
    this->datosPartida.nombrePartida =
        this->ui.campoNOmbrePartida->text().trimmed();
    this->datosPartida.idMundo = mundos->seleccionado();
    this->navegador.irA(this->ui.pageCustomizarPersonaje);
  });
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
                                 mundo.nombreMundo, "", "", ELEGIR_MAPA});
  mundos->cargar(tarjetas);
}

void ControladorNuevaPartida::reiniciar() {
  mundos->deseleccionar();
  ui.campoNOmbrePartida->clear();
  validarFormulario();
  datosPartida = DatosPartida{};
}
