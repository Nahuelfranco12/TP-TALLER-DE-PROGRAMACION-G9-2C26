#ifndef VENTANAEDITOR_H_
#define VENTANAEDITOR_H_

#include <memory>

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
  std::unique_ptr<Ui::VentanaEditor> ui;
  DatosEditor datos;
};
#endif // VENTANAEDITOR_H_
