#include "servicio_lobby_red.h"
#include "constantes_pantallas.h"

#include <QString>
#include <exception>

ServicioLobbyRed::ServicioLobbyRed(Client &client) : client(client) {}

QList<MundoMock> ServicioLobbyRed::mundos() { return obtenerMundosDePrueba(); }

QList<PartidaGuardada> ServicioLobbyRed::partidasGuardadas() {
  return obtenerPartidasDePrueba();
}

ResultadoLobby ServicioLobbyRed::jugar(const DatosPartida &datos) {
  try {
    std::string codigoAUnirse;
    switch (datos.modo) {
    case ModoPartida::Nueva:
      codigoAUnirse = client.create_match(datos.nombrePartida.toStdString());
      break;
    case ModoPartida::Unirse:
      codigoAUnirse = datos.codigoUnirsePartida.toStdString();
      break;
    case ModoPartida::Retomar:
    case ModoPartida::Ninguno:
      return ResultadoLobby{false, QString(), ERROR_LOBBY_NO_DISPONIBLE};
    }
    PlayerOutfitDto outfit{
        static_cast<PlayerHatsDto>(datos.personaje.ropa.gorro),
        static_cast<PlayerHairsDto>(datos.personaje.ropa.pelo),
        static_cast<PlayerTShirtsDto>(datos.personaje.ropa.remera),
        static_cast<PlayerPantsDto>(datos.personaje.ropa.pantalon)};
    if (!client.join_match(codigoAUnirse, datos.personaje.nombre.toStdString(),
                           outfit))
      return ResultadoLobby{false, QString(), ERROR_LOBBY_CODIGO};

    enPartida = true;
    codigoPartida = codigoAUnirse;
    personaje = datos.personaje;
    return ResultadoLobby{true, QString::fromStdString(codigoAUnirse), ""};
  } catch (const std::exception &e) {
    return ResultadoLobby{false, "", QString(ERROR_LOBBY_CONEXION) + e.what()};
  }
}

bool ServicioLobbyRed::estaEnPartida() const { return enPartida; }

const std::string &ServicioLobbyRed::codigo() const { return codigoPartida; }

const DatosPersonaje &ServicioLobbyRed::personajeElegido() const {
  return personaje;
}
