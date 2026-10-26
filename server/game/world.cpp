#include "world.h"

bool World::addSector(IdSector id) {
    Sector sector(30, 30, id);
    auto [it, inserted] = this->sectors.try_emplace(id, sector);
    return inserted;
}

// TODO: revisar para que spawnee en GRANJA directo
void World::addPlayer(Player player, IdSector idSector) {
    this->players.emplace(this->players.begin(), player);
    auto it = this->sectors.find(idSector);
    if (it != this->sectors.end()) {
        // TODO: revisar porque se insertan siempre en el (0, 0)
        // Si se insertan 2 jugadores seguidos en (0, 0), se pueden llegar a pisar.
        it->second.addEntity(player, Position(0, 0));
    }
}

bool transfer(Entity& e, IdSector destine, Position pos) {
    // TODO: implementar
    return false; 
}