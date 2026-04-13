/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P5
 * 
 * @file sort_method.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-07
 * @brief Generic abstract base class defining the Strategy Pattern interface for
 *        sorting algorithms. Manages the target sequence and the trace 
 *        execution flag.
 */

#pragma once

#include "../include/static_sequence.h"

template <class Key>
class SortMethod {
  public:
   SortMethod(const staticSequence<Key>& seq, bool trace) 
   : sequence_{seq}, dotrace_{trace} {}

   virtual ~SortMethod() = default;

   virtual void Sort() = 0;
   protected:
    staticSequence<Key> sequence_;
    bool dotrace_;
};