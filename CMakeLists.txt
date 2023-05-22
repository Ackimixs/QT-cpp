cmake_minimum_required(VERSION 3.10)
project(tp4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

find_package(Qt6Widgets CONFIG REQUIRED)

file (GLOB_RECURSE CIR2_sceneview_src src/*.cpp src/*.h)

add_executable(tp4 ${CIR2_sceneview_src})

target_link_libraries(tp4 Qt6::Widgets)
