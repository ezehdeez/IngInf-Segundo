/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: 
 * 
 * @file main.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief 
 */

#include "../include/config.h"
#include "../include/functions.h"
#include "../include/hash_table.h"
#include "../include/nif.h"

#include <string>

int main(int argc, char* argv[]) {
  ProgramConfig config = ParseArguments(argc, argv);
  Sequence<NIF>* table = CreateTable(config);
  RunMenu(*table);
  delete table;
  return 0;
}