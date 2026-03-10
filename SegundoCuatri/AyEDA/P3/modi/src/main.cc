/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P3
 * 
 * @file main.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-02-09
 * @brief Main program of the Langon's Ant simulation. This simulation is based
 *        on an ant which follows a set of instructions to move through an infinite
 *        tape (in our case is finite). Input file has to follow the next format:
 * 
 *            Línea 1: 7 10 4
 *            Línea 2: H-DDII 3 3 > ; C-IDID 5 7 v
 *            Línea 3: 3 4 1
 *            Línea 4: 3 5 2
 *            Línea 5: 5 5 3
 */

#include "../include/ant.h"
#include "../include/functions.h"
#include "../include/tape.h"
#include "../include/simulator.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  CheckCorrectParameters(argc, argv, 3);
  FileCheck(argv[1]);
  std::string type(argv[2]);
  Simulator simulator(argv[1], TapeType(type));
  simulator.RunSimulation();
  return 0;
}