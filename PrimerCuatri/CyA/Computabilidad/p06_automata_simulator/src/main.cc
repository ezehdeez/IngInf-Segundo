/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P06 - Diseño e implemetación de un simulador de autómatas finitos
 * 
 * @file main.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-16
 * @brief This program will take two files as parameters, a Finite Automaton as a
 *        .fa file, and an input file. The Finite Automaton will be simulated, and
 *        the strings in the input file are the tests to the Automaton. The program
 *        will print for every single string if it is accepted or rejected by
 *        the automaton.
 */

#include <iostream>
#include <string>

#include "../lib/automaton.h"
#include "../lib/automaton_loader.h"
#include "../lib/functions.h"
#include "../lib/alphabet.h"

int main(int argc, char* argv[]) {
  if(argc == 2) {
    HelpMessage(argv);
  }
  CheckCorrectParameters(argc, 3);
  FileCheck(argv[2], argv[1]);
  AutomatonLoader::AutomatonData data = AutomatonLoader::Loader(argv[1]);
  Automaton automaton(data.alphabet, data.starter_state, data.num_states, data.states);
  PrintStringBelongsToFA(argv[2], automaton);
  return 0;
}