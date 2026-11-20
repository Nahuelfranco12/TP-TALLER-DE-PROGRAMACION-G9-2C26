#ifndef DTOS_PANTALLAS_H_
#define DTOS_PANTALLAS_H_

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
  QString rutaMapa;
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
  QString mensajeError;
};

struct MundoMock {
  QString nombreMundo;
  QString rutaImagen;
  QString rutaMapa;
};

struct PartidaGuardada {
  QString id;
  QString nombrePartida;
  DatosPersonaje personaje;
  bool esMultiplayer = false;
};

#endif // DTOS_PANTALLAS_H_
