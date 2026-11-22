#include "navegador_paginas.h"

NavegadorPaginas::NavegadorPaginas(QStackedWidget *stack, QObject *parent)
    : QObject(parent), contenedorPaginas(stack) {}

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
