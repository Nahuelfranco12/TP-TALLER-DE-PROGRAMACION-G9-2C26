#ifndef LECTURA_TOML_H_
#define LECTURA_TOML_H_

#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <toml++/toml.hpp>
#include <utility>

#include "constantes_mapa.h"

std::string campo(const std::string &donde, const char *clave);

const toml::table &leerTabla(const toml::table &tabla, const char *clave,
                             const std::string &donde);

const toml::array &leerArray(const toml::table &tabla, const char *clave,
                             const std::string &donde);

template <typename T>
T leerValor(const toml::table &tabla, const char *clave,
            const std::string &donde) {
  std::optional<T> valor = tabla[clave].value<T>();
  if (!valor)
    throw std::runtime_error(TEXTO_ERROR_CAMPO + campo(donde, clave));
  return *valor;
}

template <typename T>
T leerEntero(const toml::table &tabla, const char *clave,
             const std::string &donde) {
  std::int64_t valor = leerValor<std::int64_t>(tabla, clave, donde);
  if (!std::in_range<T>(valor))
    throw std::runtime_error(TEXTO_ERROR_RANGO + campo(donde, clave));
  return static_cast<T>(valor);
}

#endif // LECTURA_TOML_H_
