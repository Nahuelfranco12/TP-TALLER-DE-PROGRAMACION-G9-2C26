#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <list>
#include <memory>

#include "../../world_state.h"
#include "../game_constants.h"
#include "inventory_slot.h"
#include "tool.h"

class Inventory {
private:
  std::list<InventorySlot> items;
  std::list<std::unique_ptr<Tool>> tools;

public:
  Inventory() : items(), tools() {}

  bool addItem(std::unique_ptr<Item> item);
  bool addTool(std::unique_ptr<Tool> tool);
  Tool *getTool(AvailableTools type);
  bool giveSlotTo(int index, Inventory &other);

  /*
  * Devuelve cuanta cantidad del item "sample" hay en el inventario
  */
  int countOf(const Item &sample) const;

  /*
  * Saca "amount" items iguales a sample del inventario.
  * Devuelve false si no tiene suficientes items del tipo.
  */
  bool remove(const Item &sample, int amount);

  /*
  * Variante de la función remove que guarda la suma de todos los multiplicadores de precio lo que removió en "multipliers".
  */
  bool remove(const Item &sample, int amount,  double &multipliers);

  const Item *itemAt(int index) const;

  bool removeFromSlot(int index);

  InventoryState state() const;
};

#endif // INVENTORY_H_
