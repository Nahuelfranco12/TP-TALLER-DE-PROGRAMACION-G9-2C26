#ifndef VISTA_ZONA_H_
#define VISTA_ZONA_H_

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <map>

#include "constantes.h"
#include "mapa_editor.h"

class QGraphicsScene;

class VistaZona : public QGraphicsView {
 public:
  explicit VistaZona(QWidget *parent = nullptr);

  template <typename TipoObjeto>
  void mostrar(const MapaZona<TipoObjeto> &zona);
  void limpiar();

 private:
  QGraphicsScene *escena;

  QPixmap tileDe(Terreno terreno) const;
  void dibujarCuadricula(int ancho, int alto);
};

template <typename TipoObjeto>
void VistaZona::mostrar(const MapaZona<TipoObjeto> &zona) {
  limpiar();
  std::map<Terreno, QPixmap> tiles;
  for (int y = 0; y < zona.alto(); ++y) {
    for (int x = 0; x < zona.ancho(); ++x) {
      Terreno terreno = zona.terrenoEn(x, y);
      auto tile = tiles.find(terreno);
      if (tile == tiles.end())
        tile = tiles.emplace(terreno, tileDe(terreno)).first;
      escena->addPixmap(tile->second)->setPos(x * LADO_TILE, y * LADO_TILE);
    }
  }
  dibujarCuadricula(zona.ancho(), zona.alto());
  escena->setSceneRect(0, 0, zona.ancho() * LADO_TILE,
                       zona.alto() * LADO_TILE);
}

#endif  // VISTA_ZONA_H_
