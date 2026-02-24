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
#include <memory>

class Simulator {
 public:
  // Constructor from a file name
  Simulator(const std::string&);

  // Destructor
  ~Simulator() {}

  // Run simulation method
  void RunSimulation();
  
 private:
  int number_of_colors_;
  std::vector<std::unique_ptr<Ant>> ants_;
  Tape tape_;
  
  void PrintTape();
  void ExportFile();
};