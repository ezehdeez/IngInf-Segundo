/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P08 - Gramáticas en Forma Normal de Chomsky
 * 
 * @file grammar_loader.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-29
 * @brief Grammar Loader class declaration used to extract the information from
 *        a .gra file to be used for Grammar objects creation.
 */

#pragma once

#include <map>

#include "../include/alphabet.h"

using NTSymbol = std::string;

class GrammarLoader{
 public:
  struct GrammarData{
    Alphabet alphabet_;
    std::set<NTSymbol> non_terminal_symbols_;
    NTSymbol start_symbol_;
    std::multimap<NTSymbol, std::string> productions_;

    GrammarData(Alphabet& alphabet, std::set<NTSymbol>& non_terminal_symbols,
    NTSymbol start_symbol, std::multimap<NTSymbol, std::string>& productions) :
    alphabet_{alphabet}, non_terminal_symbols_{non_terminal_symbols},
    start_symbol_{start_symbol}, productions_{productions} {}
  };

  static GrammarData Loader(const std::string& file_name);
};