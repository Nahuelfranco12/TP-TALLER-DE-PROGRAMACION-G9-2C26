#include "ventanaeditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VentanaEditor w;
    w.show();
    return QApplication::exec();
}
