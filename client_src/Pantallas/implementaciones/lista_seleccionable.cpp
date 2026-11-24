#include "lista_seleccionable.h"
#include "tarjeta_seleccionable.h"
#include <QVBoxLayout>

ListaSeleccionable::ListaSeleccionable(QWidget *contenedor, QObject *parent)
    : QObject(parent), contenedor(contenedor) {
  if (contenedor->layout() == nullptr)
    contenedor->setLayout(new QVBoxLayout());
}

void ListaSeleccionable::cargarTarjetas(const QList<DatosTarjeta> &items) {
  borrarTodasLasTarjetas();
  for (const DatosTarjeta &datos : items) {
    TarjetaSeleccionable *tarjeta = new TarjetaSeleccionable(datos, contenedor);
    connect(tarjeta, &TarjetaSeleccionable::tarjetaClickeada, this,
            &ListaSeleccionable::seleccionarTarjeta);
    contenedor->layout()->addWidget(tarjeta);
  }
}

void ListaSeleccionable::deseleccionarTarjeta() {
  if (tarjetaSeleccionada != nullptr)
    tarjetaSeleccionada->setSeleccionada(false);
  tarjetaSeleccionada = nullptr;
}

bool ListaSeleccionable::hayTarjetaSeleccionada() const {
  return tarjetaSeleccionada != nullptr;
}

QString ListaSeleccionable::idTarjetaSeleccionada() const {
  if (!hayTarjetaSeleccionada())
    return QString();
  return tarjetaSeleccionada->getId();
}

void ListaSeleccionable::borrarTodasLasTarjetas() {
  tarjetaSeleccionada = nullptr;
  QLayoutItem *item;
  while ((item = contenedor->layout()->takeAt(0)) != nullptr) {
    delete item->widget();
    delete item;
  }
}

void ListaSeleccionable::setAccionAlSeleccionarTarjeta(
    std::function<void()> accion) {
  accionAlSeleccionar = accion;
}

void ListaSeleccionable::seleccionarTarjeta(TarjetaSeleccionable *tarjeta) {
  deseleccionarTarjeta();
  tarjeta->setSeleccionada(true);
  tarjetaSeleccionada = tarjeta;
  if (accionAlSeleccionar)
    accionAlSeleccionar();
}
