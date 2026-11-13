#ifndef CONTROLADOR_PAGINA_H
#define CONTROLADOR_PAGINA_H

#include "constantes_pantallas.h"
#include "navegador.h"
#include "servicio_lobby.h"
#include <QApplication>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>

namespace Ui {
class Pantalla;
}

class ControladorPagina : public QObject {
public:
  ControladorPagina(Ui::Pantalla &ui, Navegador &navegador, QObject *parent)
      : QObject(parent), ui(ui), navegador(navegador) {}
  virtual void limpiarPagina() = 0;
  virtual void actualizarBotonAvanzar() = 0;

protected:
  Ui::Pantalla &ui;
  Navegador &navegador;
  void intentarJugar(ServicioLobby &servicio, const DatosPartida &datos,
                     QPushButton *botonJugar) {
    botonJugar->setEnabled(false);
    ResultadoLobby resultado = servicio.jugar(datos);
    if (resultado.ok) {
      QApplication::quit();
      return;
    }
    QMessageBox::warning(botonJugar->window(), TITULO_ERROR_JUGAR,
                         resultado.mensajeError);
    actualizarBotonAvanzar();
  }
};

#endif // CONTROLADOR_PAGINA_H
