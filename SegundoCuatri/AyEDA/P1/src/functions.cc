#include "../include/ant.h"

#include <fstream>

void CheckCorrectParameters(int argc, char* argv[], const int kCorrectNumber) {
  if(argc != kCorrectNumber) {
    std::cerr << "[ERROR] " << argv[0] << ": Wrong amount of arguments" << std::endl;
    std::cerr << "\tRight usage: ./langton <input_file>" << std::endl;
    std::exit;
  }
}

void FileCheck(const std::string& input_file_name) {
  std::ifstream input_file(input_file_name);
  if(!input_file) {
    std::cerr << "[ERROR]: Can't read input file" << std::endl;
    std::exit;
  }
}