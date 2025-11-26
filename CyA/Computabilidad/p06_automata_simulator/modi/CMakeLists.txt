# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Informática Básica
#
# @author F. de Sande
# @date Nov 9, 2022
# @brief CMakeLists.txt simple example. You can use this as a template for your projects
#        This does not generate documentation
#        It doesn't build any library
# CMakeLists.txt defines the whole build
# CMake reads CMakeLists.txt sequentially
#
# Build process:
#   1. cd <project_folder>
#   2. mkdir build
#   3. cd build
#   4. cmake ..
#   5. make

cmake_minimum_required(VERSION 3.1)  # Mandatory

# set the project name 
project(p06_automata_simulator                # Mandatory
    VERSION 1.0
    DESCRIPTION "A simple CMake project for the Fibonacci Sum application"
    LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17) 						# Use c++17
set(CMAKE_CXX_STANDARD_REQUIRED True)

# tell cmake to output binaries here:
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

# Debug and release flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic -Weffc++")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# tell cmake where to look for *.h files
include_directories(${PROJECT_SOURCE_DIR}/src)

# Adds an executable target called "p06_automata_simulator" to be built from the source files listed in the command invocation.
add_executable(p06_automata_simulator
    src/main.cc
    src/functions.cc
    src/automaton.cc
    src/alphabet.cc
    src/automaton_loader.cc
    lib/functions.h
    lib/automaton.h
    lib/alphabet.h
    lib/state.h
    lib/automaton_loader.h
)

# Add expected compiler features to a target.
target_compile_features(p06_automata_simulator PRIVATE cxx_std_17)

# Add compile options to a target.
target_compile_options(p06_automata_simulator PRIVATE -Wall -Wextra -Wpedantic -Weffc++)
