#include "pantalla.h"
#include "ui_pantalla.h"
#include "partidas_estaticas.h" // Incluimos las partidas simuladas
#include <QFontDatabase>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>

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


 connect(ui->botRetomarPartida, &QPushButton::clicked, this, [this]() {
     ui->stackedWidget->setCurrentWidget(ui->pageRetomarPartida);
    cargarListaPartidas();
 });

    connect(ui->botVolver, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageMenuPrincipal);
    });

    connect(ui->botSiguiente, &QPushButton::clicked, this, [this]() {
        pantallaOrigen = ui->pageNuevaPartida;
        ui->stackedWidget->setCurrentWidget(ui->pageCustomizarPersonaje);
    });

    connect(ui->botVolverUP, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageMenuPrincipal);
    });

    connect(ui->botSiguienteUP, &QPushButton::clicked, this, [this]() {
        pantallaOrigen = ui->pageUnirsePartida;
        ui->stackedWidget->setCurrentWidget(ui->pageCustomizarPersonaje);
    });

    connect(ui->botVolverPersonaje, &QPushButton::clicked, this, [this]() {
        if (pantallaOrigen != nullptr) {
            ui->stackedWidget->setCurrentWidget(pantallaOrigen);
        } else {
            ui->stackedWidget->setCurrentWidget(ui->pageMenuPrincipal);
        }
    });

    connect(ui->botVolverRP, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageMenuPrincipal);
    });

    connect(ui->botJugarRP, &QPushButton::clicked, this, [this]() {
    });
}

void Pantalla::cargarListaPartidas() {
    QLayout* layoutExistente = ui->scrollAreaWidgetContents->layout();
    if (layoutExistente != nullptr) {
        QLayoutItem* item;
        while ((item = layoutExistente->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    } else {
        ui->scrollAreaWidgetContents->setLayout(new QVBoxLayout());
    }

    QList<PartidaGuardada> partidas = obtenerPartidasDePrueba();

    for (const PartidaGuardada& partida : partidas) {
        QFrame* tarjeta = new QFrame(ui->scrollAreaWidgetContents);
        tarjeta->setStyleSheet("background-color: #3b2010; border: 2px solid #6b4020; border-radius: 5px;");
        tarjeta->setFixedHeight(80);
        QHBoxLayout* layoutTarjeta = new QHBoxLayout(tarjeta);

        QLabel* labelImagen = new QLabel(tarjeta);
        labelImagen->setPixmap(QPixmap(partida.rutaImagen).scaled(64, 64, Qt::KeepAspectRatio));
        labelImagen->setFixedSize(64, 64);
        labelImagen->setStyleSheet("border: none;");
        layoutTarjeta->addWidget(labelImagen);

        QVBoxLayout* layoutTextos = new QVBoxLayout();
        QLabel* labelPartida = new QLabel(partida.nombrePartida, tarjeta);
        QLabel* labelPersonaje = new QLabel(partida.nombrePersonaje, tarjeta);
        labelPartida->setStyleSheet("color: #f1b356; font-family: 'Stardew Valley'; font-size: 18px; border: none;");
        labelPersonaje->setStyleSheet("color: white; font-family: 'Stardew Valley'; font-size: 14px; border: none;");
        layoutTextos->addWidget(labelPartida);
        layoutTextos->addWidget(labelPersonaje);
        layoutTarjeta->addLayout(layoutTextos);

        QLabel* labelTipo = new QLabel(partida.esMultiplayer ? "Multiplayer" : "Singleplayer", tarjeta);
        labelTipo->setStyleSheet("color: #f1b356; font-family: 'Stardew Valley'; font-size: 14px; border: none;");
        layoutTarjeta->addWidget(labelTipo, 0, Qt::AlignRight);

        ui->scrollAreaWidgetContents->layout()->addWidget(tarjeta);
    }
}

Pantalla::~Pantalla()
{
    delete ui;
}