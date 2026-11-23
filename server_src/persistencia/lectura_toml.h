#ifndef LECTURA_TOML_H_
#define LECTURA_TOML_H_

#include <cstddef>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <toml++/toml.hpp>
#include <utility>
#include <vector>

#include "constantes_persistencia.h"

std::string rutaDelCampo(const std::string &donde, const char *clave);

const toml::table &leerTabla(const toml::table &tabla, const char *clave,
                             const std::string &donde);
const toml::table &leerSubtabla(const toml::table &tabla, const char *clave);

template <typename T>
T leerValor(const toml::table &tabla, const char *clave,
            const std::string &donde) {
  std::optional<T> valor = tabla[clave].value<T>();
  if (!valor)
    throw std::runtime_error(ERROR_PARTIDA_CAMPO + rutaDelCampo(donde, clave));
  return *valor;
}

template <typename T>
T leerEntero(const toml::table &tabla, const char *clave,
             const std::string &donde) {
  std::int64_t valor = leerValor<std::int64_t>(tabla, clave, donde);
  if (!std::in_range<T>(valor))
    throw std::runtime_error(ERROR_PARTIDA_RANGO + rutaDelCampo(donde, clave));
  return static_cast<T>(valor);
}

template <typename T>
std::vector<T> leerLista(const toml::table &tabla, const char *clave,
                         const std::string &donde,
                         T (*leer)(const toml::table &, const std::string &)) {
  std::string lugar = rutaDelCampo(donde, clave);
  const toml::array *array = tabla[clave].as_array();
  if (array == nullptr)
    throw std::runtime_error(ERROR_PARTIDA_CAMPO + lugar);

  std::vector<T> resultado;
  std::size_t numero = PRIMER_ELEMENTO_PARTIDA;
  for (const toml::node &nodo : *array) {
    std::string lugarElemento =
        lugar + SEPARADOR_INDICE_PARTIDA + std::to_string(numero);
    const toml::table *elemento = nodo.as_table();
    if (elemento == nullptr)
      throw std::runtime_error(ERROR_PARTIDA_CAMPO + lugarElemento);
    resultado.push_back(leer(*elemento, lugarElemento));
    ++numero;
  }
  return resultado;
}

#endif // LECTURA_TOML_H_
