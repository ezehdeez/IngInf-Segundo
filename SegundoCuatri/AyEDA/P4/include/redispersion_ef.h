/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: 
 * 
 * @file redispersion_ef.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief 
 */

#pragma once

#include "exploration_function.h"

#include <cstdlib>

template <class Key>
class RedispersionEF : public ExplorationFunction<Key> {
 public:
  RedispersionEF() = default;

  unsigned operator()(const Key& k, unsigned i) const override {
    unsigned desplazamiento;
    srand((long)k);
    for(size_t j = 0; j < i; j++) {
      desplazamiento = rand();
    }
    return desplazamiento;
  }
};