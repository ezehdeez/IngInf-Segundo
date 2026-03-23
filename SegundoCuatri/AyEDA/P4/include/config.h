/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P3
 * 
 * @file config.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief Defines the ProgramConfig structure to store the Hash table
 *        configuration passed via command-line arguments.
 */

#pragma once

#include <string>

struct ProgramConfig {
  unsigned table_size = 0;
  std::string disp_func = "";
  std::string hash_type = "";
  unsigned block_size = 0;
  std::string exp_func = "";
};