#ifndef SERVICIO_LOBBY_RED_H_
#define SERVICIO_LOBBY_RED_H_

#include <string>

#include "client.h"
#include "servicio_lobby.h"

class ServicioLobbyRed : public ServicioLobby {
public:
  explicit ServicioLobbyRed(Client &client);

  QList<MundoMock> pedirMundosDisponibles() override;
  QList<PartidaGuardada> pedirPartidasGuardadas() override;
  ResultadoLobby entrarAJugar(const DatosPartida &datos) override;

  bool estaEnPartida() const;
  const std::string &codigoPartidaActual() const;
  const DatosPersonaje &personajeEnPartida() const;

private:
  Client &client;
  bool enPartida = false;
  std::string codigoPartida;
  DatosPersonaje personaje;
};

#endif // SERVICIO_LOBBY_RED_H_
