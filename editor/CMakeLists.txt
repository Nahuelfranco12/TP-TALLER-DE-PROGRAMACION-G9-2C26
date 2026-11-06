cmake_minimum_required(VERSION 3.19)
project(editor LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
set(CMAKE_AUTORCC ON)

qt_standard_project_setup()

qt_add_executable(editor
    WIN32 MACOSX_BUNDLE
    main.cpp
    ventanaeditor.cpp
    ventanaeditor.h
    ventanaeditor.ui
    Images.qrc

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
