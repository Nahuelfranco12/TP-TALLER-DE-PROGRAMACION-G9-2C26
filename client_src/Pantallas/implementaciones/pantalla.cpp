#include "pantalla.h"
#include "constantes_pantallas.h"
#include "controlador_customizar_personaje.h"
#include "controlador_menu_principal.h"
#include "controlador_nueva_partida.h"
#include "controlador_retomar_partida.h"
#include "controlador_unirse_partida.h"
#include "navegador.h"
#include "ui_pantalla.h"
#include "vista_responsive.h"
#include "servicio_lobby.h"
#include <QFontDatabase>

Pantalla::Pantalla(ServicioLobby &servicio, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Pantalla) {
  QFontDatabase::addApplicationFont(RUTA_FUENTE);
  ui->setupUi(this);
  ui->stackedWidget->setCurrentWidget(ui->pageMenuPrincipal);
  ui->verticalLayout->removeWidget(ui->stackedWidget);
  ui->stackedWidget->setParent(nullptr);
  ui->verticalLayout->setContentsMargins(QMargins());
  ui->verticalLayout->addWidget(
      new VistaEscalada(ui->stackedWidget, QSize(ANCHO_DISENIO, ALTO_DISENIO),
                        ui->centralwidget));

  Navegador *navegador = new Navegador(ui->stackedWidget, this);
  new ControladorMenuPrincipal(*this, *ui, *navegador, this);
  new ControladorNuevaPartida(*this, *ui, *navegador, datosPartida, servicio,
                              this);
  new ControladorUnirsePartida(*this, *ui, *navegador, datosPartida, this);
  new ControladorRetomarPartida(*this, *ui, *navegador, datosPartida,
                                dibujante, servicio, this);
  new ControladorCustomizarPersonaje(*this, *ui, *navegador, datosPartida,
                                     dibujante, servicio, this);
}

Pantalla::~Pantalla() { delete ui; }
