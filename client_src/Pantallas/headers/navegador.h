#ifndef NAVEGADOR_H_
#define NAVEGADOR_H_

#include <QObject>
#include <QStack>
#include <QWidget>

class QStackedWidget;

class Navegador : public QObject {
  Q_OBJECT

public:
  explicit Navegador(QStackedWidget *stack, QObject *parent = nullptr);

  void irA(QWidget *pagina);
  void volver();

signals:
  void paginaAbierta(QWidget *pagina);

private:
  QStackedWidget *stack;
  QStack<QWidget *> historial;
};

#endif // NAVEGADOR_H_
