/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P7
 * 
 * @file config.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-16
 * @brief Program configuration structure for command-line options.
 */

#pragma once

#include <string>

struct ProgramConfig {
  std::string tree_type{""};
  std::string init_mode{""};
  size_t element_amount{0};
  std::string file_name{""};
  bool trace{false};
};