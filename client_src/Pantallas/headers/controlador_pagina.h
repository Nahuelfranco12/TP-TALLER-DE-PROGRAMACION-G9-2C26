#ifndef CONTROLADOR_PAGINA_H_
#define CONTROLADOR_PAGINA_H_

#include "navegador_paginas.h"
#include "servicio_lobby.h"
#include <QObject>
#include <QPushButton>

namespace Ui {
class Pantalla;
}

class ControladorPagina : public QObject {
  Q_OBJECT

public:
  ControladorPagina(QWidget &ventana, Ui::Pantalla &ui, NavegadorPaginas &navegador,
                    QObject *parent)
      : QObject(parent), ventana(ventana), ui(ui), navegador(navegador) {}
  virtual void limpiarPagina() = 0;
  virtual void actualizarBotonAvanzar() = 0;

signals:
  void partidaIniciada();

protected:
  QWidget &ventana;
  Ui::Pantalla &ui;
  NavegadorPaginas &navegador;
  void conectarVolver(QPushButton *boton);
  void intentarJugar(ServicioLobby &servicio, const DatosPartida &datos,
                     QPushButton *botonJugar);
};

#endif // CONTROLADOR_PAGINA_H_
