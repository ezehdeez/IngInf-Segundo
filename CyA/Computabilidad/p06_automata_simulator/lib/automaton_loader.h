/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P06 - Diseño e implemetación de un simulador de autómatas finitos
 * 
 * @file automaton_loader.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-17
 * @brief AutomatonLoader class declaration which is used to extract the data
 *        of the automaton from a .fa file, to be subsequently inserte into the
 *        automaton object.
 */

#pragma once

#include <map>

#include "../lib/alphabet.h"
#include "../lib/state.h"

class AutomatonLoader{
 public:
  struct AutomatonData{
    const std::map<int, State> states;
    int starter_state;
    int num_states;
    const Alphabet alphabet;

    AutomatonData(const std::map<int, State>& s, int start, int num, const Alphabet& a)
    : states(s), starter_state(start), num_states(num), alphabet(a) {}
  };

  static AutomatonData Loader(const std::string& file_name);
};