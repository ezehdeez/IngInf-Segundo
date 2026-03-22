/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: 
 * 
 * @file ddispersion_ef.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief 
 */

#pragma once

#include "dispersion_function.h"
#include "exploration_function.h"

template <class Key>
class DDispersionEF : public ExplorationFunction<Key> {
 public:
  DDispersionEF(DispersionFunction<Key>& df) : df_{&df} {}

  unsigned operator()(const Key& k, unsigned i) const override {
    return (*df_)(k) * i;
  }
 private:
  DispersionFunction<Key>* df_;
};