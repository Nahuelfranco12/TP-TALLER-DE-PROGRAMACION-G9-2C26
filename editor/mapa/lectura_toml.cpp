#include "lectura_toml.h"

#include <stdexcept>
#include <string>

#include "constantes_mapa.h"

std::string campo(const std::string &donde, const char *clave) {
  if (donde.empty())
    return clave;
  return donde + SEPARADOR_CAMPO_MAPA + clave;
}

const toml::table &leerTabla(const toml::table &tabla, const char *clave) {
  const toml::table *subtabla = tabla[clave].as_table();
  if (subtabla == nullptr)
    throw std::runtime_error(TEXTO_ERROR_CAMPO + std::string(clave));
  return *subtabla;
}

const toml::array &leerArray(const toml::table &tabla, const char *clave,
                             const std::string &donde) {
  const toml::array *array = tabla[clave].as_array();
  if (array == nullptr)
    throw std::runtime_error(TEXTO_ERROR_CAMPO + campo(donde, clave));
  return *array;
}
