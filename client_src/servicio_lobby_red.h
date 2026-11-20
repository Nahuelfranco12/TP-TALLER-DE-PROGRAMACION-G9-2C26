#ifndef SERVICIO_LOBBY_RED_H_
#define SERVICIO_LOBBY_RED_H_

#include <string>

#include "client.h"
#include "servicio_lobby.h"

class ServicioLobbyRed : public ServicioLobby {
public:
  explicit ServicioLobbyRed(Client &client);

  QList<MundoMock> mundosCrearPartida() override;
  QList<PartidaGuardada> partidasARetomar() override;
  ResultadoLobby entrarAJugar(const DatosPartida &datos) override;

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
