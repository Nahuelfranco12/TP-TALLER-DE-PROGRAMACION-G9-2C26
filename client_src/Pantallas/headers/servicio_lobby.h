#ifndef SERVICIO_LOBBY_H
#define SERVICIO_LOBBY_H

#include "datos_partida.h"
#include "partidas_estaticas.h"
#include <QList>
#include <QString>

struct ResultadoLobby {
    bool ok = false;
    QString codigoPartida;
    QString mensajeError;
};


class ServicioLobby {
public:
    virtual ~ServicioLobby() = default;
    virtual QList<MundoMock> mundos() = 0;
    virtual QList<PartidaGuardada> partidasGuardadas() = 0;
    virtual ResultadoLobby jugar(const DatosPartida &datos) = 0;
};

#endif // SERVICIO_LOBBY_H
