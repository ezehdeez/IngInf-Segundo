/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P1
 * 
 * @file simulator.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-02-09
 * @brief Simulator class inicialization
 */

#include "../include/simulator.h"

#include <fstream>
#include <sstream>

/**
 * @brief Construct a new Simulator:: Simulator object. The object is created from
 *        a given file name. It follows an specific structure
 * 
 *  Línea 1: Tamaño de la cinta
 *  Línea 2: Posición inicial y orientación de la hormiga
 *  Línea 3..n: Posiciones de las celdas negras (valor binario 1).
 * 
 * @param file_name 
 */
Simulator::Simulator(const std::string& file_name) : ant_{}, tape_{} {
  std::ifstream input_file{file_name};
  std::string line;
  size_t x_size, y_size;
  int ant_orientation, ant_x, ant_y;
  getline(input_file, line);
  std::istringstream iss(line);
  iss >> x_size >> y_size;
  getline(input_file, line);
  iss = std::istringstream(line);
  iss >> ant_x >> ant_y >> ant_orientation;
  Tape tape{x_size, y_size};
  Ant ant{ant_orientation, ant_x, ant_y};
  while(getline(input_file, line)) {
    iss = std::istringstream(line);
    size_t row, column;
    iss >> row >> column;
    tape.DrawCell(row, column);
  }
  tape_ = tape;
  ant_ = ant;
}

/**
 * @brief Main loop for running the simulation, it is not an infinite nonstop simulation,
 *        it waits for a request in every step, so the user can controll what to
 *        do in each step.
 * 
 */
void Simulator::RunSimulation() {
  int step_count = 0;
  while(true) {
    std::system("clear");
    tape_.PrintUntilAnt(&ant_);
    std::cout << ant_;
    tape_.PrintPostAnt(&ant_);
    std::cout << "STEP COUNT: " << step_count << "\n" << std::endl;
    std::cout << "(N)ext step / (S)ave current state" << std::endl;
    char answer = 'N';
    std::cin >> answer;
    if(answer == 'N') {
      step_count++;
      ant_.Step(tape_);
      continue;
    } else if(answer == 'S') {
      ExportFile();
      std::cout << "[DONE]: File exported" << std::endl;
      break;
    } else {
      std::cout << "[ERROR]: Wrong option, try again" << std::endl;
    }
  }
}

/**
 * @brief Private method to export the tape and ant to a file with the same 
 *        structure as the input_file.
 * 
 */
void Simulator::ExportFile() {
  std::ofstream output_file{"output.txt"};
  output_file << tape_.GetXSize() << " " << tape_.GetYSize() << "\n";
  output_file << ant_.GetOrientation() << " " << ant_.GetX() << " " << ant_.GetY() << "\n";
  for(size_t i = 0; i < tape_.GetXSize(); i++) {
    for(size_t j = 0; j < tape_.GetYSize(); j++) {
      if(tape_.GetCell(i, j)) {
        output_file << i << " " << j << "\n";
      }
    }
  }
}