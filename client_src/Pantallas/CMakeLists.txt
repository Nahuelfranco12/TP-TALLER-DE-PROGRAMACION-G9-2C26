cmake_minimum_required(VERSION 3.19)
project(Pantallas LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR})

qt_add_executable(Pantallas
    WIN32 MACOSX_BUNDLE
    main.cpp
    implementaciones/pantalla.cpp
    headers/pantalla.h
    pantalla.ui
    Images.qrc
    headers/partidas_estaticas.h
    implementaciones/partidas_estaticas.cpp
    headers/tarjeta_item.h
    implementaciones/tarjeta_item.cpp
    headers/navegador_paginas.h
    implementaciones/navegador_paginas.cpp
    implementaciones/vista_responsive.cpp
    headers/lista_seleccionable.h
    implementaciones/lista_seleccionable.cpp
    headers/controlador_pagina.h
    headers/controlador_menu_principal.h
    implementaciones/controlador_menu_principal.cpp
    headers/controlador_nueva_partida.h
    implementaciones/controlador_nueva_partida.cpp
    headers/controlador_unirse_partida.h
    implementaciones/controlador_unirse_partida.cpp
    headers/controlador_retomar_partida.h
    implementaciones/controlador_retomar_partida.cpp
    headers/controlador_customizar_personaje.h
    implementaciones/controlador_customizar_personaje.cpp
    headers/constantes.h
    headers/dtos_pantallas.h
    headers/dibujar_personaje.h
    implementaciones/dibujar_personaje.cpp
    headers/servicio_lobby.h
    headers/vista_responsive.h
)

target_link_libraries(Pantallas
    PRIVATE
        Qt::Core
        Qt::Widgets
)

target_include_directories(Pantallas PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
    ${CMAKE_CURRENT_SOURCE_DIR}/implementaciones
)
