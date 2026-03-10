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

#include <algorithm>
#include <fstream>
#include <memory>
#include <optional>
#include <sstream>

constexpr int DEFAULT_LIFE_TIME = 100;

/**
 * @brief Construct a new Simulator:: Simulator object. The object is created from
 *        a given file name. It follows an specific structure
 * 
 *    Línea 1: 7 10 4
 *    Línea 2: H-DDII 3 3 > ; C-IDID 5 7 v
 *    Línea 3: 3 4 1
 *    Línea 4: 3 5 2
 *    Línea 5: 5 5 3
 * 
 * @param file_name 
 */
Simulator::Simulator(const std::string& file_name, int tape_type) : number_of_colors_{}, ants_{}, tape_{} {
  std::cout << "in sim construcion" << std::endl;
  std::ifstream input_file{file_name};
  size_t size_x, size_y;
  input_file >> size_x >> size_y >> number_of_colors_;
  switch (tape_type) {
    case 1:
      tape_ = std::make_unique<TapePeriodic>(size_x, size_y);
      break;
    case 2:
      tape_ = std::make_unique<TapeReflective>(size_x, size_y);
      break;
    case 3:
      tape_ = std::make_unique<TapeSliding>(size_x, size_y);
      break;
    default:
      tape_ = std::make_unique<TapePeriodic>(size_x, size_y);
      break;
    }
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
    if(ant_type == "H-DDII") {
      ants_.push_back(std::make_unique<Ant_H_DDII>(orientation, DEFAULT_LIFE_TIME, ant_x_pos, ant_y_pos));
    } else if(ant_type == "C-IDID") {
      ants_.push_back(std::make_unique<Ant_C_IDID>(orientation, DEFAULT_LIFE_TIME, ant_x_pos, ant_y_pos));
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
    tape_->DrawCell(x, y, static_cast<Color>(color));
  }
  std::cout << "Simulator built" << std::endl;
}

/**
 * @brief Prints the current state of the tape and the ants to the console.
 * It calculates dynamic boundaries (a camera effect) to ensure all ants 
 * are visible, even if they step outside the original memory grid.
 */
