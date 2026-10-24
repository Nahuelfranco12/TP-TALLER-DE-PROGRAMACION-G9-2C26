#ifndef PANTALLA_H
#define PANTALLA_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Pantalla;
}
QT_END_NAMESPACE

class Pantalla : public QMainWindow
{
    Q_OBJECT

public:
    explicit Pantalla(QWidget *parent = nullptr);
    ~Pantalla() override;

private:
    Ui::Pantalla *ui;
    void cargarListaPartidas();
};
#endif // PANTALLA_H
