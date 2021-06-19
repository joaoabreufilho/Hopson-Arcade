cmake_minimum_required(VERSION 3.10)

#include(cmake/CompileFeatures.cmake)

project(hopson-arcade VERSION 2.0
                  DESCRIPTION "Hopson Arcade: Selection of simple arcade-y games"
                  LANGUAGES CXX)

## If you want to link SFML statically
#set(SFML_STATIC_LIBRARIES TRUE)   

# Main program executable
add_subdirectory(src)