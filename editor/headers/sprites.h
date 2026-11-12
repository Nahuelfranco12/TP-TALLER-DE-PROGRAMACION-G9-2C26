#ifndef SPRITES_H_
#define SPRITES_H_

#include <QPixmap>
#include <QString>

//#include "editor_dtos.h"
#include "catalogo_elementos.h"

QPixmap imagenSpriteDe(const char *rutaSprite, const Recorte &recorte,
                       const QString &nombre, int ancho, int alto);

#endif // SPRITES_H_
