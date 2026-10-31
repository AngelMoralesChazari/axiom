cmake_minimum_required(VERSION 3.16)
project(Axiom LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Axiom
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    resources/resources.qrc
)

target_link_libraries(Axiom PRIVATE Qt6::Widgets)

# Permite ejecutar tanto ./build/Axiom como ./build/MiIDE
add_custom_command(TARGET Axiom POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink Axiom $<TARGET_FILE_DIR:Axiom>/MiIDE
)

