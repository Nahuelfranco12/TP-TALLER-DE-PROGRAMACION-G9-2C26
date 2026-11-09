#ifndef CONTROLADOR_MAPAS_H_
#define CONTROLADOR_MAPAS_H_

#include <cstddef>
#include <vector>

#include "controlador_pagina_editor.h"
#include "datos_editor.h"
#include "editor_dtos.h"

class QWidget;
class VistaZona;

class ControladorMapas : public ControladorPaginaEditor {
public:
  ControladorMapas(Ui::VentanaEditor &ui, Navegador &navegador,
                   DatosEditor &datos, QObject *parent = nullptr);
  void limpiarPagina() override;

private:
  DatosEditor &datos;
  Zona zonaActual = Zona::Granja;
  std::size_t nivelCaverna = 0;

  Zona zonaDe(QWidget *pestania) const;
  void cambiarDeZona(Zona zona);
  void cargarPaleta(Zona zona);
  template <typename T>
  void agregarAPaleta(const std::vector<InfoElemento<T>> &elementos);

  MapaZona<ElementosCaverna> &cavernaActual();
  void cambiarDeNivel(int nivel);

  Dimensiones dimensionesDe(Zona zona) const;
  void mostrarDimensiones(Dimensiones dimensiones);
  void aplicarDimensiones();

  void dibujarMapa();
  template <typename T>
  void clickEn(MapaZona<T> &zona, VistaZona *vista, int x, int y,
               Qt::MouseButton boton);
  template <typename T>
  void colocarSeleccionado(MapaZona<T> &zona, int x, int y);
};

#endif // CONTROLADOR_MAPAS_H_
