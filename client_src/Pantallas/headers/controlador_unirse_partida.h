#ifndef CONTROLADOR_UNIRSE_PARTIDA_H
#define CONTROLADOR_UNIRSE_PARTIDA_H

#include "controlador_pagina.h"

class ControladorUnirsePartida : public ControladorPagina {
public:
  ControladorUnirsePartida(Ui::Pantalla &ui, Navegador &navegador,
                           QObject *parent = nullptr);
};

#endif // CONTROLADOR_UNIRSE_PARTIDA_H
