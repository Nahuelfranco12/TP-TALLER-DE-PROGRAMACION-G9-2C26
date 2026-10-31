#include "servicio_lobby_red.h"

#include <exception>

namespace {
const char *ERROR_CODIGO = "No existe una partida con ese código.";
const char *ERROR_NO_DISPONIBLE = "Esta opción todavía no está disponible.";
const char *ERROR_CONEXION = "Se perdió la conexión con el servidor: ";
} // namespace

ServicioLobbyRed::ServicioLobbyRed(Client &client) : client(client) {}

QList<MundoMock> ServicioLobbyRed::mundos() { return obtenerMundosDePrueba(); }

QList<PartidaGuardada> ServicioLobbyRed::partidasGuardadas() {
  return obtenerPartidasDePrueba();
}

ResultadoLobby ServicioLobbyRed::jugar(const DatosPartida &datos) {
  try {
    std::string codigo;
    switch (datos.modo) {
    case ModoPartida::Nueva:
      codigo = client.create_match(datos.nombrePartida.toStdString());
      break;
    case ModoPartida::Unirse:
      codigo = datos.codigoUnirsePartida.toStdString();
      break;
    case ModoPartida::Retomar:
    case ModoPartida::Ninguno:
      return ResultadoLobby{false, "", ERROR_NO_DISPONIBLE};
    }

    if (!client.join_match(codigo))
      return ResultadoLobby{false, "", ERROR_CODIGO};

    enPartida = true;
    codigoPartida = codigo;
    personaje = datos.personaje;
    return ResultadoLobby{true, QString::fromStdString(codigo), ""};
  } catch (const std::exception &e) {
    return ResultadoLobby{false, "", QString(ERROR_CONEXION) + e.what()};
  }
}

bool ServicioLobbyRed::estaEnPartida() const { return enPartida; }

const std::string &ServicioLobbyRed::codigo() const { return codigoPartida; }

const DatosPersonaje &ServicioLobbyRed::personajeElegido() const {
  return personaje;
}
