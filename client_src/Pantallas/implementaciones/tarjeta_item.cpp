#include "tarjeta_item.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>

namespace {
const int ALTO_TARJETA = 80;
const int TAMANIO_IMAGEN = 64;

const char *ESTILO_TITULO = "color: #f1b356; font-family: 'Stardew Valley'; "
                            "font-size: 18px; border: none;";
const char *ESTILO_SUBTITULO = "color: white; font-family: 'Stardew Valley'; "
                               "font-size: 14px; border: none;";
const char *ESTILO_EXTRA = "color: #f1b356; font-family: 'Stardew Valley'; "
                           "font-size: 14px; border: none;";
const char *ESTILO_BOTON =
    "background-color: #f1b356; color: #3b2010; font-weight: bold; "
    "border-radius: 3px; padding: 5px;";
const char *ESTILO_SELECCIONADA =
    "background-color: #5c341a; border: 2px solid #f1b356; border-radius: 5px;";
const char *ESTILO_NO_SELECCIONADA =
    "background-color: #3b2010; border: 2px solid #6b4020; border-radius: 5px;";

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

  QLabel *labelImagen = new QLabel(this);
  labelImagen->setPixmap(
      datos.imagen.scaled(TAMANIO_IMAGEN, TAMANIO_IMAGEN, Qt::KeepAspectRatio));
  labelImagen->setFixedSize(TAMANIO_IMAGEN, TAMANIO_IMAGEN);
  labelImagen->setStyleSheet("border: none;");
  layoutPrincipal->addWidget(labelImagen);

  QVBoxLayout *layoutTextos = new QVBoxLayout();
  layoutTextos->addWidget(crearLabel(datos.titulo, ESTILO_TITULO, this));
  if (!datos.subtitulo.isEmpty())
    layoutTextos->addWidget(
        crearLabel(datos.subtitulo, ESTILO_SUBTITULO, this));
  layoutPrincipal->addLayout(layoutTextos);

  if (!datos.textoExtra.isEmpty())
    layoutPrincipal->addWidget(crearLabel(datos.textoExtra, ESTILO_EXTRA, this),
                               0, Qt::AlignRight);

  QPushButton *boton = new QPushButton(datos.textoBoton, this);
  boton->setStyleSheet(ESTILO_BOTON);
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
    setStyleSheet(ESTILO_SELECCIONADA);
  else
    setStyleSheet(ESTILO_NO_SELECCIONADA);
}

QString TarjetaItem::getId() const { return m_id; }
