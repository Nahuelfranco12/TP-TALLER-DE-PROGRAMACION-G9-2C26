#ifndef SERVICIO_LOBBY_RED_H_
#define SERVICIO_LOBBY_RED_H_

#include <string>

#include "client.h"
#include "servicio_lobby.h"

class ServicioLobbyRed : public ServicioLobby {
public:
  explicit ServicioLobbyRed(Client &client);

  QList<MundoMock> mundos() override;
  QList<PartidaGuardada> partidasGuardadas() override;
  ResultadoLobby jugar(const DatosPartida &datos) override;

  // Para main, cuando se cierra el lobby
  bool estaEnPartida() const;
  const std::string &codigo() const;
  const DatosPersonaje &personajeElegido() const;

private:
  Client &client;
  bool enPartida = false;
  std::string codigoPartida;
  DatosPersonaje personaje;
};

#endif // SERVICIO_LOBBY_RED_H_
