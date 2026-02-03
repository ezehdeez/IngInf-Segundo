/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P06 - Diseño e implemetación de un simulador de autómatas finitos
 * 
 * @file automaton.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-16
 * @brief Automaton class inicialization.
 */

#include <stack>

#include "../lib/automaton.h"

/**
 * @brief It uses a stack to check for every state if it has epsilon transitions
 *        in it, every available state without consuming a single symbol will be
 *        stored in the returned set. 
 * 
 * @param state 
 * @return std::set<int> 
 */
std::set<int> Automaton::EpsilonClosure(const int state) {
  std::stack<int> stack;
  std::set<int> visited;
  stack.push(state);
  visited.insert(state);
  while(!stack.empty()) {
    int current = stack.top();
    stack.pop();
    std::pair<std::multimap<symbol, int>::const_iterator, std::multimap<symbol, int>::const_iterator> epsilon_range = states_[current].getTransitions().equal_range(EMPTY_STRING);
    for(auto it = epsilon_range.first; it != epsilon_range.second; it++) {
      int next = it->second;
      if(visited.find(next) == visited.end()) continue;
      visited.insert(next);
      stack.push(next);
    }
  }
  return visited;
}

/**
 * @brief EpsilonClosure adapted for a set of states instead of a single state.
 * 
 * @param states 
 * @return std::set<int> 
 */
std::set<int> Automaton::EpsilonClosure(const std::set<int>& states) {
  std::set<int> full_closure;
  for(int state : states) {
    std::set<int> closure = EpsilonClosure(state);
    full_closure.insert(closure.begin(), closure.end());
  }
  return full_closure;
}

/**
 * @brief This method check for every symbol in a string if it belongs to the
 *        automaton. Firstly it checks if the symbol belongs to the alphabet, then
 *        checks for every of the current states if any new state can be reached
 *        with the symbol, if it can, this state will be added to the new states
 *        for the next iteration. After every iteration we add EpsilonClosure of
 *        the new_states to current states, with this we update the set to advance
 *        in the algorithm. If any of the states in new_states when the algorithm 
 *        finish is an aceptation state, the string belongs to the language
 *        represented by the automaton.
 * 
 * @param string 
 * @return bool 
 */
bool Automaton::VerifyString(const std::string& string) {
  std::set<int> current_states;
  current_states.insert(starter_state_);
  current_states = EpsilonClosure(current_states);
  for(symbol c : string) {
    if(c == EMPTY_STRING) continue;
    if(alphabet_.CheckSymbol(c)) {
      return false;
    }
    std::set<int> new_states;
    for(int state : current_states) {
      std::multimap<symbol, int> transitions = states_[state].getTransitions();
      std::pair<std::multimap<symbol, int>::const_iterator, std::multimap<symbol, int>::const_iterator> range = transitions.equal_range(c);
      for(auto it = range.first; it != range.second; it++) {
        new_states.insert(it->second);
      }
    }
    if(new_states.empty()) {
      return false;
    }
    current_states = EpsilonClosure(new_states);
  }
  for(int state : current_states) {
    if(states_[state].getIsAceptation()) {
      return true;
    }
  }
  return false;
}