#include "controlador_pagina.h"
#include "constantes_pantallas.h"
#include <QMessageBox>

void ControladorPagina::conectarVolver(QPushButton *boton) {
  connect(boton, &QPushButton::clicked, this, [this]() {
    limpiarPagina();
    navegador.volver();
  });
}

void ControladorPagina::intentarJugar(ServicioLobby &servicio,
                                      const DatosPartida &datos,
                                      QPushButton *botonJugar) {
  botonJugar->setEnabled(false);
  ResultadoLobby resultado = servicio.entrarAJugar(datos);
  if (resultado.ok) {
    emit partidaIniciada();
    return;
  }
  QMessageBox::warning(&ventana, TITULO_ERROR_JUGAR, resultado.mensajeError);
  actualizarBotonAvanzar();
}
