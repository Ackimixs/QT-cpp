cmake_minimum_required(VERSION 3.10)
project(tp4)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

file (GLOB_RECURSE CIR2_sceneview_src src/*.cpp src/*.h)

add_executable(tp4 ${CIR2_sceneview_src} res.qrc)

target_link_libraries(tp4 Qt6::Widgets Qt6::Multimedia)
