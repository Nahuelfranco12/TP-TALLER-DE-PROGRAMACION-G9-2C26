#ifndef CHAT_H_
#define CHAT_H_

#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/game_dtos.h"

class Chat {
private:
  SDL2pp::Renderer &renderer;
  SDL2pp::Font fuente;
  std::vector<SDL2pp::Texture> lineas;
  std::string escribiendo;
  bool abierto;

  void agregar_linea(const std::string &texto, SDL_Color color);
  std::vector<std::string> partir_en_renglones(const std::string &texto) const;
public:
  explicit Chat(SDL2pp::Renderer &renderer);

  void agregar(const std::vector<ChatMessageDto> &mensajes);

  bool manejar_evento(const SDL_Event &evento, std::string &para_enviar);

  void dibujar(int alto_ventana);
};

#endif