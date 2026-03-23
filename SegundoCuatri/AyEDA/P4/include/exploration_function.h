/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 *  
 * @subject: AyEDA - P3
 *  
 * @file exploration_function.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief Generic abstract base class for exploration (probing) functions,
 * responsible for calculating the jump size when a collision occurs.
 */

#pragma once

template <class Key>
class ExplorationFunction {
 public:
  virtual ~ExplorationFunction() = default;
  virtual unsigned operator()(const Key&, unsigned) const=0;
 private:
};