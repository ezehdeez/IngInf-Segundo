#include "../include/simulator.h"

#include <fstream>
#include <sstream>

Simulator::Simulator(const std::string& file_name) {
  std::cout << "In simulator building" << std::endl;
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
  std::cout << "pre tape build " << x_size << " " << y_size << std::endl;
  Tape tape{x_size, y_size};
  std::cout << "tape built" << std::endl;
  Ant ant{ant_orientation, ant_x, ant_y};
  while(getline(input_file, line)) {
    iss = std::istringstream(line);
    size_t row, column;
    iss >> row >> column;
    tape.DrawCell(row, column);
  }
  tape_ = tape;
  ant_ = ant;
  std::cout << "Simulator built" << std::endl;
}

void Simulator::RunSimulation() {
  int step_count = 0;
  while(true) {
    std::system("clear");
    tape_.PrintUntilAnt(&ant_);
    std::cout << ant_;
    tape_.PrintPostAnt(&ant_);
    std::cout << "STEP COUNT: " << step_count << "\n" << std::endl;
    std::cout << "(N)ext step / (S)ave current state" << std::endl;
    std::cout << "ant at " << ant_.GetOrientation() << "pos: "<< ant_.GetX() << " " << ant_.GetY()<<std::endl;
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