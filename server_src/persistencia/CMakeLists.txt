target_sources(taller_persistencia
    PRIVATE
    archivo_partida.cpp
    ids_partida.cpp
    ids_partida.h
    lectura_toml.cpp
    lectura_toml.h

    PUBLIC
    archivo_partida.h
    constantes_persistencia.h
    partida_guardada.h
    )

add_library(taller_adaptador_partida STATIC
    adaptador_partida.cpp
    adaptador_partida.h
    )
target_link_libraries(taller_adaptador_partida PUBLIC
    taller_persistencia
    taller_game
    )
