/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P08 - Gramáticas en Forma Normal de Chomsky
 * 
 * @file functions.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-29
 * @brief This file contains utility functions used by the main program, such as 
 *        format checkers for files or parameters.
 */

#include <iostream>
#include <fstream>

#include "../include/functions.h"

/**
 * @brief This functions checks if the given number of arguments is ok.
 * 
 * @param argc 
 * @param kCorrectNumber 
 */
void CheckCorrectParameters(int argc, const int kCorrectNumber) {
  if(argc != kCorrectNumber) {
    std::cout << "Modo de empleo: ./p08_Grammar2CNF input.gra output.gra\n"
    << "Pruebe './p08_Grammar2CNF --help' para más información" << std::endl;
    exit(1);
  }
}

/**
 * @brief This functions checks if the given files are available for 
 *        reading/writing.
 * 
 * @param input_file 
 * @param input_fa
 */
void FileCheck(const std::string& input_file_name, const std::string& output_file_name) {
  std::ifstream input_file{input_file_name};
  std::ifstream output_file{output_file_name};
  if(!input_file) {
    std::cout << "El archivo de entrada no se ha podido leer correctamente." << std::endl;
    // exit(1);
  } else if(!output_file) {
    std::cout << "El archivo del salida no se ha podido leer correctamente." << std::endl;
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
    std::cout << "\nEste programa lee desde un fichero las especificaciones de un"
    "autómata finito (FA) y, a continuación,\nsimule el comportamiento del autómata"
    "para una serie de cadenas que se suministren como entrada.\n\n" <<
    "Modo de empleo: ./p06_automata_simulator <\".fa\" file> <input_file>\n\n" <<
    "Donde los dos parámetros pasados en la línea de comandos corresponden en este orden con:\n" 
    "\t· Un fichero de texto en el que figura la especificación de un autómata finito.\n" 
    "\t· Un fichero de texto con extensióon .txt en el que figura una serie de cadenas\n\t  (una"
    " cadena por línea) sobre el alfabeto del autómata especificado en el primero\n\t  de los"
    " ficheros.\n" << std::endl;
    exit(1);
  }
}