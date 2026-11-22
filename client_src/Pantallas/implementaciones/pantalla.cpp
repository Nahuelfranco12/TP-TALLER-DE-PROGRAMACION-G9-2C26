#include "pantalla.h"
#include "constantes_pantallas.h"
#include "controlador_customizar_personaje.h"
#include "controlador_menu_principal.h"
#include "controlador_nueva_partida.h"
#include "controlador_retomar_partida.h"
#include "controlador_unirse_partida.h"
#include "navegador_paginas.h"
#include "servicio_lobby.h"
#include "ui_pantalla.h"
#include "vista_responsive.h"
#include <QCoreApplication>
#include <QFontDatabase>
#include <QList>

Pantalla::Pantalla(ServicioLobby &servicio, QWidget *parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::Pantalla>()) {
  QFontDatabase::addApplicationFont(RUTA_FUENTE);
  ui->setupUi(this);
  ui->stackedWidget->setCurrentWidget(ui->pageMenuPrincipal);
  ui->verticalLayout->removeWidget(ui->stackedWidget);
  ui->stackedWidget->setParent(nullptr);
  ui->verticalLayout->setContentsMargins(QMargins());
  ui->verticalLayout->addWidget(
      new VistaEscalada(ui->stackedWidget, QSize(ANCHO_DISENIO, ALTO_DISENIO),
                        ui->centralwidget));

  NavegadorPaginas *navegador = new NavegadorPaginas(ui->stackedWidget, this);
  const QList<ControladorPagina *> controladores = {
      new ControladorMenuPrincipal(*this, *ui, *navegador, this),
      new ControladorNuevaPartida(*this, *ui, *navegador, datosPartida,
                                  servicio, this),
      new ControladorUnirsePartida(*this, *ui, *navegador, datosPartida, this),
      new ControladorRetomarPartida(*this, *ui, *navegador, datosPartida,
                                    dibujante, servicio, this),
      new ControladorCustomizarPersonaje(*this, *ui, *navegador, datosPartida,
                                         dibujante, servicio, this)};
  for (ControladorPagina *controlador : controladores)
    connect(controlador, &ControladorPagina::seInicioPartida, this,
            &QCoreApplication::quit);
}

Pantalla::~Pantalla() = default;
