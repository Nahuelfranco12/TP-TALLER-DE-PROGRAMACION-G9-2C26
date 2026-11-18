#include "chat_command.h"

#include "../../../common_src/constants.h"
#include "../world.h"

#define MERCHANT_NAME "Pierre"

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

  if (text[0] == '/') {
    size_t space = text.find(' ');
    bool hasArgs = space != std::string::npos;
    std::string command = hasArgs ? text.substr(0, space) : text;
    std::string args = hasArgs ? text.substr(space + 1) : "";

    std::string answer;
    if (command == "/ayuda") {
        answer = "Comandos: /catalogo, /comprar <producto> <cantidad>, /vender <producto> <cantidad>";
    } else if (command == "/catalogo") {
        answer = "Vendo semillas de frutilla, cebolla, papa y calabaza. Compro cultivos y minerales.";
    } else if (command == "/comprar" && hasArgs) {
        answer = "intentaste comprar " + args + "?";
    } else if (command == "/vender" && hasArgs) {
        answer = "intentaste venderme " + args + "?";
    } else {
        answer = "No entiendí el comando. Escribi /ayuda";
    }

    world.addChat({SYSTEM_SENDER_ID, MERCHANT_NAME, playerId, answer});
    return;
}
  world.addChat({playerId, sender->getName(), MESSAGE_FOR_ALL_ID, text});
}