void Simulator::PrintTape() {
  int min_x = tape_->GetMinX();
  int max_x = tape_->GetMaxX();
  int min_y = tape_->GetMinY();
  int max_y = tape_->GetMaxY();
  for (const auto& ant : ants_) {
    if (ant->GetX() < min_x) min_x = ant->GetX();
    if (ant->GetX() > max_x) max_x = ant->GetX();
    if (ant->GetY() < min_y) min_y = ant->GetY();
    if (ant->GetY() > max_y) max_y = ant->GetY();
  }
  for(int i = min_x; i <= max_x; i++) {
    for(int j = min_y; j <= max_y; j++) {
      int ants_in_cell = 0;
      char arrow = ' ';
      for(size_t k = 0; k < ants_.size(); k++) {
        if(i == ants_[k]->GetX() && j == ants_[k]->GetY()) {
          ants_in_cell++;
          if(ants_in_cell == 1) {
            switch(ants_[k]->GetOrientation()) {
              case 0: arrow = '<'; break;
              case 1: arrow = '>'; break;
              case 2: arrow = '^'; break;
              case 3: arrow = 'v'; break;
            }
          }
        }
      } 
      Color cell_color = tape_->GetCell(i, j);
      if(ants_in_cell > 0) {
        if(ants_in_cell > 1) arrow = '+'; 
        std::cout << tape_->ColorToCode(cell_color) << arrow << RESET;
      } else {
        std::cout << tape_->ColorToCode(cell_color) << "■" << RESET;
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
    std::vector<std::unique_ptr<Ant>> newborns;
    std::system("clear");
    PrintTape();
    std::cout << "STEP COUNT: " << step_count << "\n" << std::endl;
    for(auto& ant : ants_) {
      std::cout << "\t" << ant->GetAlimentation() << "-" << ant->GetType() << ": (" << ant->GetX() << "," << ant->GetY() << ") " << ant->GetLifeTime() << "\n";
    }
    std::cout << "(N)ext step / (S)ave current state" << std::endl;
    char answer = 'N';
    std::cin >> answer;
    if(ants_.empty()) {
      std::cout << "[DONE]: All ant's lifetimes have reached 0. The simulation is OVER." << std::endl;
      break;
    }
    if(answer == 'N') {
      step_count++;
      for(auto& ant : ants_) {
        ant->Step(tape_.get());
        tape_->CheckMove(ant.get());
        ant->SumToLifeTime(-1);
      }
      ProcreateRules(newborns);
      UpdateLifeTime();
      AddNewbornsToMainVector(newborns);
      ants_.erase(std::remove_if(ants_.begin(), ants_.end(), [](const std::unique_ptr<Ant>& ant) {return ant->GetLifeTime() <= 0;} ), ants_.end());
      continue;
    } else if(answer == 'S') {
      std::string output_file_name;
      std::cout << "Type the export file's name: ";
      std::cin >> output_file_name;
      ExportFile(output_file_name);
      std::cout << "[DONE]: File exported" << std::endl;
      break;
    } else {
      std::cout << "[ERROR]: Wrong option, try again" << std::endl;
    }
  }
}

void Simulator::ProcreateRules(std::vector<std::unique_ptr<Ant>>& newborns) {
  std::vector<std::pair<int, int>> breeding_locations; 
  for(size_t i = 0; i < ants_.size(); i++) {
    for(size_t j = i + 1; j < ants_.size(); j++) {
      if ((ants_[i]->GetX() == ants_[j]->GetX() && ants_[i]->GetY() == ants_[j]->GetY()) && 
          (ants_[i]->GetAlimentation() == ants_[j]->GetAlimentation() && ants_[i]->GetType() == ants_[j]->GetType())) {
        int x = ants_[i]->GetX();
        int y = ants_[i]->GetY();
        bool already_bred = false;
        for (const auto& loc : breeding_locations) {
          if (loc.first == x && loc.second == y) {
            already_bred = true;
            break;
          }
        }
        if (!already_bred) {
          breeding_locations.push_back({x, y});
          if(ants_[i]->GetAlimentation() == 'H' && ants_[i]->GetType() == "DDII") {
            newborns.push_back(std::make_unique<Ant_H_DDII>(0, DEFAULT_LIFE_TIME, x, y));
          } else if(ants_[i]->GetAlimentation() == 'C' && ants_[i]->GetType() == "IDID") {
            newborns.push_back(std::make_unique<Ant_C_IDID>(0, DEFAULT_LIFE_TIME, x, y));
          }
        }
      }
    }
  }
}

/**
 * @brief Checks for collisions in the same cell to resolve combats.
 * If two ants share the same coordinates, it delegates the event to ApplyCarnivoreRules.
 */
void Simulator::UpdateLifeTime() {
  std::vector<std::unique_ptr<Ant>> newborns;
  std::vector<std::pair<int, int>> breeding_locations;
  for (size_t i = 0; i < ants_.size(); i++) {
    for (size_t j = i + 1; j < ants_.size(); j++) {
      if (ants_[i]->GetX() == ants_[j]->GetX() && ants_[i]->GetY() == ants_[j]->GetY()) {
        ApplyCarnivoreRules(ants_[i].get(), ants_[j].get());
        ApplyCarnivoreRules(ants_[j].get(), ants_[i].get());
      }
    }
  }
}

void Simulator::AddNewbornsToMainVector(std::vector<std::unique_ptr<Ant>>& newborns) {
  for(size_t i = 0; i < newborns.size(); i++) {
    ants_.push_back(std::move(newborns[i]));
  }
}

/**
 * @brief Applies damage and health absorption rules if the attacker is a carnivore.
 * Uses RTTI (dynamic_cast) to verify inheritance without relying on type variables.
 * @param attacker Pointer to the ant evaluating its attack.
 * @param victim Pointer to the target ant.
 */
void Simulator::ApplyCarnivoreRules(Ant* attacker, Ant* victim) {
  Ant_C* carnivore = dynamic_cast<Ant_C*>(attacker);
  if(carnivore != nullptr) {
    int stolen_life = static_cast<int>(victim->GetLifeTime() * carnivore->GetVoracity());
    if (stolen_life == 0) stolen_life = 1;
    victim->SumToLifeTime(-stolen_life);
    carnivore->SumToLifeTime(stolen_life);
  }
}

/**
 * @brief Private method to export the tape and ant to a file with the same 
 *        structure as the input_file.
 * 
 */
void Simulator::ExportFile(std::string& file_name) {
  std::ofstream output_file{file_name};
  output_file << tape_->GetXSize() << " " << tape_->GetYSize() << " " << number_of_colors_ << "\n";
  for(size_t i = 0; i < ants_.size(); i++) {
    char arrow = ' ';
    switch(ants_[i]->GetOrientation()) {
      case 0: arrow = '<'; break;
      case 1: arrow = '>'; break;
      case 2: arrow = '^'; break;
      case 3: arrow = 'v'; break;
    }
    output_file << ants_[i]->GetAlimentation() << "-" << ants_[i]->GetType() << " " << ants_[i]->GetX() << " " << ants_[i]->GetY() << " " << arrow;
    if(i != (ants_.size() - 1)) {
      output_file << " ; ";
    }
  }
  output_file << "\n";
  for(size_t i = 0; i < tape_->GetXSize(); i++) {
    for(size_t j = 0; j < tape_->GetYSize(); j++) {
      if(tape_->GetCell(i, j) != Color::WHITE_CELL) {
        output_file << i << " " << j << " " << static_cast<int>(tape_->GetCell(i, j)) << "\n";
      }
    }
  }
}