#include "controlador_customizar_personaje.h"
#include "constantes.h"
#include "ui_pantalla.h"

ControladorCustomizarPersonaje::ControladorCustomizarPersonaje(
    Ui::Pantalla &ui, Navegador &navegador, QObject *parent)
    : ControladorPagina(ui, navegador, parent) {
  ui.botJugar->setEnabled(false);
  connect(ui.botVolverPersonaje, &QPushButton::clicked, this, [this]() {
    reiniciar();
    this->navegador.volver();
  });
  connect(ui.campoNombrePersonaje, &QLineEdit::textChanged, this,
          [this]() { validarFormulario(); });
  inicializarListas();
  conectarBotonesFlechas();
  actualizarPrevisualizacion();
}

void ControladorCustomizarPersonaje::validarFormulario() {
  bool tieneNombre = !ui.campoNombrePersonaje->text().trimmed().isEmpty();
  ui.botJugar->setEnabled(tieneNombre);
}

void ControladorCustomizarPersonaje::reiniciar() {
  ui.campoNombrePersonaje->clear();
  indicePelo = 0;
  indiceGorro = 0;
  indicePantalon = 0;
  indiceRemera = 0;
  actualizarPrevisualizacion();
  validarFormulario();
}

void ControladorCustomizarPersonaje::inicializarListas() {
  opcionesPelo = {{1, 10}, {1, 11}, {7, 2}, {13, 6}, {4, 6}, {5, 12}};
  opcionesGorro = {{13, 10}, {1, 5}, {13, 5}, {21, 2}, {41, 2}, {33, 4}};
  opcionesPantalon = {{1, 1}, {1, 25}, {1, 61}, {1, 73}};
  opcionesRemera = {{1, 10}, {5, 4}, {9, 5}, {5, 12}, {25, 9}};

  hojaPelo.load(TIPOS_PELO);
  hojaGorro.load(TIPOS_GORRO);
  hojaPantalon.load(TIPOS_PANTALON);
  hojaRemera.load(TIPOS_REMERA);
}

void ControladorCustomizarPersonaje::cambiarOpcion(int &indiceActual,
                                                   int cantidadOpciones,
                                                   int direccion) {
  indiceActual =
      (indiceActual + direccion + cantidadOpciones) % cantidadOpciones;
  actualizarPrevisualizacion();
}

void ControladorCustomizarPersonaje::conectarBotonesFlechas() {
  connect(ui.botAntGorro, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indiceGorro, opcionesGorro.size(), DIRECCION_ANTERIOR);
  });
  connect(ui.botSigGorro, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indiceGorro, opcionesGorro.size(), DIRECCION_SIGUIENTE);
  });

  connect(ui.botAntPelo, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indicePelo, opcionesPelo.size(), DIRECCION_ANTERIOR);
  });
  connect(ui.botSigPelo, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indicePelo, opcionesPelo.size(), DIRECCION_SIGUIENTE);
  });

  connect(ui.botAntRemera, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indiceRemera, opcionesRemera.size(), DIRECCION_ANTERIOR);
  });
  connect(ui.botSigRemera, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indiceRemera, opcionesRemera.size(), DIRECCION_SIGUIENTE);
  });

  connect(ui.botAntPantalon, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indicePantalon, opcionesPantalon.size(), DIRECCION_ANTERIOR);
  });
  connect(ui.botSigPantalon, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indicePantalon, opcionesPantalon.size(), DIRECCION_SIGUIENTE);
  });
}

void ControladorCustomizarPersonaje::actualizarPrevisualizacion() {

  int xGorro =
      (opcionesGorro[indiceGorro].columna - BASE_COORDENADAS) * ANCHO_GORRO;
  int yGorro =
      (opcionesGorro[indiceGorro].fila - BASE_COORDENADAS) * ALTO_GORRO;
  QPixmap spriteGorro =
      hojaGorro.copy(xGorro, yGorro, ANCHO_GORRO, ALTO_GORRO)
          .scaled(ANCHO_GORRO * ESCALA_GORRO, ALTO_GORRO * ESCALA_GORRO,
                  Qt::KeepAspectRatio, Qt::FastTransformation);

  int xPelo =
      (opcionesPelo[indicePelo].columna - BASE_COORDENADAS) * ANCHO_PELO;
  int yPelo = (opcionesPelo[indicePelo].fila - BASE_COORDENADAS) * ALTO_PELO;
  QPixmap spritePelo =
      hojaPelo.copy(xPelo, yPelo, ANCHO_PELO, ALTO_RECORTE_PELO)
          .scaled(ANCHO_PELO * ESCALA_PELO, ALTO_RECORTE_PELO * ESCALA_PELO,
                  Qt::KeepAspectRatio, Qt::FastTransformation);

  int xRemera =
      (opcionesRemera[indiceRemera].columna - BASE_COORDENADAS) * ANCHO_REMERA;
  int yRemera =
      (opcionesRemera[indiceRemera].fila - BASE_COORDENADAS) * ALTO_REMERA;
  QPixmap spriteRemera =
      hojaRemera.copy(xRemera, yRemera, ANCHO_REMERA, ALTO_REMERA)
          .scaled(ANCHO_REMERA * ESCALA_REMERA, ALTO_REMERA * ESCALA_REMERA,
                  Qt::KeepAspectRatio, Qt::FastTransformation);

  int xPantalon =
      (opcionesPantalon[indicePantalon].columna - BASE_COORDENADAS) *
      ANCHO_PANTALON;
  int yPantalon = (opcionesPantalon[indicePantalon].fila - BASE_COORDENADAS) *
                  ALTO_PANTALON;
  QPixmap spritePantalon =
      hojaPantalon
          .copy(xPantalon, yPantalon + OFFSET_Y_PANTALON, ANCHO_PANTALON,
                ALTO_RECORTE_PANTALON)
          .scaled(ANCHO_PANTALON * ESCALA_PANTALON,
                  ALTO_PANTALON * ESCALA_PANTALON, Qt::KeepAspectRatio,
                  Qt::FastTransformation);
  ui.mostrarGorro->setPixmap(spriteGorro);
  ui.mostrarPelo->setPixmap(spritePelo);
  ui.mostrarRemera->setPixmap(spriteRemera);
  ui.mostrarPantalon->setPixmap(spritePantalon);
}