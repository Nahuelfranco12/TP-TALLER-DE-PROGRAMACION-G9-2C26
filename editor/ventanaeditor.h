#ifndef VENTANAEDITOR_H
#define VENTANAEDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class VentanaEditor;
}
QT_END_NAMESPACE

class VentanaEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit VentanaEditor(QWidget *parent = nullptr);
    ~VentanaEditor() override;

private:
    Ui::VentanaEditor *ui;
};
#endif // VENTANAEDITOR_H
