#include "lista_seleccionable.h"
#include "tarjeta_seleccionable.h"
#include <QVBoxLayout>

ListaSeleccionable::ListaSeleccionable(QWidget *contenedor, QObject *parent)
    : QObject(parent), contenedor(contenedor) {
  if (contenedor->layout() == nullptr)
    contenedor->setLayout(new QVBoxLayout());
}

void ListaSeleccionable::cargar(const QList<DatosTarjeta> &items) {
  limpiar();
  for (const DatosTarjeta &datos : items) {
    TarjetaSeleccionable *tarjeta = new TarjetaSeleccionable(datos, contenedor);
    connect(tarjeta, &TarjetaSeleccionable::tarjetaClickeada, this,
            &ListaSeleccionable::seleccionar);
    contenedor->layout()->addWidget(tarjeta);
  }
}

void ListaSeleccionable::deseleccionar() {
  if (tarjetaSeleccionada != nullptr)
    tarjetaSeleccionada->setSeleccionada(false);
  tarjetaSeleccionada = nullptr;
}

bool ListaSeleccionable::haySeleccion() const {
  return tarjetaSeleccionada != nullptr;
}

QString ListaSeleccionable::seleccionado() const {
  if (!haySeleccion())
    return QString();
  return tarjetaSeleccionada->getId();
}

void ListaSeleccionable::limpiar() {
  tarjetaSeleccionada = nullptr;
  QLayoutItem *item;
  while ((item = contenedor->layout()->takeAt(0)) != nullptr) {
    delete item->widget();
    delete item;
  }
}

void ListaSeleccionable::setAlSeleccionar(std::function<void()> accion) {
  accionAlSeleccionar = accion;
}

void ListaSeleccionable::seleccionar(TarjetaSeleccionable *tarjeta) {
  deseleccionar();
  tarjeta->setSeleccionada(true);
  tarjetaSeleccionada = tarjeta;
  if (accionAlSeleccionar)
    accionAlSeleccionar();
}
