/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P5
 * 
 * @file main.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-07
 * @brief Main entry point of the application. Coordinates argument parsing, 
 *        executes the chosen sorting strategy, and manages exception handling.
 */

#include "../include/functions.h"
#include "../include/nif.h"
#include "../include/sort_method.h"

int main(int argc, char* argv[]) {
  try {
    ProgramConfig config = ParseArguments(argc, argv);
    SortMethod<NIF>* sort_method = BuildSortMethod(config);
    if (sort_method != nullptr) {
      sort_method->Sort();
      delete sort_method;
    }
  } catch(const std::runtime_error& e) {
    std::cerr << "\n" << e.what() << "\n";
    return 1;
  } catch(const std::exception& e) {
    std::cerr << "[ERROR]: " << e.what() << "\n";
    return 1;
  }
  return 0;
}