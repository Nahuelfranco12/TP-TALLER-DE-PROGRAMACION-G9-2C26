#ifndef VISTA_ZONA_H_
#define VISTA_ZONA_H_

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <functional>
#include <map>

#include "catalogo_elementos.h"
#include "constantes_qt.h"
#include "mapa_editor.h"
#include "sprites.h"

class QMouseEvent;

class VistaZona : public QGraphicsView {
public:
  explicit VistaZona(QWidget *parent = nullptr);

  template <typename TipoObjeto> void mostrar(const MapaZona<TipoObjeto> &zona);
  void limpiar();
  void setAlClickear(std::function<void(int, int, Qt::MouseButton)> accion);

protected:
  void mousePressEvent(QMouseEvent *evento) override;

private:
  QGraphicsScene *escena;
  std::function<void(int, int, Qt::MouseButton)> accionAlClickear;

  QPixmap imagenTerrenoDe(Terreno terreno) const;
  void dibujarLineasCuadricula(int ancho, int alto);
  template <typename TipoObjeto>
  void dibujarObjeto(const ObjetoColocado<TipoObjeto> &objeto);
};

template <typename TipoObjeto>
void VistaZona::mostrar(const MapaZona<TipoObjeto> &zona) {
  limpiar();
  std::map<Terreno, QPixmap> tiles;
  for (int y = 0; y < zona.alto(); ++y) {
    for (int x = 0; x < zona.ancho(); ++x) {
      Terreno terreno = zona.pintarTerrenoEnCelda(x, y);
      auto tile = tiles.find(terreno);
      if (tile == tiles.end())
        tile = tiles.emplace(terreno, imagenTerrenoDe(terreno)).first;
      escena->addPixmap(tile->second)
          ->setPos(x * TAMANIO_CELDA_MAPA, y * TAMANIO_CELDA_MAPA);
    }
  }
  dibujarLineasCuadricula(zona.ancho(), zona.alto());
  for (const auto &objeto : zona.objetos())
    dibujarObjeto(objeto);
  escena->setSceneRect(0, 0, zona.ancho() * TAMANIO_CELDA_MAPA,
                       zona.alto() * TAMANIO_CELDA_MAPA);
}

template <typename TipoObjeto>
void VistaZona::dibujarObjeto(const ObjetoColocado<TipoObjeto> &objeto) {
  TamanioEnCeldas celdaOcupada = tamanioEnCeldasDe(objeto.tipo);
  int ancho = celdaOcupada.ancho * TAMANIO_CELDA_MAPA;
  int alto = celdaOcupada.alto * TAMANIO_CELDA_MAPA;
  QPixmap imagen;
  const auto *info = infoDe(objeto.tipo);
  if (info == nullptr)
    imagen = imagenSpriteDe("", Recorte{}, TEXTO_DESCONOCIDO, ancho, alto);
  else
    imagen = imagenSpriteDe(info->rutaSprite, info->recorte,
                            QString::fromUtf8(info->nombre), ancho, alto);
  int x = objeto.x * TAMANIO_CELDA_MAPA + (ancho - imagen.width()) / 2;
  int y = objeto.y * TAMANIO_CELDA_MAPA + (alto - imagen.height());
  escena->addPixmap(imagen)->setPos(x, y);
}

#endif // VISTA_ZONA_H_
