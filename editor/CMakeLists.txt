cmake_minimum_required(VERSION 3.19)
project(editor LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Core Widgets)
set(CMAKE_AUTORCC ON)

qt_standard_project_setup()

include(FetchContent)
FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)

qt_add_executable(editor
    main.cpp
    ventanaeditor.ui
    Images.qrc

    headers/controlador_inicio_editor.h
    headers/controlador_pagina_editor.h
    headers/datos_editor.h
    headers/navegador.h
    headers/ventanaeditor.h
    headers/controlador_mapas.h
    headers/vista_responsive.h
    headers/constantes_qt.h
    headers/sprites.h
    headers/vista_zona.h
    headers/catalogo_elementos.h

    mapa/validacion_mapas.h
    mapa/mapa_editor.h
    mapa/elementos_mapa.h
    mapa/archivo_mapa.h
    mapa/constantes_mapa.h

    implementaciones/catalogo_elementos.cpp
    implementaciones/sprites.cpp
    implementaciones/vista_zona.cpp
    implementaciones/vista_responsive.cpp
    implementaciones/controlador_mapas.cpp
    implementaciones/controlador_inicio_editor.cpp
    implementaciones/navegador.cpp
    implementaciones/ventanaeditor.cpp

    mapa/mapa_editor.cpp
    mapa/validacion_mapas.cpp
    mapa/archivo_mapa.cpp
)

target_include_directories(editor PRIVATE headers mapa)

set_target_properties(editor PROPERTIES
    AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(editor PRIVATE
    -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror
)

target_link_libraries(editor
    PRIVATE
        Qt::Core
        Qt::Widgets
        tomlplusplus::tomlplusplus
)

install(TARGETS editor RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
