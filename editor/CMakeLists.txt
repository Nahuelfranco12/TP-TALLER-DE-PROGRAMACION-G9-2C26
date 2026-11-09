cmake_minimum_required(VERSION 3.19)
project(editor LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
set(CMAKE_AUTORCC ON)

qt_standard_project_setup()

qt_add_executable(editor
    WIN32 MACOSX_BUNDLE
    main.cpp
    ventanaeditor.ui
    Images.qrc

    headers/controlador_inicio_editor.h
    headers/controlador_pagina_editor.h
    headers/datos_editor.h
    headers/navegador.h
    headers/ventanaeditor.h
    headers/controlador_mapas.h
    headers/editor_dtos.h
    headers/vista_responsive.h
    headers/constantes.h
    headers/mapa_editor.h
    headers/control_dimensiones.h
    headers/sprites.h
    headers/vista_zona.h

    implementaciones/sprites.cpp
    implementaciones/vista_zona.cpp
    implementaciones/control_dimensiones.cpp
    implementaciones/mapa_editor.cpp
    implementaciones/vista_responsive.cpp
    implementaciones/editor_dtos.cpp
    implementaciones/controlador_mapas.cpp
    implementaciones/controlador_inicio_editor.cpp
    implementaciones/navegador.cpp
    implementaciones/ventanaeditor.cpp
)

target_include_directories(editor PRIVATE headers)

set_target_properties(editor PROPERTIES
    AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(editor
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS editor
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET editor
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
