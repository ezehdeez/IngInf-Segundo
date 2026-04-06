/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P3
 * 
 * @file nif.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
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

  static void ResetCounter() {comparation_counter_ = 0;}
  static void AddToCounter() {comparation_counter_++;}
  static unsigned GetCounter() {return comparation_counter_;}
 private:
  long value_;
  static unsigned comparation_counter_;
};

bool operator==(const NIF& nif1, const NIF& nif2);
bool operator<(const NIF& nif1, const NIF& nif2);
