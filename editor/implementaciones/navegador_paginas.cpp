#include "navegador_paginas.h"

NavegadorPaginas::NavegadorPaginas(QStackedWidget *stack, QObject *parent)
    : QObject(parent), contenedorPaginas(stack) {}

void NavegadorPaginas::irAPagina(QWidget *pagina) {
  historialPaginas.push(contenedorPaginas->currentWidget());
  contenedorPaginas->setCurrentWidget(pagina);
  emit paginaAbierta(pagina);
}

void NavegadorPaginas::volver() {
  if (historialPaginas.isEmpty())
    return;
  contenedorPaginas->setCurrentWidget(historialPaginas.pop());
}
