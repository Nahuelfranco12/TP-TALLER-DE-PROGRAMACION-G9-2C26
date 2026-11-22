#ifndef SPRITES_H_
#define SPRITES_H_

#include <QPixmap>
#include <QString>

struct Recorte {
  int x = 0;
  int y = 0;
  int ancho = 0;
  int alto = 0;
};

QPixmap cargarSpriteTratado(const char *rutaSprite, const Recorte &recorte,
                       const QString &nombre, int ancho, int alto);

#endif // SPRITES_H_
