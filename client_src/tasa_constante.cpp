#include "tasa_constante.h"

#include <thread>

TasaConstante::TasaConstante(std::chrono::milliseconds periodo)
    : periodo(periodo), t1(Reloj::now()) {}

long TasaConstante::esperar() {
  long vueltas = 1;

  Reloj::time_point t2 = Reloj::now();
  Reloj::duration descanso =
      periodo - (t2 - t1); // lo que falta para la próxima marca

  if (descanso < Reloj::duration::zero()) {  // me atrasé
    Reloj::duration atraso = -descanso;      // cuanto me pasé
    descanso = periodo - (atraso % periodo); // dormir hasta la próxima marca
    Reloj::duration perdido = atraso + descanso; // tiempo de vueltas perdidas
    t1 += perdido;                               // correr la base
    vueltas +=
        static_cast<long>(perdido / periodo); // contar las vueltas salteadas
  }

  std::this_thread::sleep_for(descanso);
  t1 += periodo;
  return vueltas;
}
