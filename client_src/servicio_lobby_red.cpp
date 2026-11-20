#include "servicio_lobby_red.h"
#include "constantes_pantallas.h"
#include "partidas_estaticas.h"

#include <QString>
#include <exception>

ServicioLobbyRed::ServicioLobbyRed(Client &client) : client(client) {}

QList<MundoMock> ServicioLobbyRed::mundos() {
  QList<MundoMock> result;
  for (const MapInfoDto &map : client.list_maps()) {
    result.append({QString::fromStdString(map.name), QString(),
                   QString::fromStdString(map.path)});
  }
  return result;
}

QList<PartidaGuardada> ServicioLobbyRed::partidasGuardadas() {
  return obtenerPartidasDePrueba();
}

ResultadoLobby ServicioLobbyRed::jugar(const DatosPartida &datos) {
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
  } catch (const std::exception &e) {
    return ResultadoLobby{false, QString(ERROR_LOBBY_CONEXION) + e.what()};
  }
}

bool ServicioLobbyRed::estaEnPartida() const { return enPartida; }

const std::string &ServicioLobbyRed::codigo() const { return codigoPartida; }

const DatosPersonaje &ServicioLobbyRed::personajeElegido() const {
  return personaje;
}
