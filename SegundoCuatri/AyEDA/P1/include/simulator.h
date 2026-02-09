/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P1
 * 
 * @file simulator.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-02-09
 * @brief Langton's Ant simulator class declaration, created by an ant and a non
 *        infinite tape.
 */

#include "../include/ant.h"
#include "../include/tape.h"

#include <string>

class Simulator {
 public:
  // Constructor from a file name
  Simulator(const std::string&);

  // Run simulation method
  void RunSimulation();
  
 private:
  Ant ant_;
  Tape tape_;
  
  void ExportFile();
};