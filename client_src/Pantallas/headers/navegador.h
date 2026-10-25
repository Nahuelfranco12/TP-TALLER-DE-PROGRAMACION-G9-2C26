#ifndef NAVEGADOR_H
#define NAVEGADOR_H

#include <QObject>
#include <QStack>
#include <QStackedWidget>

class Navegador : public QObject
{
    Q_OBJECT

public:
    explicit Navegador(QStackedWidget* stack, QObject* parent = nullptr);

    void irA(QWidget* pagina);
    void volver();

signals:
    void paginaAbierta(QWidget* pagina);

private:
    QStackedWidget* stack;
    QStack<QWidget*> historial;
};

#endif // NAVEGADOR_H
