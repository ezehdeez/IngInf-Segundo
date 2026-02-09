/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P1
 * 
 * @file tape.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-02-09
 * @brief Tape class inicialization
 */

#include "../include/ant.h"
#include "../include/colors.h"
#include "../include/tape.h"

#include <iostream>

/**
 * @brief This method is going to print each cell until reaching an ant.
 * 
 * @param ant 
 */
void Tape::PrintUntilAnt(Ant* ant) {
  for(size_t i = 0; i < GetXSize(); i++) {
    for(size_t j = 0; j < GetYSize(); j++) {
      if(i == static_cast<size_t>(ant->GetX()) && j == static_cast<size_t>(ant->GetY())) return;
      if(GetCell(i, j)) {
        std::cout << BLUE << "■" << RESET;
      } else {
        std::cout << LBLUE << "■" << RESET;
      }
    }
    if(i != static_cast<size_t>(ant->GetX())) {
      std::cout << std::endl;
    }
  }
}

/**
 * @brief This method is going to print each cell after the ant.
 * 
 * @param ant 
 */
void Tape::PrintPostAnt(Ant* ant) {
  for(size_t i = ant->GetX(); i < GetXSize(); i++) {
    size_t startY = (i == static_cast<size_t>(ant->GetX())) ? ant->GetY() + 1 : 0;
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

/**
 * @brief << operator overloading for printing the tape without ants.
 * 
 * @param out 
 * @param tape_to_print 
 * @return std::ostream& 
 */
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