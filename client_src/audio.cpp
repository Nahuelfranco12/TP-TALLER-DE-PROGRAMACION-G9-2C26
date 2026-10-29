#include "audio.h"

#include <SDL_mixer.h>

#include <algorithm>

namespace {
const int PASO_VOLUMEN = 16;
}

Audio::Audio()
    : mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS,
            1024),
      musica_granja("assets/sonidos/musica_granja.ogg"),
      musica_pueblo("assets/sonidos/musica_pueblo.ogg"),
      sonido_pasos("assets/sonidos/paso.wav"), suena_granja(true),
      volumen_musica(MIX_MAX_VOLUME / 2), volumen_pasos(MIX_MAX_VOLUME / 2) {
  mixer.SetMusicVolume(volumen_musica);
  sonido_pasos.SetVolume(volumen_pasos);
  mixer.PlayMusic(musica_granja, -1);
}

void Audio::cambiar_musica() {
  suena_granja = !suena_granja;
  if (suena_granja) {
    mixer.PlayMusic(musica_granja, -1);
  } else {
    mixer.PlayMusic(musica_pueblo, -1);
  }
}

void Audio::bajar_volumen_musica() {
  volumen_musica = std::max(0, volumen_musica - PASO_VOLUMEN);
  mixer.SetMusicVolume(volumen_musica);
}

void Audio::subir_volumen_musica() {
  volumen_musica = std::min(MIX_MAX_VOLUME, volumen_musica + PASO_VOLUMEN);
  mixer.SetMusicVolume(volumen_musica);
}

void Audio::bajar_volumen_pasos() {
  volumen_pasos = std::max(0, volumen_pasos - PASO_VOLUMEN);
  sonido_pasos.SetVolume(volumen_pasos);
}

void Audio::subir_volumen_pasos() {
  volumen_pasos = std::min(MIX_MAX_VOLUME, volumen_pasos + PASO_VOLUMEN);
  sonido_pasos.SetVolume(volumen_pasos);
}

void Audio::reproducir_paso() { mixer.PlayChannel(-1, sonido_pasos, 0); }

int Audio::obtener_volumen_musica() const {
	return volumen_musica;
}

void Audio::poner_musica_granja() {
	suena_granja = true;
	mixer.PlayMusic(musica_granja, -1);
}

void Audio::poner_musica_caverna() {
	suena_granja = false;
	mixer.PlayMusic(musica_pueblo, -1);
}