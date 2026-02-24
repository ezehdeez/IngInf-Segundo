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
#include "../include/derivated_ants.h"

#include <fstream>
#include <memory>
#include <sstream>

/**
 * @brief Construct a new Simulator:: Simulator object. The object is created from
 *        a given file name. It follows an specific structure
 * 
 *    Línea 1: Tamaño de la cinta y número de colores de las celdas
 *    Línea 2: Tipo, posición inicial y orientación de cada hormiga (separadas por ‘;’)
 *    Línea 3..: Posición y color de las celdas no blancas
 * 
 * @param file_name 
 */
Simulator::Simulator(const std::string& file_name) : number_of_colors_{}, ants_{}, tape_{} {
  std::cout << "in sim construcion" << std::endl;
  std::ifstream input_file{file_name};
  size_t size_x, size_y;
  input_file >> size_x >> size_y >> number_of_colors_;
  tape_ = {size_x, size_y};
  input_file.ignore();
  std::string all_ants_line, ant_segment;
  getline(input_file, all_ants_line);
  std::stringstream ss_ants(all_ants_line);
  while(getline(ss_ants, ant_segment, ';')) {
    std::stringstream ant_ss(ant_segment);
    size_t ant_x_pos, ant_y_pos;
    std::string ant_type;
    char orientation;
    ant_ss >> ant_type >> ant_x_pos >> ant_y_pos >> orientation;
    if(ant_type == "DDII") {
      ants_.push_back(std::make_unique<Ant_DDII>(orientation, ant_x_pos, ant_y_pos));
    } else if(ant_type == "IDID") {
      ants_.push_back(std::make_unique<Ant_IDID>(orientation, ant_x_pos, ant_y_pos));
    } 
  }
  std::string line;
  std::cout << "ants built" << std::endl;
  while(getline(input_file, line)) {
    std::cout << line << std::endl;
    std::stringstream cell_ss(line);
    size_t x, y;
    int color;
    cell_ss >> x >> y >> color;
    std::cout << "predraw " << x << " " << y << std::endl;
    tape_.DrawCell(x, y, static_cast<Color>(color));
  }
  std::cout << "Simulator built" << std::endl;
}

void Simulator::PrintTape() {
  for(size_t i = 0; i < tape_.GetXSize(); i++) {
    for(size_t j = 0; j < tape_.GetYSize(); j++) {
      bool ant_found = false;
      for(size_t k = 0; k < ants_.size(); k++) {
        if(i == static_cast<size_t>(ants_[k]->GetX()) && j == static_cast<size_t>(ants_[k]->GetY())) {
          char arrow = ' ';
          switch(ants_[k]->GetOrientation()) {
            case 0: arrow = '<'; break;
            case 1: arrow = '>'; break;
            case 2: arrow = '^'; break;
            case 3: arrow = 'v'; break;
          }
          std::cout << tape_.ColorToCode(tape_.GetCell(i, j)) << arrow << RESET;
          ant_found = true;
          break;
        }
      }
      if(!ant_found) {
        tape_.PrintCell(i, j);
      }
    }
    std::cout << std::endl;
  }
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
    PrintTape();
    std::cout << "STEP COUNT: " << step_count << "\n" << std::endl;
    std::cout << "(N)ext step / (S)ave current state" << std::endl;
    char answer = 'N';
    std::cin >> answer;
    if(answer == 'N') {
      step_count++;
      for(auto& ant : ants_) {
        ant->Step(tape_);
      }
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
  output_file << tape_.GetXSize() << " " << tape_.GetYSize() << " " << number_of_colors_ << "\n";
  for(size_t i = 0; i < ants_.size(); i++) {
    char arrow = ' ';
    switch(ants_[i]->GetOrientation()) {
      case 0: arrow = '<'; break;
      case 1: arrow = '>'; break;
      case 2: arrow = '^'; break;
      case 3: arrow = 'v'; break;
    }
    output_file << ants_[i]->GetType() << " " << ants_[i]->GetX() << " " << ants_[i]->GetY() << " " << arrow;
    if(i != (ants_.size() - 1)) {
      output_file << " ; ";
    }
  }
  output_file << "\n";
  for(size_t i = 0; i < tape_.GetXSize(); i++) {
    for(size_t j = 0; j < tape_.GetYSize(); j++) {
      if(tape_.GetCell(i, j) != Color::WHITE_CELL) {
        output_file << i << " " << j << " " << static_cast<int>(tape_.GetCell(i, j)) << "\n";
      }
    }
  }
}