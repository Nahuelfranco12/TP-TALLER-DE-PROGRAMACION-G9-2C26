#include "lectura_toml.h"

#include <stdexcept>
#include <string>

#include "constantes_persistencia.h"

std::string rutaDelCampo(const std::string &donde, const char *clave) {
  if (donde.empty())
    return clave;
  return donde + SEPARADOR_CAMPO_PARTIDA + clave;
}

const toml::table &leerSubtabla(const toml::table &tabla, const char *clave) {
  return leerTabla(tabla, clave, std::string());
}
