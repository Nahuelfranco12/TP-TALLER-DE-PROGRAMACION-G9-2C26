#include "pantalla.h"
#include "controlador_customizar_personaje.h"
#include "controlador_menu_principal.h"
#include "controlador_nueva_partida.h"
#include "controlador_retomar_partida.h"
#include "controlador_unirse_partida.h"
#include "navegador.h"
#include "ui_pantalla.h"

Pantalla::Pantalla(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Pantalla) {
  ui->setupUi(this);
  ui->stackedWidget->setCurrentWidget(ui->pageMenuPrincipal);

  Navegador *navegador = new Navegador(ui->stackedWidget, this);
  new ControladorMenuPrincipal(*ui, *navegador, this);
  new ControladorNuevaPartida(*ui, *navegador, this);
  new ControladorUnirsePartida(*ui, *navegador, this);
  new ControladorRetomarPartida(*ui, *navegador, this);
  new ControladorCustomizarPersonaje(*ui, *navegador, this);
}

Pantalla::~Pantalla() { delete ui; }
