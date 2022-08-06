cmake_minimum_required(VERSION 3.16.0)

project(lxqt-sway VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lxqt-settings)
add_subdirectory(lxqt-config-sway)
