#ifndef LISTA_SELECCIONABLE_H
#define LISTA_SELECCIONABLE_H

#include <QList>
#include <QObject>
#include <QWidget>
#include "tarjeta_item.h"

class ListaSeleccionable : public QObject
{
    Q_OBJECT

public:
    explicit ListaSeleccionable(QWidget* contenedor, QObject* parent = nullptr);

    void cargar(const QList<DatosTarjeta>& items);
    void deseleccionar();

    bool haySeleccion() const;
    QString seleccionado() const;

private:
    QWidget* contenedor;
    TarjetaItem* tarjetaSeleccionada = nullptr;

    void limpiar();
    void seleccionar(TarjetaItem* tarjeta);
};

#endif // LISTA_SELECCIONABLE_H
