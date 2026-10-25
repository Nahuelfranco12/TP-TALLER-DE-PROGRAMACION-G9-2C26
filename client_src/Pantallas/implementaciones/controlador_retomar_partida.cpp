#include "controlador_retomar_partida.h"
#include "partidas_estaticas.h"
#include "ui_pantalla.h"

ControladorRetomarPartida::ControladorRetomarPartida(Ui::Pantalla& ui, Navegador& navegador, QObject* parent)
    : ControladorPagina(ui, navegador, parent)
    , partidas(new ListaSeleccionable(ui.scrollAreaWidgetContents, this))
{
    connect(&navegador, &Navegador::paginaAbierta, this, [this](QWidget* pagina) {
        if (pagina == this->ui.pageRetomarPartida)
            cargarPartidas();
    });
    connect(ui.botVolverRP, &QPushButton::clicked, this, [this]() {
        partidas->deseleccionar();
        this->navegador.volver();
    });
}

void ControladorRetomarPartida::cargarPartidas() {
    QList<DatosTarjeta> tarjetas;
    for (const PartidaGuardada& partida : obtenerPartidasDePrueba()) {
        QString modo = partida.esMultiplayer ? "Multiplayer" : "Singleplayer";
        tarjetas.append(DatosTarjeta{partida.nombrePartida, partida.rutaImagen, partida.nombrePartida,
                                     partida.nombrePersonaje, modo, "Seleccionar"});
    }
    partidas->cargar(tarjetas);
}
