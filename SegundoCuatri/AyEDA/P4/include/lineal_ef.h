/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 *  
 * @subject: AyEDA - P3
 *  
 * @file lineal_ef.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief Implementation of the linear exploration function, which
 * increments the displacement sequentially (i).
 */

#pragma once

#include "exploration_function.h"

template <class Key>
class LinearEF : public ExplorationFunction<Key> {
 public:
  LinearEF() = default;

  unsigned operator()(const Key&, unsigned i) const override {
    return i;
  }
};