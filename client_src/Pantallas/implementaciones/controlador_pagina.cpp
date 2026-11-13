#include "controlador_pagina.h"
#include "constantes_pantallas.h"
#include <QApplication>
#include <QMessageBox>

void ControladorPagina::intentarJugar(ServicioLobby &servicio,
                                      const DatosPartida &datos,
                                      QPushButton *botonJugar) {
  botonJugar->setEnabled(false);
  ResultadoLobby resultado = servicio.jugar(datos);
  if (resultado.ok) {
    QApplication::quit();
    return;
  }
  QMessageBox::warning(&ventana, TITULO_ERROR_JUGAR, resultado.mensajeError);
  actualizarBotonAvanzar();
}
