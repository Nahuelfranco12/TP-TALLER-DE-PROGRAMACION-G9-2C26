#ifndef PANTALLA_H
#define PANTALLA_H

#include <QMainWindow>

namespace Ui {
class Pantalla;
}

class Pantalla : public QMainWindow {
  Q_OBJECT

public:
  explicit Pantalla(QWidget *parent = nullptr);
  ~Pantalla() override;

private:
  Ui::Pantalla *ui;
};
#endif // PANTALLA_H
