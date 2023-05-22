cmake_minimum_required(VERSION 3.25)
project(tp3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/lib64/cmake")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(tp3 main.cpp MainWindow.cpp MainWindow.h ex2.cpp ex2.h)
target_link_libraries(tp3
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

