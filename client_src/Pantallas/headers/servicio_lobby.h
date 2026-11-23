#ifndef SERVICIO_LOBBY_H_
#define SERVICIO_LOBBY_H_

#include "dtos_pantallas.h"
#include <QList>
#include <QString>
class ServicioLobby {
public:
  virtual ~ServicioLobby() = default;
  virtual QList<MundoMock> pedirMundosDisponibles() = 0;
  virtual QList<PartidaGuardada> pedirPartidasGuardadas() = 0;
  virtual ResultadoLobby entrarAJugar(const DatosPartida &datos) = 0;
};

#endif // SERVICIO_LOBBY_H_
