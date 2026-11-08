#include <QColor>
#include <QIcon>
#include <QListWidgetItem>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <type_traits>

#include "controlador_mapas.h"
#include "ui_ventanaeditor.h"
#include "constantes.h"

namespace {
	QPixmap placeholder(const QString &nombre) {
	  QPixmap pixmap(TAMANIO_ICONO, TAMANIO_ICONO);
	  pixmap.fill(COLOR_PLACEHOLDER);
	  QPainter pintor(&pixmap);
	  pintor.setPen(Qt::white);
	  pintor.drawText(pixmap.rect(), Qt::AlignCenter, nombre.left(1));
	  pintor.end();
	  return pixmap;
	}

	QPixmap iconoDe(const char *recurso, const Recorte &recorte,
	                const QString &nombre) {
	  QPixmap hoja(QString::fromUtf8(recurso));
	  if (hoja.isNull())
	    return placeholder(nombre);
	  QPixmap imagen = hoja;
	  if (recorte.ancho != 0)
	    imagen = hoja.copy(recorte.x, recorte.y, recorte.ancho, recorte.alto);
	  return imagen.scaled(TAMANIO_ICONO, TAMANIO_ICONO, Qt::KeepAspectRatio,
	                       Qt::FastTransformation);
	}
}  // namespace  // namespace

ControladorMapas::ControladorMapas(Ui::VentanaEditor &ui, Navegador &navegador,
                                   DatosEditor &datos, QObject *parent)
    : ControladorPaginaEditor(ui, navegador, parent), datos(datos) {
  ui.paletaAssets->setIconSize(QSize(TAMANIO_ICONO, TAMANIO_ICONO));

  connect(ui.botonVolverPM, &QPushButton::clicked, this, [this]() {
    limpiarPagina();
    this->navegador.volver();
  });
  connect(ui.pestanaMapas, &QTabWidget::currentChanged, this, [this](int i) {
    cargarPaleta(zonaDe(this->ui.pestanaMapas->widget(i)));
  });
  cargarPaleta(zonaDe(ui.pestanaMapas->currentWidget()));
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
        QIcon(iconoDe(info.recurso, info.recorte, nombre)), nombre);
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
  ui.pestanaMapas->setCurrentIndex(0);
  datos = DatosEditor{};
}
