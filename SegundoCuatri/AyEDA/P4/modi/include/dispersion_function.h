/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 *  
 * @subject: AyEDA - P3
 *  
 * @file dispersion_function.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief Generic abstract base class for dispersion (hashing) functions,
 * responsible for calculating the initial position of a key.
 */

#pragma once

template <class Key>
class DispersionFunction {
 public:
  virtual ~DispersionFunction() = default;
  virtual unsigned operator()(const Key&) const = 0;
};