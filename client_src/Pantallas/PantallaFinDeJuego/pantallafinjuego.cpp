#include "pantallafinjuego.h"
#include "ui_pantallafinjuego.h"

PantallaFinJuego::PantallaFinJuego(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::PantallaFinJuego) {
  ui->setupUi(this);
  connect(ui->botonSalir, &QPushButton::clicked, this,
          [this]() { this->close(); });
}

PantallaFinJuego::~PantallaFinJuego() { delete ui; }
