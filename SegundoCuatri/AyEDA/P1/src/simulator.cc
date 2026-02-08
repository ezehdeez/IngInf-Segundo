#include "../include/simulator.h"

#include <fstream>
#include <sstream>

Simulator::Simulator(const std::string& file_name) {
  std::ifstream input_file{file_name};
  std::string line;
  std::stringstream stringstream;
  size_t x_size, y_size;
  int ant_orientation, ant_x, ant_y;
  getline(input_file, line);
  stringstream >> x_size >> y_size;
  getline(input_file, line);
  stringstream >> ant_orientation >> ant_x >> ant_y;
  Tape tape{x_size, y_size};
  Ant ant{ant_orientation, ant_x, ant_y};
  while(getline(input_file, line)) {
    
  }
}