#include "controlador_inicio_editor.h"

#include <QDir>
#include <QFileDialog>
#include <QPushButton>

#include "ui_ventanaeditor.h"

namespace {
const char *TITULO_ABRIR = "Abrir mapa";
const char *FILTRO_MAPAS = "Mapas (*.toml *.json)";
}  // namespace

ControladorInicioEditor::ControladorInicioEditor(Ui::VentanaEditor &ui,
                                                 Navegador &navegador,
                                                 DatosEditor &datos,
                                                 QObject *parent)
    : ControladorPaginaEditor(ui, navegador, parent), datos(datos) {
  connect(ui.botonEditorCrearMapa, &QPushButton::clicked, this,
          [this]() { crearMapa(); });
  connect(ui.botonEditorMapa, &QPushButton::clicked, this,
          [this]() { editarMapa(); });
  connect(ui.botonEditorSalir, &QPushButton::clicked, this,
          [this]() { this->ui.botonEditorSalir->window()->close(); });
}

void ControladorInicioEditor::crearMapa() {
  datos = DatosEditor{ModoEditor::Crear, QString()};
  navegador.irA(ui.pageMapas);
}

void ControladorInicioEditor::editarMapa() {
  QString ruta = QFileDialog::getOpenFileName(
      ui.pageInicioEditor->window(), TITULO_ABRIR, QDir::homePath(),
      FILTRO_MAPAS);
  if (ruta.isEmpty())
    return;
  datos = DatosEditor{ModoEditor::Editar, ruta};
  navegador.irA(ui.pageMapas);
}

void ControladorInicioEditor::limpiarPagina() {}
