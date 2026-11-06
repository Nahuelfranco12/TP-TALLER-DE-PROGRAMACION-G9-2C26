#include "ventanaeditor.h"
#include "ui_ventanaeditor.h"

VentanaEditor::VentanaEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VentanaEditor)
{
    ui->setupUi(this);
}

VentanaEditor::~VentanaEditor()
{
    delete ui;
}
