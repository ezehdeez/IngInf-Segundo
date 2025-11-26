/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P02 - Cadenas y Lenguajes
 * 
 * @file cadena.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-09-17
 * @brief 
 */

#ifndef CHAIN_H_
#define CHAIN_H_

#include <string>
#include "alphabet.h"

typedef char symbol;

class Language;

class Chain {
 public:
  // Default constructor 
  Chain() : alphabet_{Alphabet ("")}, chain_{"&"}, size_{0} {}
  // Constructor from a string and an alphabet
  Chain(const std::string& string, const Alphabet& alphabet) : alphabet_(alphabet), 
  chain_(string), size_(string.size()) {}
  // Copy constructor
  Chain(const Chain& chain) : alphabet_{chain.alphabet_}, chain_{chain.chain_}, 
  size_{chain.size_} {}
  // Getters
  size_t getSize() const {return size_;}
  std::string getChain() const {return chain_;}
  Alphabet getAlphabet() const {return alphabet_;}
  // Methods
  Chain Inverse();
  Language Prefixes();
  Language Suffixes();
  bool SearchSubsequence(std::string& subsequence);
  
  bool operator<(const Chain& other) const; 
 private:
  Alphabet alphabet_;
  std::string chain_;
  size_t size_;
};

Chain operator+(Chain& chain1, Chain& chain2);
std::ostream& operator<<(std::ostream& out, const Chain& chain);

#endif