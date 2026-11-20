#include "navegador_paginas.h"
#include <QStackedWidget>

NavegadorPaginas::NavegadorPaginas(QStackedWidget *contenedorPaginas, QObject *parent)
    : QObject(parent), contenedorPaginas(contenedorPaginas) {}

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
