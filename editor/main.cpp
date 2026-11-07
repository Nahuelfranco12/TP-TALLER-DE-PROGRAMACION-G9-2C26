#include "ventanaeditor.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QFontDatabase::addApplicationFont(":/Fuentes/stardew_valley.ttf");
  VentanaEditor w;
  w.show();
  return QApplication::exec();
}
