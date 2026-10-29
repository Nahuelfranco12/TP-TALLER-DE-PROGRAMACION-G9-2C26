#include "controlador_customizar_personaje.h"
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

  hojaPelo.load(":/ropas/assets/ropas/StardewValley_Character_Hairstyles.png");
  hojaGorro.load(":/ropas/assets/ropas/StardewValley_Character_Hats.png");
  hojaPantalon.load(":/ropas/assets/ropas/StardewValley_Character_Pants.png");
  hojaRemera.load(":/ropas/assets/ropas/StardewValley_Character_Shirts.png");
}

void ControladorCustomizarPersonaje::cambiarOpcion(int &indiceActual,
                                                   int cantidadOpciones,
                                                   int direccion) {
  indiceActual =
      (indiceActual + direccion + cantidadOpciones) % cantidadOpciones;
  actualizarPrevisualizacion();
}

void ControladorCustomizarPersonaje::conectarBotonesFlechas() {
  connect(ui.botAntGorro, &QPushButton::clicked, this,
          [this]() { cambiarOpcion(indiceGorro, opcionesGorro.size(), -1); });
  connect(ui.botSigGorro, &QPushButton::clicked, this,
          [this]() { cambiarOpcion(indiceGorro, opcionesGorro.size(), 1); });

  connect(ui.botAntPelo, &QPushButton::clicked, this,
          [this]() { cambiarOpcion(indicePelo, opcionesPelo.size(), -1); });
  connect(ui.botSigPelo, &QPushButton::clicked, this,
          [this]() { cambiarOpcion(indicePelo, opcionesPelo.size(), 1); });

  connect(ui.botAntRemera, &QPushButton::clicked, this,
          [this]() { cambiarOpcion(indiceRemera, opcionesRemera.size(), -1); });
  connect(ui.botSigRemera, &QPushButton::clicked, this,
          [this]() { cambiarOpcion(indiceRemera, opcionesRemera.size(), 1); });

  connect(ui.botAntPantalon, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indicePantalon, opcionesPantalon.size(), -1);
  });
  connect(ui.botSigPantalon, &QPushButton::clicked, this, [this]() {
    cambiarOpcion(indicePantalon, opcionesPantalon.size(), 1);
  });
}

void ControladorCustomizarPersonaje::actualizarPrevisualizacion() {
#define ESCALA_REMERA 5
#define ESCALA_PELO 3

#define ESCALA_GORRO 3
#define ESCALA_PANTALON 5

  int xGorro = (opcionesGorro[indiceGorro].columna - 1) * 20;
  int yGorro = (opcionesGorro[indiceGorro].fila - 1) * 20;
  QPixmap spriteGorro =
      hojaGorro.copy(xGorro, yGorro, 20, 20)
          .scaled(20 * ESCALA_GORRO, 20 * ESCALA_GORRO, Qt::KeepAspectRatio,
                  Qt::FastTransformation);

  int xPelo = (opcionesPelo[indicePelo].columna - 1) * 16;
  int yPelo = (opcionesPelo[indicePelo].fila - 1) * 32;
  QPixmap spritePelo = hojaPelo.copy(xPelo, yPelo, 16, 16)
                           .scaled(16 * ESCALA_PELO, 16 * ESCALA_PELO,
                                   Qt::KeepAspectRatio, Qt::FastTransformation);

  int xRemera = (opcionesRemera[indiceRemera].columna - 1) * 8;
  int yRemera = (opcionesRemera[indiceRemera].fila - 1) * 8;
  QPixmap spriteRemera =
      hojaRemera.copy(xRemera, yRemera, 8, 8)
          .scaled(8 * ESCALA_REMERA, 8 * ESCALA_REMERA, Qt::KeepAspectRatio,
                  Qt::FastTransformation);

  int xPantalon = (opcionesPantalon[indicePantalon].columna - 1) * 16;
  int yPantalon = (opcionesPantalon[indicePantalon].fila - 1) * 32;
  QPixmap spritePantalon =
      hojaPantalon.copy(xPantalon, yPantalon + 16, 16, 16)
          .scaled(16 * ESCALA_PANTALON, 16 * ESCALA_PANTALON,
                  Qt::KeepAspectRatio, Qt::FastTransformation);
  ui.mostrarGorro->setPixmap(spriteGorro);
  ui.mostrarPelo->setPixmap(spritePelo);
  ui.mostrarRemera->setPixmap(spriteRemera);
  ui.mostrarPantalon->setPixmap(spritePantalon);
}