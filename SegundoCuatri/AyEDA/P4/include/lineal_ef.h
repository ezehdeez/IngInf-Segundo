/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: 
 * 
 * @file linear_ef.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief 
 */

#pragma once

#include "exploration_function.h"

template <class Key>
class LinearEF : public ExplorationFunction<Key> {
 public:
  LinearEF() = default;

  unsigned operator()(const Key& k, unsigned i) const override {
    return i;
  }
};