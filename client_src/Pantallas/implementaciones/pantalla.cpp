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
  new ControladorNuevaPartida(*ui, *navegador, datosPartida, this);
  new ControladorUnirsePartida(*ui, *navegador, datosPartida, this);
  new ControladorRetomarPartida(*ui, *navegador, datosPartida, dibujante, this);
  new ControladorCustomizarPersonaje(*ui, *navegador, datosPartida, dibujante,
                                     this);
}

Pantalla::~Pantalla() { delete ui; }
