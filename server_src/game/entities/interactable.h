#ifndef INTERACTABLE_H_
#define INTERACTABLE_H_

class World;
class Player;

class Interactable {
public:
  virtual ~Interactable() = default;
  virtual void interact(World &world, Player &player) = 0;
};

#endif // INTERACTABLE_H_