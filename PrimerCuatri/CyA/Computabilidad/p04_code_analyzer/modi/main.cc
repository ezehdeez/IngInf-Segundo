/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P04 - Expresiones regulares en C++
 * 
 * @file main.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-05
 * @brief Main program which takes as parameter two files, and analyzes the first
 *        one (it should be a C++ code) to extracts the most important information
 *        about the code such as if it has a main function or a description. It
 *        also lists every variable, statement or comment in the code.
 * 
 *        Usage: /p04_code_analyzer example.cc out.txt
 */

/**
 *  Modificación: Identificar declaración de clases => CLASSES: A: Lineas a - b
 */


#include <fstream>
#include <string>
#include <regex>
#include "code_struc.h"
#include "functions.h"

int main(int argc, char* argv[]) {
  std::ifstream input_file(argv[1]);
  std::ofstream output_file(argv[2]);
  HelpMessage(argv);
  CheckCorrectParameters(argc, 3);
  FileCheck(input_file, output_file);
  std::string input_file_name(argv[1]);
  CodeStructure code_structure(input_file_name);
  code_structure.FillCodeStructure(input_file);
  output_file << code_structure;
  return 0;
}