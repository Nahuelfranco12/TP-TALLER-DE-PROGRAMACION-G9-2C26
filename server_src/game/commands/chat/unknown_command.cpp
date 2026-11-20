#include "unknown_command.h"

#include "../../../../common_src/constants.h"
#include "../../world.h"


UnknownCommand::UnknownCommand(int playerId, const std::string &word)
      : playerId(playerId), word(word) {}

void UnknownCommand::execute(World &world) {
  world.addChat({SYSTEM_SENDER_ID, SYSTEM_SENDER_NAME, playerId, "No conozco el comando " + word});
}