#ifndef EDITOR_DTOS_H
#define EDITOR_DTOS_H

#include <QPixmap>
#include <QString>

enum class TipoAsset {Granja, Caverna, Pueblo};

struct AssetsGranja{

};

struct AssetsPueblo{

};

struct AssetsCaverna{

};

struct AssetsTotal{
	AssetsGranja granja;
	AssetsPueblo pueblo;
	AssetsCaverna caverna;
}

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

#endif // EDITOR_DTOS_H
