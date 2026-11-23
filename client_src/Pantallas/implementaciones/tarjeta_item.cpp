#include "tarjeta_item.h"
#include "constantes_pantallas.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>

namespace {
QLabel *crearLabel(const QString &texto, const char *estilo, QWidget *parent) {
  QLabel *label = new QLabel(texto, parent);
  label->setStyleSheet(estilo);
  return label;
}
} // namespace

TarjetaItem::TarjetaItem(const DatosTarjeta &datos, QWidget *parent)
    : QFrame(parent), m_id(datos.id) {
  setSeleccionada(false);
  setFixedHeight(ALTO_TARJETA);
  setCursor(Qt::PointingHandCursor);

  QHBoxLayout *layoutPrincipal = new QHBoxLayout(this);

  if (!datos.imagen.isNull()) {
    QLabel *labelImagen = new QLabel(this);
    labelImagen->setPixmap(datos.imagen.scaled(
        TAMANIO_IMAGEN_TARJETA, TAMANIO_IMAGEN_TARJETA, Qt::KeepAspectRatio));
    labelImagen->setFixedSize(TAMANIO_IMAGEN_TARJETA, TAMANIO_IMAGEN_TARJETA);
    labelImagen->setStyleSheet(ESTILO_SIN_BORDE);
    layoutPrincipal->addWidget(labelImagen);
  }

  QVBoxLayout *layoutTextos = new QVBoxLayout();
  layoutPrincipal->addLayout(layoutTextos);
  layoutTextos->addWidget(
      crearLabel(datos.titulo, ESTILO_TARJETA_TITULO, this));
  if (!datos.subtitulo.isEmpty())
    layoutTextos->addWidget(
        crearLabel(datos.subtitulo, ESTILO_TARJETA_SUBTITULO, this));

  if (!datos.textoExtra.isEmpty())
    layoutPrincipal->addWidget(
        crearLabel(datos.textoExtra, ESTILO_TARJETA_EXTRA, this), 0,
        Qt::AlignRight);

  QPushButton *boton = new QPushButton(datos.textoBoton, this);
  boton->setStyleSheet(ESTILO_TARJETA_BOTON);
  layoutPrincipal->addWidget(boton, 0, Qt::AlignRight);

  connect(boton, &QPushButton::clicked, this,
          [this]() { emit clickeada(this); });
}

void TarjetaItem::mousePressEvent(QMouseEvent *event) {
  emit clickeada(this);
  QFrame::mousePressEvent(event);
}

void TarjetaItem::setSeleccionada(bool estado) {
  if (estado)
    setStyleSheet(ESTILO_TARJETA_SELECCIONADA);
  else
    setStyleSheet(ESTILO_TARJETA_NO_SELECCIONADA);
}

QString TarjetaItem::getId() const { return m_id; }
