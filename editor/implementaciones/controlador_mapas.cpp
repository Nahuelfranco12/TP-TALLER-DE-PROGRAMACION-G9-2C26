#include "controlador_mapas.h"

#include <QIcon>
#include <QListWidgetItem>
#include <QPushButton>
#include <QSpinBox>
#include <type_traits>
#include <vector>

#include "constantes.h"
#include "sprites.h"
#include "ui_ventanaeditor.h"
#include "vista_zona.h"

ControladorMapas::ControladorMapas(Ui::VentanaEditor &ui, Navegador &navegador,
                                   DatosEditor &datos, QObject *parent)
    : ControladorPaginaEditor(ui, navegador, parent), datos(datos) {
  ui.paletaAssets->setIconSize(QSize(TAMANIO_ICONO, TAMANIO_ICONO));
  ui.valorAnchoMapa->setRange(DIMENSION_MINIMA, DIMENSION_MAXIMA);
  ui.valorAltoMapa->setRange(DIMENSION_MINIMA, DIMENSION_MAXIMA);
  ui.valorNivelCaverna->setRange(PRIMER_NIVEL_CAVERNA,
                                 CANTIDAD_NIVELES_CAVERNA);

  connect(ui.botonVolverPM, &QPushButton::clicked, this, [this]() {
    limpiarPagina();
    this->navegador.volver();
  });
  connect(ui.botonAplicarPM, &QPushButton::clicked, this,
          [this]() { aplicarDimensiones(); });
  connect(ui.pestanaMapas, &QTabWidget::currentChanged, this, [this](int i) {
    cambiarDeZona(zonaDe(this->ui.pestanaMapas->widget(i)));
  });
  connect(ui.valorNivelCaverna, &QSpinBox::valueChanged, this,
          [this](int nivel) { cambiarDeNivel(nivel); });
  connect(&navegador, &Navegador::paginaAbierta, this, [this](QWidget *pagina) {
    if (pagina == this->ui.pageMapas) {
      dibujarMapa();
      cambiarDeZona(zonaDe(this->ui.pestanaMapas->currentWidget()));
    }
  });

  ui.vistaGranja->setAlClickear([this](int x, int y, Qt::MouseButton boton) {
    clickEn(this->datos.mapa.granja, this->ui.vistaGranja, x, y, boton);
  });
  ui.vistaCaverna->setAlClickear([this](int x, int y, Qt::MouseButton boton) {
    clickEn(cavernaActual(), this->ui.vistaCaverna, x, y, boton);
  });
  ui.vistaPueblo->setAlClickear([this](int x, int y, Qt::MouseButton boton) {
    clickEn(this->datos.mapa.pueblo, this->ui.vistaPueblo, x, y, boton);
  });

  cambiarDeZona(zonaDe(ui.pestanaMapas->currentWidget()));
}

void ControladorMapas::limpiarPagina() {
  datos = DatosEditor{};
  ui.valorNivelCaverna->setValue(PRIMER_NIVEL_CAVERNA);
  ui.pestanaMapas->setCurrentWidget(ui.tabGranja);
  ui.vistaGranja->limpiar();
  ui.vistaCaverna->limpiar();
  ui.vistaPueblo->limpiar();
}

Zona ControladorMapas::zonaDe(QWidget *pestania) const {
  if (pestania == ui.tabCaverna)
    return Zona::Caverna;
  if (pestania == ui.tabPueblo)
    return Zona::Pueblo;
  return Zona::Granja;
}

void ControladorMapas::cambiarDeZona(Zona zona) {
  zonaActual = zona;
  cargarPaleta(zona);
  mostrarDimensiones(dimensionesDe(zona));
}

void ControladorMapas::cargarPaleta(Zona zona) {
  ui.paletaAssets->clear();
  agregarAPaleta(terrenosDe(zona));
  switch (zona) {
  case Zona::Granja:
    agregarAPaleta(catalogoGranja());
    break;
  case Zona::Caverna:
    agregarAPaleta(catalogoCaverna());
    break;
  case Zona::Pueblo:
    agregarAPaleta(catalogoPueblo());
    break;
  }
}

template <typename T>
void ControladorMapas::agregarAPaleta(
    const std::vector<InfoElemento<T>> &elementos) {
  for (const auto &info : elementos) {
    QString nombre = QString::fromUtf8(info.nombre);
    QPixmap icono = spriteDe(info.recurso, info.recorte, nombre, TAMANIO_ICONO,
                             TAMANIO_ICONO);
    auto *item = new QListWidgetItem(QIcon(icono), nombre);
    item->setData(ROL_VALOR, static_cast<int>(info.elemento));
    item->setData(ROL_ES_TERRENO, std::is_same_v<T, Terreno>);
    ui.paletaAssets->addItem(item);
  }
}

MapaZona<ElementosCaverna> &ControladorMapas::cavernaActual() {
  return datos.mapa.nivelesCaverna[nivelCaverna];
}

void ControladorMapas::cambiarDeNivel(int nivel) {
  nivelCaverna = static_cast<std::size_t>(nivel - PRIMER_NIVEL_CAVERNA);
  ui.vistaCaverna->mostrar(cavernaActual());
}

Dimensiones ControladorMapas::dimensionesDe(Zona zona) const {
  switch (zona) {
  case Zona::Granja:
    return datos.mapa.granja.tamanio();
  case Zona::Caverna:
    return datos.mapa.nivelesCaverna.front().tamanio();
  case Zona::Pueblo:
    return datos.mapa.pueblo.tamanio();
  }
  return Dimensiones{};
}

void ControladorMapas::mostrarDimensiones(Dimensiones dimensiones) {
  ui.valorAnchoMapa->setValue(dimensiones.ancho);
  ui.valorAltoMapa->setValue(dimensiones.alto);
}

void ControladorMapas::aplicarDimensiones() {
  Dimensiones nuevas{ui.valorAnchoMapa->value(), ui.valorAltoMapa->value()};
  switch (zonaActual) {
  case Zona::Granja:
    datos.mapa.granja.redimensionar(nuevas);
    break;
  case Zona::Caverna:
    for (auto &nivel : datos.mapa.nivelesCaverna)
      nivel.redimensionar(nuevas);
    break;
  case Zona::Pueblo:
    datos.mapa.pueblo.redimensionar(nuevas);
    break;
  }
  dibujarMapa();
}

void ControladorMapas::dibujarMapa() {
  ui.vistaGranja->mostrar(datos.mapa.granja);
  ui.vistaCaverna->mostrar(cavernaActual());
  ui.vistaPueblo->mostrar(datos.mapa.pueblo);
}

template <typename T>
void ControladorMapas::clickEn(MapaZona<T> &zona, VistaZona *vista, int x,
                               int y, Qt::MouseButton boton) {
  if (!zona.contiene(x, y))
    return;
  if (boton == Qt::RightButton)
    zona.quitarEn(x, y);
  else if (boton == Qt::LeftButton)
    colocarSeleccionado(zona, x, y);
  vista->mostrar(zona);
}

template <typename T>
void ControladorMapas::colocarSeleccionado(MapaZona<T> &zona, int x, int y) {
  QListWidgetItem *item = ui.paletaAssets->currentItem();
  if (item == nullptr)
    return;
  int valor = item->data(ROL_VALOR).toInt();
  if (item->data(ROL_ES_TERRENO).toBool())
    zona.setTerreno(x, y, static_cast<Terreno>(valor));
  else
    zona.colocar(static_cast<T>(valor), x, y);
}
