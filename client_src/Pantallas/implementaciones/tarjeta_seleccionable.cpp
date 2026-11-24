#include "tarjeta_seleccionable.h"
#include "constantes_pantallas.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>

namespace {
QLabel *crearTextoConEstilo(const QString &texto, const char *estilo,
                            QWidget *parent) {
  QLabel *label = new QLabel(texto, parent);
  label->setStyleSheet(estilo);
  return label;
}
} // namespace

TarjetaSeleccionable::TarjetaSeleccionable(const DatosTarjeta &datos,
                                           QWidget *parent)
    : QFrame(parent), id(datos.id) {
  setSeleccionada(false);
  setFixedHeight(ALTO_TARJETA);
  setCursor(Qt::PointingHandCursor);

  QHBoxLayout *filaTarjeta = new QHBoxLayout(this);

  if (!datos.imagen.isNull()) {
    QLabel *imagenTarjeta = new QLabel(this);
    imagenTarjeta->setPixmap(datos.imagen.scaled(
        TAMANIO_IMAGEN_TARJETA, TAMANIO_IMAGEN_TARJETA, Qt::KeepAspectRatio));
    imagenTarjeta->setFixedSize(TAMANIO_IMAGEN_TARJETA, TAMANIO_IMAGEN_TARJETA);
    imagenTarjeta->setStyleSheet(ESTILO_SIN_BORDE);
    filaTarjeta->addWidget(imagenTarjeta);
  }

  QVBoxLayout *columnaTextos = new QVBoxLayout();
  filaTarjeta->addLayout(columnaTextos);
  columnaTextos->addWidget(
      crearTextoConEstilo(datos.titulo, ESTILO_TARJETA_TITULO, this));
  if (!datos.subtitulo.isEmpty())
    columnaTextos->addWidget(
        crearTextoConEstilo(datos.subtitulo, ESTILO_TARJETA_SUBTITULO, this));

  if (!datos.textoExtra.isEmpty())
    filaTarjeta->addWidget(
        crearTextoConEstilo(datos.textoExtra, ESTILO_TARJETA_EXTRA, this), 0,
        Qt::AlignRight);

  QPushButton *botonSeleccionar = new QPushButton(datos.textoBoton, this);
  botonSeleccionar->setStyleSheet(ESTILO_TARJETA_BOTON);
  filaTarjeta->addWidget(botonSeleccionar, 0, Qt::AlignRight);

  connect(botonSeleccionar, &QPushButton::clicked, this,
          [this]() { emit tarjetaClickeada(this); });
}

void TarjetaSeleccionable::mousePressEvent(QMouseEvent *event) {
  emit tarjetaClickeada(this);
  QFrame::mousePressEvent(event);
}

void TarjetaSeleccionable::setSeleccionada(bool estado) {
  if (estado)
    setStyleSheet(ESTILO_TARJETA_SELECCIONADA);
  else
    setStyleSheet(ESTILO_TARJETA_NO_SELECCIONADA);
}

QString TarjetaSeleccionable::getId() const { return id; }
