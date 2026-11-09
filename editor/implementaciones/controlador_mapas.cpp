#include "controlador_mapas.h"

#include <QIcon>
#include <QListWidgetItem>
#include <QPushButton>
#include <type_traits>

#include "constantes.h"
#include "sprites.h"
#include "ui_ventanaeditor.h"

ControladorMapas::ControladorMapas(Ui::VentanaEditor &ui, Navegador &navegador,
                                   DatosEditor &datos, QObject *parent)
    : ControladorPaginaEditor(ui, navegador, parent), datos(datos),
      dimensiones(new ControlDimensiones(ui.valorAnchoMapa, ui.valorAltoMapa,
                                         ui.botonAplicarPM, this)) {
  ui.paletaAssets->setIconSize(QSize(TAMANIO_ICONO, TAMANIO_ICONO));

  connect(ui.botonVolverPM, &QPushButton::clicked, this, [this]() {
    limpiarPagina();
    this->navegador.volver();
  });
  connect(ui.pestanaMapas, &QTabWidget::currentChanged, this, [this](int i) {
    cambiarDeZona(zonaDe(this->ui.pestanaMapas->widget(i)));
  });
  connect(&navegador, &Navegador::paginaAbierta, this, [this](QWidget *pagina) {
    if (pagina == this->ui.pageMapas) {
      dibujarMapa();
      cambiarDeZona(zonaDe(this->ui.pestanaMapas->currentWidget()));
    }
  });
  dimensiones->setAlAplicar(
      [this](Dimensiones nuevas) { redimensionarZona(zonaActual, nuevas); });

  cambiarDeZona(zonaDe(ui.pestanaMapas->currentWidget()));
}

Zona ControladorMapas::zonaDe(QWidget *pestania) const {
  if (pestania == ui.tabCaverna)
    return Zona::Caverna;
  if (pestania == ui.tabPueblo)
    return Zona::Pueblo;
  return Zona::Granja;
}

template <typename T>
void ControladorMapas::agregarAPaleta(
    const std::vector<InfoElemento<T>> &elementos) {
  for (const auto &info : elementos) {
    QString nombre = QString::fromUtf8(info.nombre);
    auto *item = new QListWidgetItem(
    	QIcon(spriteDe(info.recurso, info.recorte, nombre, TAMANIO_ICONO)),
            nombre);
    item->setData(ROL_VALOR, static_cast<int>(info.elemento));
    item->setData(ROL_ES_TERRENO, std::is_same_v<T, Terreno>);
    ui.paletaAssets->addItem(item);
  }
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

void ControladorMapas::limpiarPagina() {
  ui.vistaGranja->limpiar();
  ui.vistaCaverna->limpiar();
  ui.vistaPueblo->limpiar();
  ui.pestanaMapas->setCurrentIndex(0);
  datos = DatosEditor{};
}

void ControladorMapas::cambiarDeZona(Zona zona) {
  zonaActual = zona;
  cargarPaleta(zona);
  dimensiones->mostrar(dimensionesDe(zona));
}

Dimensiones ControladorMapas::dimensionesDe(Zona zona) const {
  if (!datos.mapa)
    return Dimensiones{};
  switch (zona) {
  case Zona::Granja:
    return datos.mapa->granja.tamanio();
  case Zona::Caverna:
    return datos.mapa->nivelesCaverna.front().tamanio();
  case Zona::Pueblo:
    return datos.mapa->pueblo.tamanio();
  }
  return Dimensiones{};
}

void ControladorMapas::redimensionarZona(Zona zona, Dimensiones nuevas) {
  if (!datos.mapa)
    return;
  switch (zona) {
  case Zona::Granja:
    datos.mapa->granja.redimensionar(nuevas);
    break;
  case Zona::Caverna:
    for (auto &nivel : datos.mapa->nivelesCaverna)
      nivel.redimensionar(nuevas);
    break;
  case Zona::Pueblo:
    datos.mapa->pueblo.redimensionar(nuevas);
    break;
  }
  dibujarMapa();
}

void ControladorMapas::dibujarMapa() {
  if (!datos.mapa)
    return;
  ui.vistaGranja->mostrar(datos.mapa->granja);
  ui.vistaCaverna->mostrar(datos.mapa->nivelesCaverna.front());
  ui.vistaPueblo->mostrar(datos.mapa->pueblo);
}
