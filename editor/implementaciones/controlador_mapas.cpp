#include "controlador_mapas.h"

#include <QCursor>
#include <QDir>
#include <QFileDialog>
#include <QIcon>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QStringList>
#include <QToolTip>
#include <exception>
#include <stdexcept>
#include <vector>

#include "archivo_mapa.h"
#include "constantes_mapa.h"
#include "constantes_qt.h"
#include "sprites.h"
#include "ui_ventanaeditor.h"
#include "validacion_mapas.h"
#include "vista_zona.h"

ControladorMapas::ControladorMapas(QWidget &ventana, Ui::VentanaEditor &ui,
                                   Navegador &navegador, DatosEditor &datos,
                                   QObject *parent)
    : ControladorPaginaEditor(ventana, ui, navegador, parent), datos(datos) {
  ui.paletaAssets->setIconSize(QSize(TAMANIO_ICONO, TAMANIO_ICONO));
  ui.valorAnchoMapa->setRange(DIMENSION_MINIMA, DIMENSION_MAXIMA);
  ui.valorAltoMapa->setRange(DIMENSION_MINIMA, DIMENSION_MAXIMA);
  ui.valorNivelCaverna->setRange(PRIMER_NIVEL_CAVERNA,
                                 CANTIDAD_NIVELES_CAVERNA);
  ui.cajaNombreMapa->setMaxLength(MAX_LARGO_NOMBRE_MUNDO);
  ui.cajaNombreMapa->setPlaceholderText(NOMBRE_PREDETERMINADO_AYUDA);

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
      this->ui.cajaNombreMapa->setText(
          QString::fromStdString(this->datos.mapa.nombre));
      dibujarMapa();
      cambiarDeZona(zonaDe(this->ui.pestanaMapas->currentWidget()));
    }
  });
  connect(ui.botonExportarPM, &QPushButton::clicked, this,
          [this]() { exportar(); });

  ui.vistaGranja->setAlClickear([this](int x, int y, Qt::MouseButton boton) {
    clickEn(this->datos.mapa.granja, this->ui.vistaGranja, x, y, boton);
  });
  ui.vistaCaverna->setAlClickear([this](int x, int y, Qt::MouseButton boton) {
    clickEn(cavernaActual(), this->ui.vistaCaverna, x, y, boton);
  });
  ui.vistaPueblo->setAlClickear([this](int x, int y, Qt::MouseButton boton) {
    clickEn(this->datos.mapa.pueblo, this->ui.vistaPueblo, x, y, boton);
  });

  connect(ui.cajaNombreMapa, &QLineEdit::textChanged, this,
          [this](const QString &texto) {
            this->datos.mapa.nombre = texto.trimmed().toStdString();
          });

  cambiarDeZona(zonaDe(ui.pestanaMapas->currentWidget()));
}

void ControladorMapas::limpiarPagina() {
  ui.cajaNombreMapa->clear();
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
  mostrarDimensiones(dimensionesDe(datos.mapa, zona));
}

void ControladorMapas::cargarPaleta(Zona zona) {
  ui.paletaAssets->clear();
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
    QPixmap icono = imagenSpriteDe(info.rutaSprite, info.recorte, nombre,
                                   TAMANIO_ICONO, TAMANIO_ICONO);
    auto *item = new QListWidgetItem(QIcon(icono), nombre);
    item->setData(ROL_VALOR, static_cast<int>(info.elemento));
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

void ControladorMapas::mostrarDimensiones(Dimensiones dimensiones) {
  ui.valorAnchoMapa->setValue(dimensiones.ancho);
  ui.valorAltoMapa->setValue(dimensiones.alto);
}

void ControladorMapas::aplicarDimensiones() {
  Dimensiones nuevas{ui.valorAnchoMapa->value(), ui.valorAltoMapa->value()};
  try {
    redimensionar(datos.mapa, zonaActual, nuevas);
  } catch (const std::invalid_argument &error) {
    QMessageBox::warning(&ventana, TITULO_ERROR_DIMENSIONES,
                         QString::fromUtf8(error.what()));
    mostrarDimensiones(dimensionesDe(datos.mapa, zonaActual));
    return;
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
  if (!zona.existeCelda(x, y))
    return;
  if (boton == Qt::RightButton)
    zona.quitarEn(x, y);
  else if (boton == Qt::LeftButton)
    colocarSeleccionado(zona, vista, x, y);
  vista->mostrar(zona);
}

template <typename T>
void ControladorMapas::colocarSeleccionado(MapaZona<T> &zona, VistaZona *vista,
                                           int x, int y) {
  QListWidgetItem *item = ui.paletaAssets->currentItem();
  if (item == nullptr) {
    QToolTip::showText(QCursor::pos(), TEXTO_ELEGIR_ELEMENTO, vista);
    return;
  }
  int valor = item->data(ROL_VALOR).toInt();
  if (!zona.colocar(static_cast<T>(valor), x, y))
    QToolTip::showText(QCursor::pos(), TEXTO_NO_SE_PUEDE_COLOCAR, vista);
}

void ControladorMapas::exportar() {
  std::vector<std::string> errores = erroresDe(datos.mapa);
  if (!errores.empty()) {
    QStringList lineas;
    for (const auto &error : errores)
      lineas.append(QString::fromStdString(error));
    QMessageBox::warning(&ventana, VALIDACION_TEXTO_TITULO_MAPA_INVALIDO,
                         lineas.join('\n'));
    return;
  }

  QString ruta = QFileDialog::getSaveFileName(&ventana, TITULO_GUARDAR,
                                              QDir::homePath(), FILTRO_MAPAS);
  if (ruta.isEmpty())
    return;
  if (!ruta.endsWith(EXTENSION_MAPA))
    ruta += EXTENSION_MAPA;

  try {
    escribirMapa(datos.mapa, ruta.toStdString());
    QMessageBox::information(&ventana, TITULO_MAPA_GUARDADO,
                             TEXTO_MAPA_GUARDADO + ruta);
  } catch (const std::exception &error) {
    QMessageBox::warning(&ventana, TITULO_ERROR_GUARDAR,
                         QString::fromUtf8(error.what()));
  }
}
