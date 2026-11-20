#ifndef CONTROLADOR_PAGINA_EDITOR_H_
#define CONTROLADOR_PAGINA_EDITOR_H_

#include <QDir>
#include <QObject>
#include <QString>

#include "constantes_qt.h"
#include "navegador_paginas.h"

class QWidget;

namespace Ui {
class VentanaEditor;
}

class ControladorPaginaEditor : public QObject {
public:
  ControladorPaginaEditor(QWidget &ventana, Ui::VentanaEditor &ui,
                          NavegadorPaginas &navegador, QObject *parent)
      : QObject(parent), ventana(ventana), ui(ui), navegador(navegador) {}

protected:
  QWidget &ventana;
  Ui::VentanaEditor &ui;
  NavegadorPaginas &navegador;

  static QString carpetaMapas() {
    QDir actual = QDir::current();
    actual.mkpath(CARPETA_MAPAS);
    return actual.absoluteFilePath(CARPETA_MAPAS);
  }
};

#endif // CONTROLADOR_PAGINA_EDITOR_H_
