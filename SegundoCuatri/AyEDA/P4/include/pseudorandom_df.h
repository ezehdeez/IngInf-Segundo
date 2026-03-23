/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 *  
 * @subject: AyEDA - P3
 *  
 * @file pseudorandom_df.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief Implementation of the pseudo-random dispersion function, using
 * the key itself as the generator seed.
 */

#pragma once

#include "dispersion_function.h"

#include <cstdlib>

template <class Key>
class PseudorandomDF : public DispersionFunction<Key> {
 public:
  PseudorandomDF(unsigned table_size) : table_size_{table_size} {}

  unsigned operator()(const Key& k) const {
    long valor = (long)k;
    srand(valor);
    return rand() % table_size_;
  }
  
 private:
  unsigned table_size_;
};