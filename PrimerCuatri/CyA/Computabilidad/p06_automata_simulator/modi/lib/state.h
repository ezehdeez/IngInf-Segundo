/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: CyA 25-26
 *           P06 - Diseño e implemetación de un simulador de autómatas finitos
 * 
 * @file state.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2025-10-16
 * @brief State class declaration, it stores the state identification number, if
 *        it is an aceptation state, the number of transitions and a multimap to
 *        store every transition (symbol and objective state). It also contains 
 *        a few methods, being the most important and used the InsertTransition().
 */

#pragma once

class State{
 public:
  State() = default;
  State(int state, bool is_aceptation, int num_transitions) : state_{state}, 
  is_aceptation_{is_aceptation}, num_transitions_{num_transitions}, transitions_{} {}
  void InsertTransition(char symbol, int state) {transitions_.insert({symbol, state});}
  int getState() const {return state_;}
  bool getIsAceptation() const {return is_aceptation_;}
  int getNumTransitions() const {return num_transitions_;}
  std::multimap<symbol, int> getTransitions() const {return transitions_;}
 private:
  int state_;
  bool is_aceptation_;
  int num_transitions_;
  std::multimap<symbol, int> transitions_;
};