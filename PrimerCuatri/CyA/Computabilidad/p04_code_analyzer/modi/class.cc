/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: 
 * 
 * @file class.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-08
 * @brief 
 */

#include "class.h"

std::ostream& operator<<(std::ostream& out, Class& classes) {
  out << classes.getName() << ": Líneas " << classes.getStartLine() << "-" <<
  classes.getEndLine();
  return out;
}