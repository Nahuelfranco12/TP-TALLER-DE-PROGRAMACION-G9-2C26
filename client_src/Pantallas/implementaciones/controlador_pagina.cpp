#include "controlador_pagina.h"
#include "constantes_pantallas.h"
#include <QMessageBox>

void ControladorPagina::conectarBotonVolver(QPushButton *boton) {
  connect(boton, &QPushButton::clicked, this, [this]() {
    reiniciarPagina();
    navegador.volverPaginaAnterior();
  });
}

void ControladorPagina::intentarEntrarAJugar(ServicioLobby &servicio,
                                             const DatosPartida &datos,
                                             QPushButton *botonJugar) {
  botonJugar->setEnabled(false);
  ResultadoLobby resultado = servicio.entrarAJugar(datos);
  if (resultado.ok) {
    emit seInicioPartida();
    return;
  }
  QMessageBox::warning(&ventana, TITULO_ERROR_JUGAR, resultado.mensajeError);
  actualizarEstadoBotonAvanzar();
}
