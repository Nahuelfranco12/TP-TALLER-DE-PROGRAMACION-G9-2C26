#ifndef ADAPTADOR_PARTIDA_H_
#define ADAPTADOR_PARTIDA_H_

#include "../game/world.h"
#include "partida_guardada.h"

PartidaGuardada extraerPartida(const World &mundo,
                               const PartidaGuardada &anterior);
void restaurarJugador(Player &jugador, const JugadorGuardado &guardado);
void restaurarPartida(World &mundo, const PartidaGuardada &partida);

#endif // ADAPTADOR_PARTIDA_H_
