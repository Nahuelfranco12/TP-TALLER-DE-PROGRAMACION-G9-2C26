#ifndef CONTROLADOR_CUSTOMIZAR_PERSONAJE_H
#define CONTROLADOR_CUSTOMIZAR_PERSONAJE_H

#include "controlador_pagina.h"

class ControladorCustomizarPersonaje : public ControladorPagina {
public:
  ControladorCustomizarPersonaje(Ui::Pantalla &ui, Navegador &navegador,
                                 QObject *parent = nullptr);
  void reiniciar() override;
  void validarFormulario() override;
};

#endif // CONTROLADOR_CUSTOMIZAR_PERSONAJE_H
