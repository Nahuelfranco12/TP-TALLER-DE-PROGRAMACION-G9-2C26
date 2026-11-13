#ifndef VENTANAEDITOR_H
#define VENTANAEDITOR_H

#include "datos_editor.h"
#include <QMainWindow>

namespace Ui {
class VentanaEditor;
}

class VentanaEditor : public QMainWindow {
  Q_OBJECT

public:
  explicit VentanaEditor(QWidget *parent = nullptr);
  ~VentanaEditor() override;

private:
  Ui::VentanaEditor *ui;
  DatosEditor datos;
};
#endif // VENTANAEDITOR_H
