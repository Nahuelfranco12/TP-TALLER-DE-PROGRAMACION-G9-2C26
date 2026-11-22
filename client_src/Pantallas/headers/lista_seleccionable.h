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

  void cargarTarjetas(const QList<DatosTarjeta> &datosTarjetas);
  void deseleccionarTarjeta();

  bool hayTarjetaSeleccionada() const;
  QString idTarjetaSeleccionada() const;

  void setAccionAlSeleccionarTarjeta(std::function<void()> accion);

private:
  QWidget *contenedor;
  TarjetaSeleccionable *tarjetaSeleccionada = nullptr;
  std::function<void()> accionAlSeleccionar = nullptr;

  void borrarTodasLasTarjetas();
  void seleccionarTarjeta(TarjetaSeleccionable *tarjeta);
};

#endif // LISTA_SELECCIONABLE_H_
