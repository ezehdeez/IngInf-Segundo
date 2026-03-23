/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 *  
 * @subject: AyEDA - P3
 *  
 * @file ddispersion_ef.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief Implementation of the double dispersion exploration function,
 * which uses an auxiliary dispersion function to calculate the jump.
 */

#pragma once

#include "dispersion_function.h"
#include "exploration_function.h"

template <class Key>
class DDispersionEF : public ExplorationFunction<Key> {
 public:
  DDispersionEF(DispersionFunction<Key>& df) : df_{&df} {}

  // Evitar copias para quitar warnings a la hora de compilar
  DDispersionEF(const DDispersionEF&) = delete;
  DDispersionEF& operator=(const DDispersionEF&) = delete;

  unsigned operator()(const Key& k, unsigned i) const override {
    return (*df_)(k) * i;
  }
 private:
  DispersionFunction<Key>* df_;
};