cmake_minimum_required(VERSION 3.25)
project(tp1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/lib64/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(tp1 main.cpp Window.cpp Window.h WindowTest.cpp WindowTest.cpp WindowTest.h)
target_link_libraries(tp1
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

