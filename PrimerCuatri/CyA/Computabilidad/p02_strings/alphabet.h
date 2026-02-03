/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P02 - Cadenas y Lenguajes
 * 
 * @file alphabet.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-09-17
 * @brief Alphabet class declaration as a set of symbols (chars) that's used
 *        for chain representation.
 */

#ifndef ALPHABET_H_
#define ALPHABET_H_

#include <set>
#include <string>
#include <iostream>

typedef char symbol;

class Alphabet {
 public:
  // Constructor from an alphabet
  Alphabet(const std::string& alphabet);
  // Constructor from a single symbol
  Alphabet(symbol symbol) {alphabet_.emplace(symbol);}
  // Set getter
  std::set<symbol> getSet() const {return alphabet_;}
 private:
  std::set<symbol> alphabet_;
};

std::ostream& operator<<(std::ostream& out, const Alphabet& alphabet);

#endif