/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: 
 * 
 * @file sequence.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief 
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