/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P02 - Cadenas y Lenguajes
 * 
 * @file cadena.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-09-17
 * @brief 
 */

#include <iostream>
#include <string>

#include "chain.h"
#include "language.h"

typedef char symbol;

/**
 * @brief When applied to a chain, this method returns the inverse.
 * 
 * @return Chain 
 */
Chain Chain::Inverse() {
  std::string inversed_string;
  for(int i = getSize() - 1; i >= 0; i--) {
    inversed_string.push_back(getChain()[i]);
  }
  Chain inverse(inversed_string, alphabet_);
  return inverse;
}

/**
 * @brief This operator overloading is used for set sorting.
 * 
 * @param other 
 * @return bool 
 */
bool Chain::operator<(const Chain& other) const{
  return chain_ < other.chain_;
}

/**
 * @brief When applied to a chain, this method returns as a language all the 
 *        posible prefixes.
 * 
 * @return Language 
 */
Language Chain::Prefixes() {
  std::set<Chain> chain_set;
  chain_set.emplace(Chain ("&", alphabet_));
  for(size_t i = 1; i <= size_; i++) {
    chain_set.emplace(Chain (chain_.substr(0, i), alphabet_));
  }
  Language prefixes(chain_set);
  return prefixes;
}

/**
 * @brief When applied to a chain, this method returns as a language all the
 *        posible suffixes.
 * 
 * @return Language 
 */
Language Chain::Suffixes() {
  std::set<Chain> chain_set;
  chain_set.emplace(Chain ("&", alphabet_));
  for(int i = size_ - 1; i >= 0; i--) {
    chain_set.emplace(Chain (chain_.substr(i), alphabet_));
  }
  Language suffixes(chain_set);
  return suffixes;
}

bool Chain::SearchSubsequence(std::string& subsequence) {
  if(subsequence.empty()) {
    return true;
  }
  size_t subsequence_i = 0;
  for(size_t i = 0; i < size_ && subsequence_i < subsequence.size(); i++) {
    if(chain_[i] == subsequence[subsequence_i]) {
      subsequence_i++;
    }
  }
  return subsequence_i == subsequence.size();
}

/**
 * @brief Operator overloading that is used as a chain concatenation, they should
 *        have the same alphabet.
 * 
 * @param chain1 
 * @param chain2 
 * @return Chain 
 */
Chain operator+(Chain& chain1, Chain& chain2) {
  std::string concatenated_string = chain1.getChain() + chain2.getChain();
  Alphabet alphabet = chain1.getAlphabet();
  Chain concatenated(concatenated_string, alphabet);
  return concatenated;
}

/**
 * @brief Operator overloading for chains.
 * 
 * @param out 
 * @param chain 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& out, const Chain& chain) {
  std::string chain_content = chain.getChain();
  out << chain_content;
  return out;
}