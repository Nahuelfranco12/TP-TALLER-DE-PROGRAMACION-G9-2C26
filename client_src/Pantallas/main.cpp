#include "pantalla.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QFontDatabase::addApplicationFont(":/fuentes/assets/Stardew_Valley.ttf");
  Pantalla w;
  w.show();
  return QApplication::exec();
}
