/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P02 - Cadenas y Lenguajes
 * 
 * @file language.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-09-18
 * @brief Language class inicialization
 */

#include <fstream>
#include "chain.h"
#include "language.h"

/**
 * @brief Output operator overloading, language format: "{"ab", "ac", ...}"
 * 
 * @param out 
 * @param language 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& out, const Language& language) {
  std::set<Chain> language_set(language.getSet());
  out << "{";
  for(std::set<Chain>::iterator iterator = language_set.begin(); iterator != language_set.end(); ) {
    out << *iterator;
    iterator++;
    if(iterator != language_set.end()) {
      out << ", ";
    }
  }
  out << "}";
  return out;
}