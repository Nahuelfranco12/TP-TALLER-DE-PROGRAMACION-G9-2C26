#ifndef DATOS_PARTIDA_H
#define DATOS_PARTIDA_H

#include <QString>

enum class ModoPartida { Ninguno, Nueva, Unirse, Retomar };

struct DatosPersonaje {
  QString nombre;
  int gorro = 0;
  int pelo = 0;
  int pantalon = 0;
  int remera = 0;
};

struct DatosPartida {
  ModoPartida modo = ModoPartida::Ninguno;
  QString nombrePartida;
  QString idMundo;
  QString codigoUnirsePartida;
  QString idRetomarPartida;
  DatosPersonaje personaje;
};

#endif // DATOS_PARTIDA_H
