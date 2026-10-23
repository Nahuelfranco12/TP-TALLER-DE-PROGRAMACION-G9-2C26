#include "pantalla.h"
#include "ui_pantalla.h"
#include <QFontDatabase>

static QWidget* pantallaOrigen = nullptr;

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

    connect(ui->botUnirsePartida, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageUnirsePartida);
    });

    connect(ui->botVolver, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageMenuPrincipal);
    });

    connect(ui->botSiguiente, &QPushButton::clicked, this, [this]() {
        pantallaOrigen = ui->pageNuevaPartida; // Guardamos que venimos de Nueva Partida
        ui->stackedWidget->setCurrentWidget(ui->pageCustomizarPersonaje);
    });

    connect(ui->botVolverUP, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageMenuPrincipal);
    });

    connect(ui->botSiguienteUP, &QPushButton::clicked, this, [this]() {
        pantallaOrigen = ui->pageUnirsePartida; // Guardamos que venimos de Unirse a Partida
        ui->stackedWidget->setCurrentWidget(ui->pageCustomizarPersonaje);
    });

    connect(ui->botVolverPersonaje, &QPushButton::clicked, this, [this]() {
        if (pantallaOrigen != nullptr) {
            ui->stackedWidget->setCurrentWidget(pantallaOrigen);
        } else {
            ui->stackedWidget->setCurrentWidget(ui->pageMenuPrincipal); // Por seguridad
        }
    });
}

Pantalla::~Pantalla()
{
    delete ui;
}