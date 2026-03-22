/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: 
 * 
 * @file nif.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief 
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
