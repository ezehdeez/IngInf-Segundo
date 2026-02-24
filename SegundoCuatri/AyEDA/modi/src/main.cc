/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P1
 * 
 * @file main.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-02-09
 * @brief Main program of the Langon's Ant simulation. This simulation is based
 *        on an ant which follows a set of instructions to move through an infinite
 *        tape (in our case is finite). Input file has to follow the next format:
 * 
 *            Línea 1: Tamaño de la cinta
 *            Línea 2: Posición inicial y orientación de la hormiga
 *            Línea 3..n: Posiciones de las celdas negras (valor binario 1).
 */

#include "../include/ant.h"
#include "../include/functions.h"
#include "../include/tape.h"
#include "../include/simulator.h"

#include <iostream>

int main(int argc, char* argv[]) {
  CheckCorrectParameters(argc, argv, 2);
  FileCheck(argv[1]);
  Simulator simulator(argv[1]);
  simulator.RunSimulation();
  return 0;
}