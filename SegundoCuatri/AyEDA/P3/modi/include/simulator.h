/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P3
 * 
 * @file simulator.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-02-09
 * @brief Langton's Ant simulator class declaration, created by an ant and a non
 *        infinite tape.
 */

#include "../include/derivated_ants.h"
#include "../include/derivated_tapes.h"

#include <string>
#include <memory>

#ifndef SIMULATOR_H
#define SIMULATOR_H

class Simulator {
 public:
  // Constructor from a file name
  Simulator(const std::string&, int);

  // Destructor
  ~Simulator() {}

  // Run simulation method
  void RunSimulation();
  
 private:
  int number_of_colors_;
  std::vector<std::unique_ptr<Ant>> ants_;
  std::unique_ptr<Tape> tape_;
  
  void PrintTape();
  void ProcreateRules(std::vector<std::unique_ptr<Ant>>& newborns);
  void UpdateLifeTime();
  void AddNewbornsToMainVector(std::vector<std::unique_ptr<Ant>>& newborns);
  void ApplyCarnivoreRules(Ant*, Ant*);
  void ExportFile(std::string&);
};

#endif