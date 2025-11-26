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

cmake_minimum_required(VERSION 3.5)  # Mandatory

# set the project name 
project(backup                # Mandatory
    VERSION 1.0
    DESCRIPTION "A simple CMake project for the Fibonacci Sum application"
    LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)            # ¡IMPORTANTE! Usar c++23
set(CMAKE_CXX_STANDARD_REQUIRED True)

# tell cmake to output binaries here:
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

# Debug and release flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic -Weffc++")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# tell cmake where to look for *.h files
include_directories(${PROJECT_SOURCE_DIR}/include) 


# **********************************************
# 1. Ejecutable 'backup' (El Cliente)
#    Fuentes: backup.cc, copy.cc, functions.cc
# **********************************************
add_executable(backup  
    src/backup.cc
    src/copy.cc
    src/functions.cc
)

# Ya no es necesario target_compile_features, se usa el estándar global
target_compile_options(backup PRIVATE -Wall -Wextra -Wpedantic -Weffc++)


# **********************************************
# 2. Ejecutable 'backup-server' (El Servidor)
#    Fuentes: backup-server.cc, functions.cc
# **********************************************
add_executable(backup-server  
    src/backup-server.cc
    src/functions.cc
)

# Ya no es necesario target_compile_features, se usa el estándar global
target_compile_options(backup-server PRIVATE -Wall -Wextra -Wpedantic -Weffc++)