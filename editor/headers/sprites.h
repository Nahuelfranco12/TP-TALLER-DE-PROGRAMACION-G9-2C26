#ifndef SPRITES_H_
#define SPRITES_H_

#include <QPixmap>
#include <QString>

#include "editor_dtos.h"

QPixmap spriteDe(const char *recurso, const Recorte &recorte,
                 const QString &nombre, int lado);

#endif  // SPRITES_H_
