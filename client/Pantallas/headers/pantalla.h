#ifndef PANTALLA_H
#define PANTALLA_H

#include <QMainWindow>
#include <QPushButton>
#include <functional>
#include "ui_pantalla.h"

typedef std::function<void()> AccionExtra;

class Pantalla : public QMainWindow
{
    Q_OBJECT

public:
    explicit Pantalla(QWidget *parent = nullptr);
    ~Pantalla() override;

private:
    Ui::Pantalla *ui;
    QWidget *pantallaOrigen;

    void configurarFuentes();
    void configurarNavegacion();
    void cargarListaPartidas();
    void conectarBoton(QPushButton* boton, QWidget* destino, QWidget* nuevoOrigen = nullptr, AccionExtra accion = nullptr);
};
#endif // PANTALLA_H