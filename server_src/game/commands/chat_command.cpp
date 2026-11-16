#include "chat_command.h"

#include "../../../common_src/constants.h"
#include "../world.h"

void ChatCommand::execute(World &world) {
  Player *sender = world.getPlayer(playerId);
  if (!sender || text.empty())
    return;

  if (text[0] == '@') {
    size_t space = text.find(' ');
    if (space == std::string::npos)
      return;
    std::string receiverName = text.substr(1, space - 1);
    std::string message = text.substr(space + 1);

    Player *receiver = world.getPlayerByName(receiverName);
    if (!receiver) {
      world.addChat({SYSTEM_SENDER_ID, SYSTEM_SENDER_NAME, playerId,
                     receiverName + " no está conectado"});
      return;
    }
    world.addChat({playerId, sender->getName(), receiver->getId(), message});
    return;
  }
  world.addChat({playerId, sender->getName(), MESSAGE_FOR_ALL_ID, text});
}