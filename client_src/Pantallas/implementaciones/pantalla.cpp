#include "pantalla.h"
#include "constantes_qt.h"
#include "controlador_customizar_personaje.h"
#include "controlador_menu_principal.h"
#include "controlador_nueva_partida.h"
#include "controlador_retomar_partida.h"
#include "controlador_unirse_partida.h"
#include "navegador.h"
#include "ui_pantalla.h"
#include "vista_responsive.h"

Pantalla::Pantalla(ServicioLobby &servicio, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Pantalla) {
  ui->setupUi(this);
  ui->stackedWidget->setCurrentWidget(ui->pageMenuPrincipal);
  ui->verticalLayout->removeWidget(ui->stackedWidget);
  ui->stackedWidget->setParent(nullptr);
  ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
  ui->verticalLayout->addWidget(
      new VistaEscalada(ui->stackedWidget, QSize(ANCHO_DISENIO, ALTO_DISENIO),
                        ui->centralwidget));

  Navegador *navegador = new Navegador(ui->stackedWidget, this);
  new ControladorMenuPrincipal(*ui, *navegador, this);
  new ControladorNuevaPartida(*ui, *navegador, datosPartida, servicio, this);
  new ControladorUnirsePartida(*ui, *navegador, datosPartida, this);
  new ControladorRetomarPartida(*ui, *navegador, datosPartida, dibujante,
                                servicio, this);
  new ControladorCustomizarPersonaje(*ui, *navegador, datosPartida, dibujante,
                                     servicio, this);
}

Pantalla::~Pantalla() { delete ui; }
