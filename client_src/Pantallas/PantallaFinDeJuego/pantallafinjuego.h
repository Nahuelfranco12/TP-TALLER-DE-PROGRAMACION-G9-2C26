#ifndef PANTALLAFINJUEGO_H
#define PANTALLAFINJUEGO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class PantallaFinJuego;
}
QT_END_NAMESPACE

class PantallaFinJuego : public QMainWindow
{
    Q_OBJECT

public:
    explicit PantallaFinJuego(QWidget *parent = nullptr);
    ~PantallaFinJuego() override;

private:
    Ui::PantallaFinJuego *ui;
};
#endif // PANTALLAFINJUEGO_H
