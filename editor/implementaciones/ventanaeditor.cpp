#include "ventanaeditor.h"

#include "constantes_qt.h"
#include "controlador_inicio_editor.h"
#include "controlador_mapas.h"
#include "navegador.h"
#include "ui_ventanaeditor.h"
#include "vista_responsive.h"

VentanaEditor::VentanaEditor(QWidget *parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::VentanaEditor>()) {
  ui->setupUi(this);
  ui->stackedWidget->setCurrentWidget(ui->pageInicioEditor);

  ui->horizontalLayout->removeWidget(ui->stackedWidget);
  ui->stackedWidget->setParent(nullptr);
  ui->horizontalLayout->setContentsMargins(QMargins());
  ui->horizontalLayout->addWidget(
      new VistaEscalada(ui->stackedWidget, QSize(ANCHO_DISENIO, ALTO_DISENIO),
                        ui->centralwidget));

  Navegador *navegador = new Navegador(ui->stackedWidget, this);
  new ControladorInicioEditor(*this, *ui, *navegador, datos, this);
  new ControladorMapas(*this, *ui, *navegador, datos, this);
}

VentanaEditor::~VentanaEditor() = default;
