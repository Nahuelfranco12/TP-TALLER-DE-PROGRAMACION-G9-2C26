#ifndef VISTA_ZONA_H_
#define VISTA_ZONA_H_

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <functional>
#include <map>

#include "constantes.h"
#include "editor_dtos.h"
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

  QPixmap tileDe(Terreno terreno) const;
  void dibujarCuadricula(int ancho, int alto);
  template <typename TipoObjeto>
  void dibujarObjeto(const ObjetoColocado<TipoObjeto> &objeto);
};

template <typename TipoObjeto>
void VistaZona::mostrar(const MapaZona<TipoObjeto> &zona) {
  limpiar();
  std::map<Terreno, QPixmap> tiles; // una imagen por tipo de terreno
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
  for (const auto &objeto : zona.objetos())
    dibujarObjeto(objeto);
  escena->setSceneRect(0, 0, zona.ancho() * LADO_TILE, zona.alto() * LADO_TILE);
}

template <typename TipoObjeto>
void VistaZona::dibujarObjeto(const ObjetoColocado<TipoObjeto> &objeto) {
  Huella huella = huellaDe(objeto.tipo);
  int ancho = huella.ancho * LADO_TILE;
  int alto = huella.alto * LADO_TILE;
  QPixmap imagen;
  const auto *info = infoDe(objeto.tipo);
  if (info == nullptr)
    imagen = spriteDe("", Recorte{}, TEXTO_DESCONOCIDO, ancho, alto);
  else
    imagen = spriteDe(info->recurso, info->recorte,
                      QString::fromUtf8(info->nombre), ancho, alto);
  int x = objeto.x * LADO_TILE + (ancho - imagen.width()) / 2;
  int y = objeto.y * LADO_TILE + (alto - imagen.height());
  escena->addPixmap(imagen)->setPos(x, y);
}

#endif // VISTA_ZONA_H_
