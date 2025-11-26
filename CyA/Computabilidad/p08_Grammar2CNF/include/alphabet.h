/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P08 - Gramáticas en Forma Normal de Chomsky
 * 
 * @file alphabet.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-29
 * @brief Alphabet class declaration as a set of symbols (chars) that's used
 *        for chain representation.
 */

#pragma once

#include <set>
#include <string>
#include <iostream>

typedef char symbol;

class Alphabet {
 public:
  Alphabet() = default;
  // Constructor from an alphabet
  Alphabet(const std::string& alphabet);
  // Set getter
  std::set<symbol> getSet() const {return alphabet_;}
  bool CheckSymbol(symbol symbol);
  void InsertSymbol(symbol s) {alphabet_.insert(s);}
 private:
  /**
   * @brief alphabet_ being a set of symbols as its formal definition.
   * 
   */
  std::set<symbol> alphabet_;
};

std::ostream& operator<<(std::ostream& out, const Alphabet& alphabet);