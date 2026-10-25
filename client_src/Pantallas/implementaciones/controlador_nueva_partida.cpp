#include "controlador_nueva_partida.h"
#include "partidas_estaticas.h"
#include "ui_pantalla.h"

ControladorNuevaPartida::ControladorNuevaPartida(Ui::Pantalla& ui, Navegador& navegador, QObject* parent)
    : ControladorPagina(ui, navegador, parent)
    , mundos(new ListaSeleccionable(ui.scrollAreaWidgetContents_2, this))
{
    connect(&navegador, &Navegador::paginaAbierta, this, [this](QWidget* pagina) {
        if (pagina == this->ui.pageNuevaPartida)
            cargarMundos();
    });
    connect(ui.botVolver, &QPushButton::clicked, this, [this]() {
        reiniciar();
        this->navegador.volver();
    });
    connect(ui.botSiguiente, &QPushButton::clicked, this, [this]() {
        this->navegador.irA(this->ui.pageCustomizarPersonaje);
    });
}

void ControladorNuevaPartida::cargarMundos() {
    QList<DatosTarjeta> tarjetas;
    for (const MundoMock& mundo : obtenerMundosDePrueba())
        tarjetas.append(DatosTarjeta{mundo.nombreMundo, mundo.rutaImagen, mundo.nombreMundo, "", "", "Elegir Mapa"});
    mundos->cargar(tarjetas);
}

void ControladorNuevaPartida::reiniciar() {
    mundos->deseleccionar();
    ui.campoNOmbrePartida->clear();
}
