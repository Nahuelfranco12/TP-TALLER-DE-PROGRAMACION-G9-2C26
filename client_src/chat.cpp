#include "chat.h"

using SDL2pp::Rect;
using SDL2pp::Texture;

namespace {
const size_t MAX_LINEAS = 8;
const int TAMANIO_LETRA = 14;
const int MARGEN = 10;
const int ALTO_LINEA = 18;
const int ESPACIO_INVENTARIO = 70;
const int ANCHO_CHAT = 420;
const int ANCHO_TEXTO = ANCHO_CHAT - 2 * MARGEN;

const SDL_Color BLANCO = {255, 255, 255, 255};
const SDL_Color AMARILLO = {255, 220, 90, 255};
} // namespace

Chat::Chat(SDL2pp::Renderer &renderer)
    : renderer(renderer),
      fuente("assets/fuentes/DejaVuSans-Bold.ttf", TAMANIO_LETRA),
      abierto(false) {
  SDL_StopTextInput();
}

void Chat::agregar_linea(const std::string &texto, SDL_Color color) {
  for (const std::string &renglon : partir_en_renglones(texto))
    lineas.emplace_back(renderer, fuente.RenderUTF8_Blended(renglon, color));
  while (lineas.size() > MAX_LINEAS)
    lineas.erase(lineas.begin());
}
std::vector<std::string> Chat::partir_en_renglones(const std::string &texto) const {
  std::vector<std::string> renglones;
  std::string renglon;
  size_t inicio = 0;

  while (inicio < texto.size()) {
    size_t espacio = texto.find(' ', inicio);
    if (espacio == std::string::npos)
      espacio = texto.size();
    std::string palabra = texto.substr(inicio, espacio - inicio);
    inicio = espacio + 1;

    std::string con_palabra = renglon.empty() ? palabra : renglon + " " + palabra;
    if (fuente.GetSizeUTF8(con_palabra).GetX() > ANCHO_TEXTO && !renglon.empty()) {
      renglones.push_back(renglon);
      renglon = palabra;
    } else {
      renglon = con_palabra;
    }
  }
  if (!renglon.empty())
    renglones.push_back(renglon);
  return renglones;
}

void Chat::agregar(const std::vector<ChatMessageDto> &mensajes) {
  for (const ChatMessageDto &mensaje : mensajes)
    agregar_linea(mensaje.fromName + ": " + mensaje.text,
                  mensaje.isPrivate ? AMARILLO : BLANCO);
}

bool Chat::manejar_evento(const SDL_Event &evento, std::string &para_enviar) {
  if (!abierto) {
    if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_RETURN) {
      abierto = true;
      escribiendo.clear();
      SDL_StartTextInput();
      return true;
    }
    return false;
  }

  if (evento.type == SDL_TEXTINPUT) {
    escribiendo += evento.text.text;
    return true;
  }
  if (evento.type == SDL_KEYDOWN) {
    switch (evento.key.keysym.sym) {
    case SDLK_RETURN:
      para_enviar = escribiendo;
      abierto = false;
      SDL_StopTextInput();
      break;
    case SDLK_ESCAPE:
      abierto = false;
      SDL_StopTextInput();
      break;
    case SDLK_BACKSPACE:
      if (!escribiendo.empty())
        escribiendo.pop_back();
      break;
    default:
      break;
    }
    return true;
  }
  return evento.type == SDL_KEYUP;
}

void Chat::dibujar(int alto_ventana) {
  int lineas_totales = static_cast<int>(lineas.size()) + (abierto ? 1 : 0);
  if (lineas_totales == 0)
    return;

  int base = alto_ventana - ESPACIO_INVENTARIO;

  // agregue un fondo medio transparente atras del texto
  renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
  renderer.SetDrawColor(0, 0, 0, abierto ? 160 : 90);
  renderer.FillRect(Rect(MARGEN,
                         base - lineas_totales * ALTO_LINEA - MARGEN / 2,
                         ANCHO_CHAT, lineas_totales * ALTO_LINEA + MARGEN));

  // acá se muestran todos los mensajes
  int y = base - lineas_totales * ALTO_LINEA;
  for (Texture &linea : lineas) {
    renderer.Copy(linea, SDL2pp::NullOpt,
                  Rect(MARGEN * 2, y, linea.GetWidth(), linea.GetHeight()));
    y += ALTO_LINEA;
  }

  // y aca muestro lo que se está escribiendo ahora para q sea mas user friendly
  if (abierto) {
    Texture entrada(
        renderer, fuente.RenderUTF8_Blended("> " + escribiendo + "_", BLANCO));
    renderer.Copy(entrada, SDL2pp::NullOpt,
                  Rect(MARGEN * 2, y, entrada.GetWidth(), entrada.GetHeight()));
  }
}