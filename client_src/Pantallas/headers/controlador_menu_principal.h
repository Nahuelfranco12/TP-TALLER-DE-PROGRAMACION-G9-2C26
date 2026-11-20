#ifndef CONTROLADOR_MENU_PRINCIPAL_H_
#define CONTROLADOR_MENU_PRINCIPAL_H_

#include "controlador_pagina.h"

class ControladorMenuPrincipal : public ControladorPagina {
public:
  ControladorMenuPrincipal(QWidget &ventana, Ui::Pantalla &ui,
                           NavegadorPaginas &navegador, QObject *parent = nullptr);
  void limpiarPagina() override;
  void actualizarBotonAvanzar() override;
};

#endif // CONTROLADOR_MENU_PRINCIPAL_H_
