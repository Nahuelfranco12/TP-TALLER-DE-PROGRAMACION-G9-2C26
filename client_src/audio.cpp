#include "audio.h"

#include <SDL_mixer.h>

#include <algorithm>

#include "constantes_sdl.h"

Audio::Audio()
    : mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS,
            AUDIO_TAMANIO_BUFFER),
      musica_granja(RUTA_MUSICA_GRANJA), musica_caverna(RUTA_MUSICA_CAVERNA),
      musica_pueblo(RUTA_MUSICA_PUEBLO), sonido_pasos(RUTA_SONIDO_PASO),
      musica_actual(AUDIO_MUSICA_GRANJA), volumen_musica(AUDIO_VOLUMEN_INICIAL),
      volumen_pasos(AUDIO_VOLUMEN_INICIAL) {
  mixer.SetMusicVolume(volumen_musica);
  sonido_pasos.SetVolume(volumen_pasos);
  mixer.PlayMusic(musica_granja, AUDIO_REPETIR_SIEMPRE);
}

void Audio::cambiar_musica() {
  int siguiente = (musica_actual + 1) % AUDIO_CANTIDAD_MUSICAS;
  if (siguiente == AUDIO_MUSICA_GRANJA) {
    poner_musica_granja();
  } else if (siguiente == AUDIO_MUSICA_CAVERNA) {
    poner_musica_caverna();
  } else {
    poner_musica_pueblo();
  }
}

void Audio::bajar_volumen_musica() {
  volumen_musica = std::max(0, volumen_musica - AUDIO_INCREMENTO_VOLUMEN);
  mixer.SetMusicVolume(volumen_musica);
}

void Audio::subir_volumen_musica() {
  volumen_musica =
      std::min(MIX_MAX_VOLUME, volumen_musica + AUDIO_INCREMENTO_VOLUMEN);
  mixer.SetMusicVolume(volumen_musica);
}

void Audio::bajar_volumen_pasos() {
  volumen_pasos = std::max(0, volumen_pasos - AUDIO_INCREMENTO_VOLUMEN);
  sonido_pasos.SetVolume(volumen_pasos);
}

void Audio::subir_volumen_pasos() {
  volumen_pasos =
      std::min(MIX_MAX_VOLUME, volumen_pasos + AUDIO_INCREMENTO_VOLUMEN);
  sonido_pasos.SetVolume(volumen_pasos);
}

void Audio::reproducir_paso() {
  mixer.PlayChannel(AUDIO_CANAL_LIBRE, sonido_pasos, AUDIO_SIN_REPETIR);
}

int Audio::obtener_volumen_musica() const { return volumen_musica; }

void Audio::poner_musica_granja() {
  musica_actual = AUDIO_MUSICA_GRANJA;
  mixer.PlayMusic(musica_granja, AUDIO_REPETIR_SIEMPRE);
}

void Audio::poner_musica_caverna() {
  musica_actual = AUDIO_MUSICA_CAVERNA;
  mixer.PlayMusic(musica_caverna, AUDIO_REPETIR_SIEMPRE);
}

void Audio::poner_musica_pueblo() {
  musica_actual = AUDIO_MUSICA_PUEBLO;
  mixer.PlayMusic(musica_pueblo, AUDIO_REPETIR_SIEMPRE);
}
