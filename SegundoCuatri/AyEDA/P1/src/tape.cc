#include "../include/ant.h"
#include "../include/colors.h"
#include "../include/tape.h"

#include <iostream>

void Tape::PrintUntilAnt(Ant* ant) {
  for(size_t i = 0; i < GetXSize(); i++) {
    for(size_t j = 0; j < GetYSize(); j++) {
      if(i == ant->GetX() && j == ant->GetY()) return;
      if(GetCell(i, j)) {
        std::cout << BLUE << "■" << RESET;
      } else {
        std::cout << LBLUE << "■" << RESET;
      }
    }
    if(i != ant->GetX()) {
      std::cout << std::endl;
    }
  }
}

void Tape::PrintPostAnt(Ant* ant) {
  for(size_t i = ant->GetX(); i < GetXSize(); i++) {
    size_t startY = (i == ant->GetX()) ? ant->GetY() + 1 : 0;
    for(size_t j = startY; j < GetYSize(); j++) {
      if(GetCell(i, j)) {
        std::cout << BLUE << "■" << RESET;
      } else {
        std::cout << LBLUE << "■" << RESET;
      }
    }
    std::cout << std::endl;
  }
}

std::ostream& operator<<(std::ostream& out, const Tape& tape_to_print) {
  for(size_t i = 0; i < tape_to_print.GetXSize(); i++) {
    for(size_t j = 0; j < tape_to_print.GetYSize(); j++) {
      if(tape_to_print.GetCell(i, j)) {
        out << BLUE << "■";
      } else {
        out << LBLUE << "■";
      }
    }
    out << "\n";
  }
  return out;
}