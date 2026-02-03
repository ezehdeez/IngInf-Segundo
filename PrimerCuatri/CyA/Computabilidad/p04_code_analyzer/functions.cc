/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P04 - Expresiones regulares en C++
 * 
 * @file functions.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-05
 * @brief This file contains utility functions used by the main program, such as 
 *        format checkers for files or parameters. Besides we have the OpSelector
 *        which dceides the operation that is going to be written in the output
 *        file.
 */

#include <iostream>
#include <fstream>
#include <regex>

#include "functions.h"

/**
 * @brief This functions checks if the given number of arguments is ok.
 * 
 * @param argc 
 * @param kCorrectNumber 
 */
void CheckCorrectParameters(int argc, const int kCorrectNumber) {
  if(argc != kCorrectNumber) {
    std::cerr << "Modo de empleo: ./p04_code_structure <input_file> <output_file>\n"
    << "Pruebe './p04_code_analyzer --help' para más información" << std::endl;
    exit(1);
  }
}

/**
 * @brief This functions checks if the given files are available for 
 *        reading/writing.
 * 
 * @param input_file 
 * @param output_file 
 */
void FileCheck(std::ifstream& input_file, std::ofstream& output_file) {
  if(!input_file) {
    std::cerr << "El archivo de entrada no se ha podido leer correctamente." << std::endl;
    exit(1);
  } else if(!output_file) {
    std::cerr << "El archivo de salida no se ha podido leer correctamente." << std::endl;
    exit(1);
  }
}

/**
 * @brief If the argument in the program is "--help" this function is going to
 *        print the help message.
 * 
 * @param argv 
 */
void HelpMessage(char* argv[]) {
  if(std::string(argv[1]) == "--help") {
    std::cout << "Este programa aceptará como parámetros un primer archivo de entrada" <<
    "de código en C++ y un segundo archivo de salida .txt.\n" <<
    "Modo de empleo: ./p04_code_analyzer <input_file> <output_file>" << std::endl;
    exit(1);
  }
}