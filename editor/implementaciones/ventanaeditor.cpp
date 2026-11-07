#include "ventanaeditor.h"
#include "ui_ventanaeditor.h"
#include "navegador.h"
#include "controlador_inicio_editor.h"

VentanaEditor::VentanaEditor(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::VentanaEditor) {
  ui->setupUi(this);
  ui->stackedWidget->setCurrentWidget(ui->pageInicioEditor);
  Navegador *navegador = new Navegador(ui->stackedWidget, this);
  new ControladorInicioEditor(*ui, *navegador, datos, this);
}

VentanaEditor::~VentanaEditor() { delete ui; }
