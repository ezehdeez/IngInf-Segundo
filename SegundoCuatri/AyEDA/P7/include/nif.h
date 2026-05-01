/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P7
 * 
 * @file nif.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-07
 * @brief NIF class that encapsulates a tax identification number, managing
 *        its validation and operator overloading for mathematical manipulation.
 */

#pragma once

#include <stdexcept>

class NIF{
 public:
  NIF();
  NIF(long);

  long GetValue() const {return value_;}

  operator long() const;
 private:
  long value_;
};

bool operator==(const NIF& nif1, const NIF& nif2);
bool operator<(const NIF& nif1, const NIF& nif2);
bool operator>(const NIF& nif1, const NIF& nif2);
bool operator<=(const NIF& nif1, const NIF& nif2);
bool operator>=(const NIF& nif1, const NIF& nif2);
bool operator!=(const NIF& nif1, const NIF& nif2);
