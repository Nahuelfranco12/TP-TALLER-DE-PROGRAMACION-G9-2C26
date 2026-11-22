#include "navegador_paginas.h"
#include <QStackedWidget>

NavegadorPaginas::NavegadorPaginas(QStackedWidget *contenedorPaginas, QObject *parent)
    : QObject(parent), contenedorPaginas(contenedorPaginas) {}

void NavegadorPaginas::irAPagina(QWidget *pagina) {
  historialPaginas.push(contenedorPaginas->currentWidget());
  contenedorPaginas->setCurrentWidget(pagina);
  emit seAbrioPagina(pagina);
}

void NavegadorPaginas::volverPaginaAnterior() {
  if (historialPaginas.isEmpty())
    return;
  contenedorPaginas->setCurrentWidget(historialPaginas.pop());
}
