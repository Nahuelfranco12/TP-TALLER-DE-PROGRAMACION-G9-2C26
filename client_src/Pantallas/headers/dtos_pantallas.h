#ifndef DTOS_PANTALLAS_H
#define DTOS_PANTALLAS_H

#include <QPixmap>
#include <QString>

enum class ModoPartida { Ninguno, Nueva, Unirse, Retomar };

struct Apariencia {
  int gorro = 0;
  int pelo = 0;
  int pantalon = 0;
  int remera = 0;
};

struct DatosPersonaje {
  QString nombre;
  Apariencia ropa;
};

struct DatosPartida {
  ModoPartida modo = ModoPartida::Ninguno;
  QString nombrePartida;
  QString idMundo;
  QString codigoUnirsePartida;
  QString idRetomarPartida;
  DatosPersonaje personaje;
};

struct DatosTarjeta {
  QString id;
  QPixmap imagen;
  QString titulo;
  QString subtitulo;
  QString textoExtra;
  QString textoBoton;
};

struct ResultadoLobby {
  bool ok = false;
  QString codigoPartida;
  QString mensajeError;
};

struct MundoMock {
  QString nombreMundo;
  QString rutaImagen;
};

struct PartidaGuardada {
  QString id;
  QString nombrePartida;
  DatosPersonaje personaje;
  bool esMultiplayer = false;
};

#endif // DTOS_PANTALLAS_H
