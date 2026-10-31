#include "controlador_customizar_personaje.h"
#include "constantes.h"
#include "ui_pantalla.h"
#include <QDebug>

namespace {
struct MedidasSprite {
  int anchoCelda;
  int altoCelda;
  int anchoRecorte;
  int altoRecorte;
  int offsetY;
  int escala;
};

const MedidasSprite MEDIDAS_GORRO{ANCHO_GORRO, ALTO_GORRO, ANCHO_GORRO,
                                  ALTO_GORRO,  0,          ESCALA_GORRO};
const MedidasSprite MEDIDAS_PELO{ANCHO_PELO,        ALTO_PELO, ANCHO_PELO,
                                 ALTO_RECORTE_PELO, 0,         ESCALA_PELO};
const MedidasSprite MEDIDAS_REMERA{ANCHO_REMERA, ALTO_REMERA, ANCHO_REMERA,
                                   ALTO_REMERA,  0,           ESCALA_REMERA};
const MedidasSprite MEDIDAS_PANTALON{ANCHO_PANTALON,    ALTO_PANTALON,
                                     ANCHO_PANTALON,    ALTO_RECORTE_PANTALON,
                                     OFFSET_Y_PANTALON, ESCALA_PANTALON};

QPixmap recortarSprite(const QPixmap &hoja, const CoordenadaSprite &coord,
                       const MedidasSprite &m) {
  int x = (coord.columna - BASE_COORDENADAS) * m.anchoCelda;
  int y = (coord.fila - BASE_COORDENADAS) * m.altoCelda + m.offsetY;
  return hoja.copy(x, y, m.anchoRecorte, m.altoRecorte)
      .scaled(m.anchoRecorte * m.escala, m.altoRecorte * m.escala,
              Qt::KeepAspectRatio, Qt::FastTransformation);
}
} // namespace

ControladorCustomizarPersonaje::ControladorCustomizarPersonaje(
    Ui::Pantalla &ui, Navegador &navegador, DatosPartida &datosPartida,
    QObject *parent)
    : ControladorPagina(ui, navegador, parent), datosPartida(datosPartida) {
  ui.botJugar->setEnabled(false);
  connect(ui.botVolverPersonaje, &QPushButton::clicked, this, [this]() {
    limpiarPagina();
    this->navegador.volver();
  });
  connect(ui.campoNombrePersonaje, &QLineEdit::textChanged, this,
          [this]() { actualizarBotonAvanzar(); });
  inicializarListas();
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
  connect(ui.botJugar, &QPushButton::clicked, this, [this]() {
    DatosPersonaje &p = this->datosPartida.personaje;
    p.nombre = this->ui.campoNombrePersonaje->text().trimmed();
    p.gorro = indiceGorro;
    p.pelo = indicePelo;
    p.remera = indiceRemera;
    p.pantalon = indicePantalon;

    qDebug() << "Modo:" << static_cast<int>(datosPartida.modo)
             << "| Código:" << datosPartida.codigoUnirsePartida
             << "| Partida:" << datosPartida.nombrePartida
             << "| Mundo:" << datosPartida.idMundo << "| Personaje:" << p.nombre
             << p.gorro << p.pelo << p.remera << p.pantalon;
  });
}

void ControladorCustomizarPersonaje::actualizarPrevisualizacion() {
  ui.mostrarGorro->setPixmap(
      recortarSprite(hojaGorro, opcionesGorro[indiceGorro], MEDIDAS_GORRO));
  ui.mostrarPelo->setPixmap(
      recortarSprite(hojaPelo, opcionesPelo[indicePelo], MEDIDAS_PELO));
  ui.mostrarRemera->setPixmap(
      recortarSprite(hojaRemera, opcionesRemera[indiceRemera], MEDIDAS_REMERA));
  ui.mostrarPantalon->setPixmap(recortarSprite(
      hojaPantalon, opcionesPantalon[indicePantalon], MEDIDAS_PANTALON));
}