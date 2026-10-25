#include "controlador_unirse_partida.h"
#include "ui_pantalla.h"

ControladorUnirsePartida::ControladorUnirsePartida(Ui::Pantalla& ui, Navegador& navegador, QObject* parent)
    : ControladorPagina(ui, navegador, parent)
{
    connect(ui.botVolverUP, &QPushButton::clicked, this, [this]() {
        this->navegador.volver();
    });
    connect(ui.botSiguienteUP, &QPushButton::clicked, this, [this]() {
        this->navegador.irA(this->ui.pageCustomizarPersonaje);
    });
}
