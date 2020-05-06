cmake_minimum_required(VERSION 3.16)
project(Diamond_Square)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(Diamond_Square main.cpp)
target_link_libraries(Diamond_Square sfml-graphics)
