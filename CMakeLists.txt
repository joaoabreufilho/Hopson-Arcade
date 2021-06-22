cmake_minimum_required(VERSION 3.10)

include(cmake/CompileFeatures.cmake)

project(hopson-arcade VERSION 2.1
                  DESCRIPTION "Hopson Arcade: Selection of simple arcade-y games"
                  LANGUAGES CXX)

# Main program executable
add_subdirectory(src)