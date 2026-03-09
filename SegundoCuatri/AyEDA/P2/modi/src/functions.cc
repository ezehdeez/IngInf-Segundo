/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P1
 * 
 * @file functions.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-02-09
 * @brief Several useful functions
 */

#include "../include/ant.h"

#include <fstream>

/**
 * @brief Checker for the amount of arguments
 * 
 * @param argc 
 * @param argv 
 * @param kCorrectNumber 
 */
void CheckCorrectParameters(int argc, char* argv[], const int kCorrectNumber) {
  if(argc != kCorrectNumber) {
    std::cerr << "[ERROR] " << argv[0] << ": Wrong amount of arguments" << std::endl;
    std::cerr << "\tRight usage: ./langton <input_file>" << std::endl;
    exit(1);
  }
}

/**
 * @brief Used to check file disponibility
 * 
 * @param input_file_name 
 */
void FileCheck(const std::string& input_file_name) {
  std::ifstream input_file(input_file_name);
  if(!input_file) {
    std::cerr << "[ERROR]: Can't read input file" << std::endl;
    exit(1);
  }
}