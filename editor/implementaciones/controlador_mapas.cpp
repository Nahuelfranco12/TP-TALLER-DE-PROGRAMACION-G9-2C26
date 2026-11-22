#include "controlador_mapas.h"

#include <QCursor>
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
                                   NavegadorPaginas &navegador,
                                   DatosEditor &datos, QObject *parent)
    : ControladorPaginaEditor(ventana, ui, navegador, parent), datos(datos) {
  ui.paletaAssets->setIconSize(QSize(TAMANIO_ICONO, TAMANIO_ICONO));
  ui.valorAnchoMapa->setRange(DIMENSION_MINIMA, DIMENSION_MAXIMA);
  ui.valorAltoMapa->setRange(DIMENSION_MINIMA, DIMENSION_MAXIMA);
  ui.valorNivelCaverna->setRange(PRIMER_NIVEL_CAVERNA,
                                 CANTIDAD_NIVELES_CAVERNA);
  ui.campoNombreMundo->setMaxLength(MAX_LARGO_NOMBRE_MUNDO);
  ui.campoNombreMundo->setPlaceholderText(TEXTO_AYUDA_NOMBRE_MUNDO);

  connect(ui.botonVolverMapas, &QPushButton::clicked, this, [this]() {
    reiniciarPaginaMapas();
    this->navegador.volverPaginaAnterior();
  });
  connect(ui.botonAplicarMapas, &QPushButton::clicked, this,
          [this]() { redimensionarZonaActual(); });
  connect(ui.pestaniaMapas, &QTabWidget::currentChanged, this, [this](int i) {
    cambiarZonaActual(zonaDePestania(this->ui.pestaniaMapas->widget(i)));
  });
  connect(ui.valorNivelCaverna, &QSpinBox::valueChanged, this,
          [this](int nivel) { cambiarNivelCaverna(nivel); });
  connect(&navegador, &NavegadorPaginas::seAbrioPagina, this,
          [this](QWidget *pagina) {
            if (pagina == this->ui.pageMapas) {
              this->ui.campoNombreMundo->setText(
                  QString::fromStdString(this->datos.mapa.nombre));
              dibujarTodasLasZonas();
              cambiarZonaActual(
                  zonaDePestania(this->ui.pestaniaMapas->currentWidget()));
            }
          });
  connect(ui.botonExportarMapas, &QPushButton::clicked, this,
          [this]() { validarYExportarMapa(); });

  ui.vistaGranja->setAccionAlClickearCelda(
      [this](int x, int y, Qt::MouseButton boton) {
        manejarClickEnCelda(this->datos.mapa.granja, this->ui.vistaGranja, x, y,
                            boton);
      });
  ui.vistaCaverna->setAccionAlClickearCelda(
      [this](int x, int y, Qt::MouseButton boton) {
        manejarClickEnCelda(nivelCavernaActual(), this->ui.vistaCaverna, x, y,
                            boton);
      });
  ui.vistaPueblo->setAccionAlClickearCelda(
      [this](int x, int y, Qt::MouseButton boton) {
        manejarClickEnCelda(this->datos.mapa.pueblo, this->ui.vistaPueblo, x, y,
                            boton);
      });

  connect(ui.campoNombreMundo, &QLineEdit::textChanged, this,
          [this](const QString &texto) {
            this->datos.mapa.nombre = texto.trimmed().toStdString();
          });

  cambiarZonaActual(zonaDePestania(ui.pestaniaMapas->currentWidget()));
}

void ControladorMapas::reiniciarPaginaMapas() {
  ui.campoNombreMundo->clear();
  ui.valorNivelCaverna->setValue(PRIMER_NIVEL_CAVERNA);
  ui.pestaniaMapas->setCurrentWidget(ui.tabGranja);
  ui.vistaGranja->limpiarEscena();
  ui.vistaCaverna->limpiarEscena();
  ui.vistaPueblo->limpiarEscena();
}

Zona ControladorMapas::zonaDePestania(QWidget *pestania) const {
  if (pestania == ui.tabCaverna)
    return Zona::Caverna;
  if (pestania == ui.tabPueblo)
    return Zona::Pueblo;
  return Zona::Granja;
}

void ControladorMapas::cambiarZonaActual(Zona zona) {
  zonaActual = zona;
  cargarPaletaDeZona(zona);
  mostrarDimensionesEnCampos(dimensionesDeZona(datos.mapa, zona));
}

void ControladorMapas::cargarPaletaDeZona(Zona zona) {
  ui.paletaAssets->clear();
  switch (zona) {
  case Zona::Granja:
    agregarElementosAPaleta(elementosParaColocarEnGranja());
    break;
  case Zona::Caverna:
    agregarElementosAPaleta(elementosParaColocarEnCaverna());
    break;
  case Zona::Pueblo:
    agregarElementosAPaleta(elementosParaColocarEnPueblo());
    break;
  }
}

