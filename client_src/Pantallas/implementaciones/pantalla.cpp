#include "pantalla.h"
#include "partidas_estaticas.h"
#include <QFontDatabase>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>

Pantalla::Pantalla(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Pantalla)
    , pantallaOrigen(nullptr)
{
    ui->setupUi(this);
    configurarFuentes();
    configurarNavegacion();
    ui->stackedWidget->setCurrentWidget(ui->pageMenuPrincipal);
}

Pantalla::~Pantalla()
{
    delete ui;
}

void Pantalla::configurarFuentes() {
    QFontDatabase::addApplicationFont(":/fuentes/assets/Stardew_Valley.ttf");
}

void Pantalla::conectarBoton(QPushButton* boton, QWidget* destino, QWidget* nuevoOrigen, AccionExtra accion) {
    connect(boton, &QPushButton::clicked, this, [this, destino, nuevoOrigen, accion]() {
        if (nuevoOrigen != nullptr)
            pantallaOrigen = nuevoOrigen;
        if (destino != nullptr)
            ui->stackedWidget->setCurrentWidget(destino);
        if (accion != nullptr)
            accion();
    });
}

void Pantalla::configurarNavegacion() {
    // esto es para pasar nomas, tipo boton de siguiente y eso, volver tambien
    conectarBoton(ui->botNuevaPartida, ui->pageNuevaPartida);
    conectarBoton(ui->botUnirsePartida, ui->pageUnirsePartida);
    conectarBoton(ui->botVolver, ui->pageMenuPrincipal);
    conectarBoton(ui->botVolverUP, ui->pageMenuPrincipal);

    // aca no me interesa el origen asi que es nulo, el this es una anonima y hace uso de cargar
    conectarBoton(ui->botRetomarPartida, ui->pageRetomarPartida, nullptr, [this]() {
        cargarListaPartidas();
    });

    // esto lo hago para por ejemplo volver a la pantalla correcta
    conectarBoton(ui->botSiguiente, ui->pageCustomizarPersonaje, ui->pageNuevaPartida);
    conectarBoton(ui->botSiguienteUP, ui->pageCustomizarPersonaje, ui->pageUnirsePartida);

    connect(ui->botVolverPersonaje, &QPushButton::clicked, this, [this]() {
        if (pantallaOrigen != nullptr)
            ui->stackedWidget->setCurrentWidget(pantallaOrigen);
        else
            ui->stackedWidget->setCurrentWidget(ui->pageMenuPrincipal);
    });

    conectarBoton(ui->botVolverRP, ui->pageMenuPrincipal, nullptr, [this]() {
        partidaSeleccionada = "";
        tarjetaSeleccionada = nullptr;
    });

    connect(ui->botJugarRP, &QPushButton::clicked, this, [this]() {
        if (partidaSeleccionada.isEmpty())
            return;
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
        QFrame* tarjetaLista = crearTarjetaPartida(partida);
        ui->scrollAreaWidgetContents->layout()->addWidget(tarjetaLista);
    }
}

QFrame* Pantalla::crearTarjetaPartida(const PartidaGuardada& partida) {
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

    QPushButton* botSeleccionar = new QPushButton("Seleccionar", tarjeta);
    botSeleccionar->setStyleSheet("background-color: #f1b356; color: #3b2010; font-weight: bold; border-radius: 3px; padding: 5px;");
    layoutTarjeta->addWidget(botSeleccionar, 0, Qt::AlignRight);

    connect(botSeleccionar, &QPushButton::clicked, this, [this, tarjeta, partida]() {
        if (this->tarjetaSeleccionada != nullptr)
            this->tarjetaSeleccionada->setStyleSheet("background-color: #3b2010; border: 2px solid #6b4020; border-radius: 5px;");
        tarjeta->setStyleSheet("background-color: #5c341a; border: 2px solid #f1b356; border-radius: 5px;");
        this->tarjetaSeleccionada = tarjeta;
        this->partidaSeleccionada = partida.nombrePartida;
    });

    return tarjeta;
}