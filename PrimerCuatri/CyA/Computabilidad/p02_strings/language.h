/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P02 - Cadenas y Lenguajes
 * 
 * @file language.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-09-17
 * @brief Language declaration as a set of chains, used for certain 
 *        representations.
 */

#ifndef LANGUAGE_H_
#define LANGUAGE_H_

#include <fstream>
#include <set>

class Chain;

class Language {
 public:
  // Default constructor
  Language() : chains_{} {}
  // Constructo from a set of chains
  Language(std::set<Chain>& chains) : chains_{chains} {}
  // Copy constructor
  Language(Language& other) : chains_{other.chains_} {}
  // Set getter
  std::set<Chain> getSet() const {return chains_;}
 private:
  std::set<Chain> chains_;
};

std::ostream& operator<<(std::ostream& out, const Language& language);

#endif