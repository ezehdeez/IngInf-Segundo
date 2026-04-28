/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P6
 * 
 * @file main.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-16
 * @brief 
 */

#include "../include/functions.h"
#include "../include/nif.h"

#include <iostream>

int main(int argc, char* argv[]) {
  try {
    ProgramConfig config = ParseArguments(argc, argv);
    AB<NIF>* arbol = BuildTree(config);
    InitializeTree(arbol, config);
    RunMenu(arbol);
    delete arbol;
  } catch(const std::runtime_error& e) {
    std::cerr << "\n" << e.what() << "\n";
    return 1;
  } catch(const std::exception& e) {
    std::cerr << "[ERROR]: " << e.what() << "\n";
    return 1;
  }
  return 0;
}