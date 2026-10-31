#ifndef CONTROLADOR_MENU_PRINCIPAL_H
#define CONTROLADOR_MENU_PRINCIPAL_H

#include "controlador_pagina.h"

class ControladorMenuPrincipal : public ControladorPagina {
public:
  ControladorMenuPrincipal(Ui::Pantalla &ui, Navegador &navegador,
                           QObject *parent = nullptr);
  void limpiarPagina() override;
  void actualizarBotonAvanzar() override;
};

#endif // CONTROLADOR_MENU_PRINCIPAL_H
