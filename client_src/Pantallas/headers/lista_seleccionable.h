#ifndef LISTA_SELECCIONABLE_H
#define LISTA_SELECCIONABLE_H

#include "tarjeta_item.h"
#include <QList>
#include <QObject>
#include <QWidget>
#include <functional>

class ListaSeleccionable : public QObject {
  Q_OBJECT

public:
  explicit ListaSeleccionable(QWidget *contenedor, QObject *parent = nullptr);

  void cargar(const QList<DatosTarjeta> &items);
  void deseleccionar();

  bool haySeleccion() const;
  QString seleccionado() const;

  void setAlSeleccionar(std::function<void()> accion);

private:
  QWidget *contenedor;
  TarjetaItem *tarjetaSeleccionada = nullptr;
  std::function<void()> accionAlSeleccionar = nullptr;

  void limpiar();
  void seleccionar(TarjetaItem *tarjeta);
};

#endif // LISTA_SELECCIONABLE_H
