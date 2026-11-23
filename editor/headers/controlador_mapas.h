#ifndef CONTROLADOR_MAPAS_H_
#define CONTROLADOR_MAPAS_H_

#include <cstddef>
#include <vector>

#include "catalogo_elementos.h"
#include "controlador_pagina_editor.h"
#include "datos_editor.h"

class QWidget;
class VistaZona;

class ControladorMapas : public ControladorPaginaEditor {
public:
  ControladorMapas(QWidget &ventana, Ui::VentanaEditor &ui,
                   NavegadorPaginas &navegador, DatosEditor &datos,
                   QObject *parent = nullptr);

private:
  DatosEditor &datos;
  Zona zonaActual = Zona::Granja;
  std::size_t indiceNivelCaverna = 0;

  void reiniciarPaginaMapas();
  Zona zonaDePestania(QWidget *pestania) const;
  void cambiarZonaActual(Zona zona);
  void cargarPaletaDeZona(Zona zona);
  template <typename T>
  void agregarElementosAPaleta(const std::vector<InfoElemento<T>> &elementos);

  MapaZona<ElementosCaverna> &nivelCavernaActual();
  void cambiarNivelCaverna(int nivel);

  void mostrarDimensionesEnCampos(Dimensiones dimensiones);
  void redimensionarZonaActual();

  void dibujarTodasLasZonas();
  template <typename T>
  void manejarClickEnCelda(MapaZona<T> &zona, VistaZona *vista, int x, int y,
                           Qt::MouseButton boton);
  template <typename T>
  void colocarElementoSeleccionadEnCelda(MapaZona<T> &zona, VistaZona *vista,
                                         int x, int y);

  void validarYExportarMapa();
};

#endif // CONTROLADOR_MAPAS_H_
