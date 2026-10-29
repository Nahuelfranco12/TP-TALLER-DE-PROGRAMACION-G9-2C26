#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2pp/SDL2pp.hh>

class Audio {
private:
	SDL2pp::Mixer mixer;
    SDL2pp::Music musica_granja;
    SDL2pp::Music musica_pueblo;
    SDL2pp::Chunk sonido_pasos;

    bool suena_granja;
    int volumen_musica;
    int volumen_pasos;

public:
	// Abrir el audio, cargar los sonidos y arrancar la música
    Audio();

    // Alternar entre m´usicas
    void cambiar_musica();

    void poner_musica_granja();
    void poner_musica_caverna();

    // Volúmenes
    void bajar_volumen_musica();
    void subir_volumen_musica();
    void bajar_volumen_pasos();
    void subir_volumen_pasos();

    // Hacer sonar un paso
    void reproducir_paso();

    int obtener_volumen_musica() const;
};

#endif
