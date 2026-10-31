#ifndef TASA_CONSTANTE_H
#define TASA_CONSTANTE_H

#include <chrono>

//loop da una vuelta cada periodo como un reloj (drop & rest)
class TasaConstante {
private:
    using Reloj = std::chrono::steady_clock;

    std::chrono::milliseconds periodo;
    Reloj::time_point t1; //donde empieza la vuelta actual
public:
    explicit TasaConstante(std::chrono::milliseconds periodo);
    long esperar(); //duerme lo que flta para completar la vuelta
};

#endif 
