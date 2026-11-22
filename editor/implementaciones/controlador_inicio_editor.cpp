#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <exception>
#include <utility>

#include "archivo_mapa.h"
#include "constantes_qt.h"
#include "controlador_inicio_editor.h"
#include "ui_ventanaeditor.h"

ControladorInicioEditor::ControladorInicioEditor(QWidget &ventana,
                                                 Ui::VentanaEditor &ui,
                                                 NavegadorPaginas &navegador,
                                                 DatosEditor &datos,
                                                 QObject *parent)
    : ControladorPaginaEditor(ventana, ui, navegador, parent), datos(datos) {
  connect(ui.botonCrearMapaInicioEditor, &QPushButton::clicked, this,
          [this]() { crearMapa(); });
  connect(ui.botonEditarMapaInicioEditor, &QPushButton::clicked, this,
          [this]() { cargarMapaExistente(); });
  connect(ui.botonSalirInicioEditor, &QPushButton::clicked, this,
          [this]() { this->ventana.close(); });
}

void ControladorInicioEditor::crearMapa() {
  datos = DatosEditor{};
  navegador.irAPagina(ui.pageMapas);
}

void ControladorInicioEditor::cargarMapaExistente() {
  QString ruta = QFileDialog::getOpenFileName(&ventana, TITULO_ABRIR,
                                              crearYObtenerCarpetaMapas(), FILTRO_MAPAS);
  if (ruta.isEmpty())
    return;
  try {
    MapaEditor mapa = cargarMapaDeArchivo(ruta.toStdString());
    datos = DatosEditor{ruta, std::move(mapa)};
    navegador.irAPagina(ui.pageMapas);
  } catch (const std::exception &error) {
    QMessageBox::warning(&ventana, TITULO_ERROR_CARGAR,
                         QString::fromUtf8(error.what()));
  }
}
