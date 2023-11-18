cmake_minimum_required(VERSION 3.10)
project(Pong)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add raylib
add_subdirectory(dependencies/raylib)
# pong gui
add_executable(Pong-gui main.cpp)
target_link_libraries(Pong-gui PUBLIC raylib)
target_include_directories(Pong-gui PUBLIC "${PROJECT_SOURCE_DIR}/dependencies/raylib")

