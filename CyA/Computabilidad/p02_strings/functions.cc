/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P02 - Cadenas y Lenguajes
 * 
 * @file functions.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-09-17
 * @brief This file contains utility functions used by the main program, such as 
 *        format checkers for files or parameters. Besides we have the OpSelector
 *        which dceides the operation that is going to be written in the output
 *        file.
 */

#include <iostream>
#include <fstream>

#include "functions.h"
#include "alphabet.h"
#include "chain.h"
#include "language.h"

/**
 * @brief This functions checks if the given number of arguments is ok.
 * 
 * @param argc 
 * @param kCorrectNumber 
 */
void CheckCorrectParameters(int argc, const int kCorrectNumber) {
  if(argc != kCorrectNumber) {
    std::cerr << "Modo de empleo: ./p02_strings <input_file> <output_file> opcode\n"
    << "Pruebe './p02_strings --help' para más información" << std::endl;
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
    ".txt, un segundo archivo de salida .txt y un código de operación (opcode).\n" <<
    "Modo de empleo: ./p02_strings <input_file> <output_file> opcode\n\n" <<
    "Códigos de operación:\n" <<
    "\t[1] Alfabeto -> Escribe en el fichero salida el alfabeto de cada una de las cadenas de entrada.\n" <<
    "\t[2] Longitud -> Escribe en el fichero de salida la longitud de cada una de las cadenas de entrada.\n"
    "\t[3] Inversa -> Escribe en el fichero de salida la inversa de cada una de las cadenas de entrada.\n"
    "\t[4] Prefijos -> Escribe en el fichero de salida todos los prefijos de sus cadenas correspondientes.\n"
    "\t[5] Sufijos -> Escribe en el fichero de salida todos los sufijos de sus cadenas correspondientes.\n" << std::endl;
    exit(1);
  }
}

/**
 * @brief This is the main function which will read the input_file and depending
 *        of the opcode is going to do the corresponding option.
 * 
 * @param input_file 
 * @param output_file 
 * @param opcode 
 */
void OpSelector(std::ifstream& input_file, std::ofstream& output_file, int opcode) {
  std::string chain_string, alphabet_string;
  while(input_file >> chain_string >> alphabet_string) {
    Alphabet target_alphabet(alphabet_string);
    Chain target_chain(chain_string, target_alphabet);
    switch(opcode) {
      case 1:
        output_file << target_alphabet << std::endl;
        break;
      case 2:
        output_file << target_chain.getSize() << std::endl;
        break;
      case 3:
        output_file << target_chain.Inverse() << std::endl;
        break;
      case 4:
        output_file << target_chain.Prefixes() << std::endl;
        break;
      case 5:
        output_file << target_chain.Suffixes() << std::endl;
        break;
      default:
        std::cerr << "Given opcode is not correct. Try again or check them using ./p02_strings --help" << std::endl;
        exit(1);
    }
  }
}