#include <QDir>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <exception>
#include <utility>

#include "constantes_qt.h"
#include "controlador_inicio_editor.h"
#include "ui_ventanaeditor.h"
#include "archivo_mapa.h"


ControladorInicioEditor::ControladorInicioEditor(QWidget &ventana,
                                                 Ui::VentanaEditor &ui,
                                                 Navegador &navegador,
                                                 DatosEditor &datos,
                                                 QObject *parent)
    : ControladorPaginaEditor(ventana, ui, navegador, parent), datos(datos) {
  connect(ui.botonEditorCrearMapa, &QPushButton::clicked, this,
          [this]() { crearMapa(); });
  connect(ui.botonEditorMapa, &QPushButton::clicked, this,
          [this]() { editarMapa(); });
  connect(ui.botonEditorSalir, &QPushButton::clicked, this,
          [this]() { this->ventana.close(); });
}

void ControladorInicioEditor::crearMapa() {
  datos = DatosEditor{};
  navegador.irA(ui.pageMapas);
}

void ControladorInicioEditor::editarMapa() {
  QString ruta = QFileDialog::getOpenFileName(&ventana, TITULO_ABRIR,
                                              QDir::homePath(), FILTRO_MAPAS);
  if (ruta.isEmpty())
    return;
  try {
    MapaEditor mapa = cargarMapa(ruta.toStdString());
    datos = DatosEditor{ruta, std::move(mapa)};
    navegador.irA(ui.pageMapas);
  } catch (const std::exception &error) {
    QMessageBox::warning(&ventana, TITULO_ERROR_CARGAR,
                         QString::fromUtf8(error.what()));
  }
}

void ControladorInicioEditor::limpiarPagina() {}
