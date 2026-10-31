#include "pantalla.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QFontDatabase::addApplicationFont(
      ":/fuentes/assets/fuentes/Stardew_Valley.otf");
  Pantalla w;
  w.show();
  return QApplication::exec();
}
