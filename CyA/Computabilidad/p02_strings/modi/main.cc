/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P02 - Cadenas y Lenguajes
 * 
 * @file main.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-09-17
 * @brief This files contains the main program, this program takes an input file 
 *        that contains a chain and an alphabet in each line and it will write
 *        in a given output file an operation for each of the lines. The 
 *        operation is selected by the opcode. The details are ine the 
 *        HelpMessage function in functions.cc.
 */

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include "alphabet.h"
#include "chain.h"
#include "language.h"
#include "functions.h"

int main(int argc, char* argv[]) {
  std::ifstream input_file{argv[1]};
  std::ofstream output_file{argv[2]};
  HelpMessage(argv);
  CheckCorrectParameters(argc, 4);
  FileCheck(input_file, output_file);
  OpSelector(input_file, output_file, std::stoi(argv[3]));
  return 0;
}