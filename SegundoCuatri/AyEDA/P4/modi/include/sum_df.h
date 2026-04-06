/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 *  
 * @subject: AyEDA - P3
 *  
 * @file sum_df.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief Implementation of the dispersion function based on the sum of
 * the digits that make up the numeric key.
 */

#pragma once

#include "dispersion_function.h"

template <class Key>
class SumDF : public DispersionFunction<Key> {
 public:
  SumDF(unsigned table_size) : table_size_{table_size} {}

  unsigned operator()(const Key& k) const {
    unsigned sum = 0;
    long value = (long)k;
    while(value > 0) {
      sum += (value % 10);
      value /= 10;
    }
    return sum % table_size_;
  }

 private:
  unsigned table_size_;
};