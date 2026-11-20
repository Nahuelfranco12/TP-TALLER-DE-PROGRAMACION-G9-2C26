#ifndef NAVEGADOR_PAGINAS_H_
#define NAVEGADOR_PAGINAS_H_

#include <QObject>
#include <QStack>
#include <QStackedWidget>

class NavegadorPaginas : public QObject {
  Q_OBJECT

public:
  explicit NavegadorPaginas(QStackedWidget *stack, QObject *parent = nullptr);

  void irAPagina(QWidget *pagina);
  void volver();

signals:
  void paginaAbierta(QWidget *pagina);

private:
  QStackedWidget *contenedorPaginas;
  QStack<QWidget *> historialPaginas;
};

#endif // NAVEGADOR_PAGINAS_H_
