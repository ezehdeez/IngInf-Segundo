/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: SSOO
 * 
 * @file functions.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-11-26
 * @brief 
 */

#include <string>

#include "../includes/functions.h"

std::string GetEnviromentalVariable(const std::string& name) {
  char* value = getenv(name.c_str());
  if(value) {
  return std::string(value);
  } else {
  return std::string();
  }
}