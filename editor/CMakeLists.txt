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

set(FLAGS_EDITOR
    -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror
)

add_library(editor_mapa STATIC
    mapa/archivo_mapa.h
    mapa/constantes_mapa.h
    mapa/elementos_mapa.h
    mapa/ids_mapa.h
    mapa/lectura_toml.h
    mapa/mapa_editor.h
    mapa/validacion_mapas.h

    mapa/archivo_mapa.cpp
    mapa/ids_mapa.cpp
    mapa/lectura_toml.cpp
    mapa/mapa_editor.cpp
    mapa/validacion_mapas.cpp
)

target_include_directories(editor_mapa PUBLIC mapa)

set_target_properties(editor_mapa PROPERTIES
    AUTOMOC OFF
    AUTOUIC OFF
    AUTORCC OFF
)

target_compile_options(editor_mapa PRIVATE ${FLAGS_EDITOR})

target_link_libraries(editor_mapa PRIVATE tomlplusplus::tomlplusplus)

qt_add_executable(editor
    main.cpp
    ventanaeditor.ui
    Images.qrc

    headers/catalogo_elementos.h
    headers/constantes_qt.h
    headers/controlador_inicio_editor.h
    headers/controlador_mapas.h
    headers/controlador_pagina_editor.h
    headers/datos_editor.h
    headers/navegador.h
    headers/sprites.h
    headers/ventanaeditor.h
    headers/vista_responsive.h
    headers/vista_zona.h

    implementaciones/catalogo_elementos.cpp
    implementaciones/controlador_inicio_editor.cpp
    implementaciones/controlador_mapas.cpp
    implementaciones/navegador.cpp
    implementaciones/sprites.cpp
    implementaciones/ventanaeditor.cpp
    implementaciones/vista_responsive.cpp
    implementaciones/vista_zona.cpp
)

target_include_directories(editor PRIVATE headers)

set_target_properties(editor PROPERTIES
    AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(editor PRIVATE ${FLAGS_EDITOR})

target_link_libraries(editor
    PRIVATE
        editor_mapa
        Qt::Core
        Qt::Widgets
)

install(TARGETS editor RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
