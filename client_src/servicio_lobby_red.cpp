#include "servicio_lobby_red.h"
#include "constantes_pantallas.h"
#include "partidas_estaticas.h"

#include <QString>
#include <exception>

ServicioLobbyRed::ServicioLobbyRed(Client &client) : client(client) {}

QList<MundoMock> ServicioLobbyRed::pedirMundosDisponibles() {
  QList<MundoMock> mundos;
  for (const MapInfoDto &mapa : client.list_maps()) {
    mundos.append({QString::fromStdString(mapa.name),
                   QString::fromStdString(mapa.path)});
  }
  return mundos;
}

QList<PartidaGuardada> ServicioLobbyRed::pedirPartidasGuardadas() {
  return obtenerPartidasDePrueba();
}

ResultadoLobby ServicioLobbyRed::entrarAJugar(const DatosPartida &datos) {
  try {
    std::string codigoAUnirse;
    switch (datos.modo) {
    case ModoPartida::Nueva:
      codigoAUnirse = client.create_match(datos.nombrePartida.toStdString(),
                                          datos.rutaMapa.toStdString());
      if (codigoAUnirse.empty())
        return ResultadoLobby{false, ERROR_LOBBY_CREAR};
      break;
    case ModoPartida::Unirse:
      codigoAUnirse = datos.codigoUnirsePartida.toStdString();
      break;
    case ModoPartida::Retomar:
      return ResultadoLobby{false, ERROR_LOBBY_NO_DISPONIBLE};
    case ModoPartida::Ninguno:
      return ResultadoLobby{false, ERROR_LOBBY_SIN_MODO};
    }
    PlayerOutfitDto outfit{
        static_cast<PlayerHatsDto>(datos.personaje.ropa.gorro),
        static_cast<PlayerHairsDto>(datos.personaje.ropa.pelo),
        static_cast<PlayerTShirtsDto>(datos.personaje.ropa.remera),
        static_cast<PlayerPantsDto>(datos.personaje.ropa.pantalon)};
    if (!client.join_match(codigoAUnirse, datos.personaje.nombre.toStdString(),
                           outfit)) {
      if (datos.modo == ModoPartida::Nueva)
        return ResultadoLobby{false, ERROR_LOBBY_ENTRAR_CREADA};
      return ResultadoLobby{false, ERROR_LOBBY_CODIGO};
    }

    enPartida = true;
    codigoPartida = codigoAUnirse;
    personaje = datos.personaje;
    return ResultadoLobby{true, QString()};
  } catch (const std::exception &error) {
    return ResultadoLobby{false, QString(ERROR_LOBBY_CONEXION) + error.what()};
  }
}

ResultadoLobby
ServicioLobbyRed::verificarCodigoPartida(const QString &codigo) {
  try {
    std::string buscado = codigo.toStdString();
    for (const MatchInfoDto &partida : client.list_matches())
      if (partida.code == buscado)
        return ResultadoLobby{true, QString()};
    return ResultadoLobby{false, ERROR_LOBBY_CODIGO};
  } catch (const std::exception &error) {
    return ResultadoLobby{false, QString(ERROR_LOBBY_CONEXION) + error.what()};
  }
}

bool ServicioLobbyRed::estaEnPartida() const { return enPartida; }

const std::string &ServicioLobbyRed::codigoPartidaActual() const {
  return codigoPartida;
}

const DatosPersonaje &ServicioLobbyRed::personajeEnPartida() const {
  return personaje;
}
