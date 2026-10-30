#ifndef DATOS_PARTIDA_H
#define DATOS_PARTIDA_H

#include <QString>

struct DatosPersonaje {
  QString nombre;
  int gorro = 0;
  int pelo = 0;
  int pantalon = 0;
  int remera = 0;
};

struct DatosPartida {
  QString nombrePartida;
  QString idMundo;
  DatosPersonaje personaje;
};

#endif // DATOS_PARTIDA_H
