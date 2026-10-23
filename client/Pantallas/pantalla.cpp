#include "pantalla.h"
#include "ui_pantalla.h"
#include <QFontDatabase>

Pantalla::Pantalla(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Pantalla)
{
    ui->setupUi(this);

    QFontDatabase::addApplicationFont(":/fuentes/Stardew_Valley.ttf");

    ui->stackedWidget->setCurrentWidget(ui->pageMenuPrincipal);

    connect(ui->botNuevaPartida, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageNuevaPartida);
    });

    connect(ui->botVolver, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageMenuPrincipal);
    });

    connect(ui->botVolverPersonaje, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageNuevaPartida);
    });

    connect(ui->botSiguiente, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageCustomizarPersonaje);
    });

    connect(ui->botUnirsePartida, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageUnirsePartida);
    });

    connect(ui->botVolverUP, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageMenuPrincipal);
    });

}

Pantalla::~Pantalla()
{
    delete ui;
}