template <typename T>
void ControladorMapas::agregarElementosAPaleta(
    const std::vector<InfoElemento<T>> &elementos) {
  for (const auto &info : elementos) {
    QString nombre = QString::fromUtf8(info.nombre);
    QPixmap icono = cargarSpriteTratado(info.rutaSprite, info.recorte, nombre,
                                        TAMANIO_ICONO, TAMANIO_ICONO);
    auto *item = new QListWidgetItem(QIcon(icono), nombre);
    item->setData(ROL_VALOR, static_cast<int>(info.elemento));
    ui.paletaAssets->addItem(item);
  }
}

MapaZona<ElementosCaverna> &ControladorMapas::nivelCavernaActual() {
  return datos.mapa.nivelesCaverna[indiceNivelCaverna];
}

void ControladorMapas::cambiarNivelCaverna(int nivel) {
  indiceNivelCaverna = static_cast<std::size_t>(nivel - PRIMER_NIVEL_CAVERNA);
  ui.vistaCaverna->dibujarZona(nivelCavernaActual());
}

void ControladorMapas::mostrarDimensionesEnCampos(Dimensiones dimensiones) {
  ui.valorAnchoMapa->setValue(dimensiones.ancho);
  ui.valorAltoMapa->setValue(dimensiones.alto);
}

void ControladorMapas::redimensionarZonaActual() {
  Dimensiones nuevas{ui.valorAnchoMapa->value(), ui.valorAltoMapa->value()};
  try {
    redimensionarZonaDelMapa(datos.mapa, zonaActual, nuevas);
  } catch (const std::invalid_argument &error) {
    QMessageBox::warning(&ventana, TITULO_ERROR_DIMENSIONES,
                         QString::fromUtf8(error.what()));
    mostrarDimensionesEnCampos(dimensionesDeZona(datos.mapa, zonaActual));
    return;
  }
  dibujarTodasLasZonas();
}

void ControladorMapas::dibujarTodasLasZonas() {
  ui.vistaGranja->dibujarZona(datos.mapa.granja);
  ui.vistaCaverna->dibujarZona(nivelCavernaActual());
  ui.vistaPueblo->dibujarZona(datos.mapa.pueblo);
}

template <typename T>
void ControladorMapas::manejarClickEnCelda(MapaZona<T> &zona, VistaZona *vista,
                                           int x, int y,
                                           Qt::MouseButton boton) {
  if (!zona.existeCelda(x, y))
    return;
  if (boton == Qt::RightButton)
    zona.quitarObjetoEnCelda(x, y);
  else if (boton == Qt::LeftButton)
    colocarElementoSeleccionadEnCelda(zona, vista, x, y);
  vista->dibujarZona(zona);
}

template <typename T>
void ControladorMapas::colocarElementoSeleccionadEnCelda(MapaZona<T> &zona,
                                                         VistaZona *vista,
                                                         int x, int y) {
  QListWidgetItem *item = ui.paletaAssets->currentItem();
  if (item == nullptr) {
    QToolTip::showText(QCursor::pos(), TEXTO_ELEGIR_ELEMENTO, vista);
    return;
  }
  int valor = item->data(ROL_VALOR).toInt();
  if (!zona.colocarObjetoEnCelda(static_cast<T>(valor), x, y))
    QToolTip::showText(QCursor::pos(), TEXTO_NO_SE_PUEDE_COLOCAR, vista);
}

void ControladorMapas::validarYExportarMapa() {
  std::vector<std::string> errores = erroresParaExportar(datos.mapa);
  if (!errores.empty()) {
    QStringList lineas;
    for (const auto &error : errores)
      lineas.append(QString::fromStdString(error));
    QMessageBox::warning(&ventana, TITULO_MAPA_INVALIDO, lineas.join('\n'));
    return;
  }

  QString ruta = QFileDialog::getSaveFileName(
      &ventana, TITULO_GUARDAR, crearYObtenerCarpetaMapas(), FILTRO_MAPAS);
  if (ruta.isEmpty())
    return;
  if (!ruta.endsWith(EXTENSION_MAPA))
    ruta += EXTENSION_MAPA;

  try {
    escribirMapaEnArchivo(datos.mapa, ruta.toStdString());
    QMessageBox::information(&ventana, TITULO_MAPA_GUARDADO,
                             TEXTO_MAPA_GUARDADO + ruta);
  } catch (const std::exception &error) {
    QMessageBox::warning(&ventana, TITULO_ERROR_GUARDAR,
                         QString::fromUtf8(error.what()));
  }
}
