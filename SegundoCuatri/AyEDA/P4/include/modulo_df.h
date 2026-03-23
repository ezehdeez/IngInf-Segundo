/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 *  
 * @subject: AyEDA - P3
 *  
 * @file modulo_df.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief Implementation of the dispersion function based on the division
 * (modulo) method over the table size.
 */

#pragma once

#include "dispersion_function.h"

template <class Key>
class ModuloDF : public DispersionFunction<Key> {
 public:
  ModuloDF(unsigned table_size) : table_size_{table_size} {}

  unsigned operator()(const Key& k) const {
    return (long)k % table_size_;
  }

 private:
  unsigned table_size_;
};