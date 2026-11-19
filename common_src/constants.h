#ifndef CONSTANTS_H_
#define CONSTANTS_H_

constexpr unsigned int QUEUE_MAX_SIZE = 1000;
#define STRING_END '\0'
#define STRING_BRK '\n'
#define END_OP 'q'
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define UNKNOWN_OP_ERROR "Operación desconocida."
#define SOCKET_CLOSE_RECEIVE_ERROR "Error: Socket cerrado al recibir"
#define SOCKET_CLOSE_SEND_ERROR "Error: Socket cerrado al enviar"

#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

#define OP_MOVE 1
#define OP_WORLD_STATE 2
#define OP_PLAYER_ID 3
#define OP_CREATE_MATCH 4
#define OP_LIST_MATCHES 5
#define OP_JOIN_MATCH 6
#define OP_SELECT_TOOL 7
#define OP_MINE 8
#define OP_COLLECT 9
#define OP_WORLD_MAP 10
#define OP_PLANT 11
#define OP_GIFT_OFFER 12
#define OP_GIFT_RESPONSE 13
#define OP_TILL 14
#define OP_WATER 15
#define OP_CHEAT_WATER 16
#define OP_CHEAT_GROWTH 17
#define OP_ATTACK 18
#define OP_CHAT 19
#define OP_SLEEP 20
#define OP_CHEAT_END_DAY 21
#define OP_CHEAT_ENEMIES_DAMAGE 22
#define OP_INTERACT 23

#define JOIN_SUCCESS 0
#define JOIN_FAILURE 1

#define SYSTEM_SENDER_ID -1
#define SYSTEM_SENDER_NAME "Juego"
#define MESSAGE_FOR_ALL_ID -1

#endif // CONSTANTS_H_
