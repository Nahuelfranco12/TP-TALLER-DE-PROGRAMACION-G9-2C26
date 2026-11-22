#ifndef NAVEGADOR_PAGINAS_H_
#define NAVEGADOR_PAGINAS_H_

#include <QObject>
#include <QStack>
#include <QWidget>

class QStackedWidget;
class NavegadorPaginas : public QObject {
  Q_OBJECT

public:

  explicit NavegadorPaginas(QStackedWidget *contenedorPaginas, QObject *parent = nullptr);
  void irAPagina(QWidget *pagina);
  void volverPaginaAnterior();

signals:
  void seAbrioPagina(QWidget *pagina);

private:
  QStackedWidget *contenedorPaginas;
  QStack<QWidget *> historialPaginas;
};

#endif // NAVEGADOR_PAGINAS_H_
