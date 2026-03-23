/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P3
 * 
 * @file sequence.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief Generic abstract base class that defines the common interface
 * (insertion and search) for all types of data sequences.
 */

#pragma once

template <class Key>
class Sequence {
 public:
  virtual ~Sequence() = default;

  virtual bool search(const Key& k) const = 0;
  virtual bool insert(const Key& k) = 0;

  virtual bool isFull() const = 0;
  virtual void print() const = 0;
};