#include "navegador.h"
#include <QStackedWidget>

Navegador::Navegador(QStackedWidget *stack, QObject *parent)
    : QObject(parent), stack(stack) {}

void Navegador::irA(QWidget *pagina) {
  historial.push(stack->currentWidget());
  stack->setCurrentWidget(pagina);
  emit paginaAbierta(pagina);
}

void Navegador::volver() {
  if (historial.isEmpty())
    return;
  stack->setCurrentWidget(historial.pop());
}
