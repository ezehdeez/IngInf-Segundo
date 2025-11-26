/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P02 - Cadenas y Lenguajes
 * @file alphabet.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-09-17
 * @brief Alphabet class inicialization
 */

#include <fstream>
#include <string>
#include "alphabet.h"

typedef char symbol;

Alphabet::Alphabet(const std::string& alphabet) {
  for(size_t i = 0; i < alphabet.size(); i++) {
    alphabet_.emplace(alphabet[i]);
  }
}

/**
 * @brief Output operator overloading, alphabet format: "{a, b, c, ...}""
 * 
 * @param out 
 * @param alphabet 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& out, const Alphabet& alphabet) {
  std::set<char> alphabet_set(alphabet.getSet());
  out << "{";
  for(std::set<char>::iterator iterator = alphabet_set.begin(); iterator != alphabet_set.end(); ) {
    out << *iterator;
    iterator++;
    if(iterator != alphabet_set.end()) {
      out << ", ";
    }
  }
  out << "}";
  return out;
}