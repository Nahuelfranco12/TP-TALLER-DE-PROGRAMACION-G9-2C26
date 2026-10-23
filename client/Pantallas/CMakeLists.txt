cmake_minimum_required(VERSION 3.19)
project(Pantallas LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()
set(CMAKE_AUTORCC ON)

qt_add_executable(Pantallas
    WIN32 MACOSX_BUNDLE
    main.cpp
    pantalla.cpp
    pantalla.h
    pantalla.ui
    Images.qrc
    partidas_estaticas.h partidas_estaticas.cpp
)

target_link_libraries(Pantallas
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS Pantallas
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Pantallas
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
