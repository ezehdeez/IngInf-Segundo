/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: 
 * 
 * @file nif.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief 
 */

#include "../include/nif.h"

#include <cstdlib>
#include <stdexcept>

NIF::NIF() : value_{} {
  value_ = rand() % 100000000;
}

NIF::NIF(long nif) : value_{} {
  if(nif < 0 || nif > 99999999) {
    throw std::invalid_argument("[ERROR]: El NIF debe ser un número positivo de máximo 8 dígitos (0 - 99999999).");
  }
  value_ = nif;
}

NIF::operator long() const {
  return value_;
}

bool operator==(const NIF& nif1, const NIF& nif2) {
  return nif1.GetValue() == nif2.GetValue();
}

bool operator<(const NIF& nif1, const NIF& nif2) {
  return nif1.GetValue() < nif2.GetValue();
}