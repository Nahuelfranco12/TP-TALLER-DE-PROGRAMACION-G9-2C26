#ifndef PANTALLAFINJUEGO_H
#define PANTALLAFINJUEGO_H

#include <QMainWindow>

namespace Ui {
class PantallaFinJuego;
}

class PantallaFinJuego : public QMainWindow {
  Q_OBJECT

public:
  explicit PantallaFinJuego(QWidget *parent = nullptr);
  ~PantallaFinJuego() override;

private:
  Ui::PantallaFinJuego *ui;
};
#endif // PANTALLAFINJUEGO_H
