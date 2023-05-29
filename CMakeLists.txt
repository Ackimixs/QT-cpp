cmake_minimum_required(VERSION 3.10)
project(CPP_QT_TPminiprojet)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

configure_file(${CMAKE_SOURCE_DIR}/.env ${CMAKE_BINARY_DIR}/.env COPYONLY)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        Sql
        REQUIRED)

file (GLOB_RECURSE sourceCode src/*.cpp src/*.h main.cpp)

add_executable(CPP_QT_TPminiprojet ${sourceCode} res.qrc)

target_link_libraries(CPP_QT_TPminiprojet Qt6::Widgets Qt6::Multimedia Qt6::Sql)