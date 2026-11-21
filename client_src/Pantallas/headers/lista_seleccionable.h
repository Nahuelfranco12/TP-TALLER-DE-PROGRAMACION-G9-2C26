#ifndef LISTA_SELECCIONABLE_H_
#define LISTA_SELECCIONABLE_H_

#include "dtos_pantallas.h"
#include <QList>
#include <QObject>
#include <QString>
#include <functional>

class QWidget;
class TarjetaSeleccionable;

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
  TarjetaSeleccionable *tarjetaSeleccionada = nullptr;
  std::function<void()> accionAlSeleccionar = nullptr;

  void limpiar();
  void seleccionar(TarjetaSeleccionable *tarjeta);
};

#endif // LISTA_SELECCIONABLE_H_
