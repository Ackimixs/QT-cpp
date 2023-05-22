cmake_minimum_required(VERSION 3.25)
project(tp2)

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

add_executable(tp2 main.cpp SQLClientWindow.cpp SQLClientWindow.h ButtonPanel.cpp ButtonPanel.h LabeledTextField.cpp LabeledTextField.h ConfigurationDialog.cpp ConfigurationDialog.h)
target_link_libraries(tp2
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

