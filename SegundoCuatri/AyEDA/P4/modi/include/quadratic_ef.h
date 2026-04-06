/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 *  
 * @subject: AyEDA - P3
 *  
 * @file quadratic_ef.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief Implementation of the quadratic exploration function, which
 * increments the displacement based on the square of the attempt (i^2).
 */

#pragma once

#include "exploration_function.h"

template <class Key>
class QuadraticEF : public ExplorationFunction<Key> {
 public:
  QuadraticEF() = default;

  unsigned operator()(const Key&, unsigned i) const override {
    return i*i;
  }
};