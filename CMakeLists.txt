cmake_minimum_required(VERSION 3.10)
project(CPP_QT_miniprojet)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


if(EXISTS ${CMAKE_SOURCE_DIR}/.env)
    configure_file(${CMAKE_SOURCE_DIR}/.env ${CMAKE_BINARY_DIR}/.env COPYONLY)
endif ()

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        Sql
        REQUIRED)

file (GLOB_RECURSE sourceCode src/*.cpp src/*.h main.cpp)

add_executable(CPP_QT_miniprojet ${sourceCode} res.qrc src/settings.h src/keyPressedDialogRecorder.cpp src/keyPressedDialogRecorder.h src/SkinCardWidget.cpp src/SkinCardWidget.h src/AudioSettingsLayout.cpp src/AudioSettingsLayout.h)

target_link_libraries(CPP_QT_miniprojet Qt6::Widgets Qt6::Multimedia Qt6::Sql)