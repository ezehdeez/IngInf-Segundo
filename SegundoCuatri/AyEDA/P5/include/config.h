/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P5
 * 
 * @file config.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-11
 * @brief Defines the ProgramConfig structure to store configuration parameters 
 *        (size, method, initialization mode, and trace) parsed from 
 *        command-line arguments.
 */

#include <string>

struct ProgramConfig {
  size_t sequence_size{0};
  char sort_method{' '}; // Represented by a letter from a to d.
  std::string init_mode{""}; // Manual, random or through a file.
  std::string filename{""};
  bool dotrace{false};
};