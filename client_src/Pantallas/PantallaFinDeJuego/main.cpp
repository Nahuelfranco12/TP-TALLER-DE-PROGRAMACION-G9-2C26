#include "pantallafinjuego.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(
        ":/fuentes/assets/fuentes/Stardew_Valley.otf");
    PantallaFinJuego w;
    w.show();
    return QApplication::exec();
}