/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P7
 * 
 * @file nodoavl.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-29
 * @brief AVL node class derived from binary node with balance factor support.
 */

#pragma once

#include "nodob.h"

template <class Key>
class NodoAVL : public NodoB<Key> {
 public:
  NodoAVL(const Key& data, NodoB<Key>* left = nullptr, NodoB<Key>* right = nullptr, int bal = 0)
  : NodoB<Key>(data, left, right), bal_(bal) {}

  int GetBal() const {return bal_;}
  void SetBal(int bal) {bal_ = bal;}
 private:
  int bal_;  
};