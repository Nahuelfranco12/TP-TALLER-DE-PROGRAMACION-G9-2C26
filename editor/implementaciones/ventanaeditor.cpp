#include "ventanaeditor.h"

#include "constantes.h"
#include "controlador_inicio_editor.h"
#include "controlador_mapas.h"
#include "navegador.h"
#include "ui_ventanaeditor.h"
#include "vista_responsive.h"

VentanaEditor::VentanaEditor(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::VentanaEditor) {
  ui->setupUi(this);
  ui->stackedWidget->setCurrentWidget(ui->pageInicioEditor);

  ui->horizontalLayout->removeWidget(ui->stackedWidget);
  ui->stackedWidget->setParent(nullptr);
  ui->horizontalLayout->setContentsMargins(0, 0, 0, 0);
  ui->horizontalLayout->addWidget(
      new VistaEscalada(ui->stackedWidget, QSize(ANCHO_DISENIO, ALTO_DISENIO),
                        ui->centralwidget));

  Navegador *navegador = new Navegador(ui->stackedWidget, this);
  new ControladorInicioEditor(*ui, *navegador, datos, this);
  new ControladorMapas(*ui, *navegador, datos, this);
}

VentanaEditor::~VentanaEditor() { delete ui; }
