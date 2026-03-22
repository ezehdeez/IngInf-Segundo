/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: 
 * 
 * @file static_sequence.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief 
 */

#pragma once

#include <iostream>
#include <vector>

template<class Key>
class staticSequence : public Sequence<Key> {
 public:
  staticSequence() = default;
  staticSequence(unsigned);
  ~staticSequence() override = default;

  bool search(const Key& k) const override;
  bool insert(const Key& k) override;

  bool isFull() const override {return false;}
  void print() const override;
 private:
  unsigned block_size_;
  std::vector<Key> data_;
};

template <class Key>
staticSequence<Key>::staticSequence(unsigned block_size) : block_size_{block_size} {
  data_.reserve(block_size_);
}

template <class Key>
bool staticSequence<Key>::search(const Key& k) const {
  for(size_t i = 0; i < data_.size(); i++) {
    if(data_[i] == k) {
      return true;
    }
  }
  return false;
}

template <class Key>
bool staticSequence<Key>::insert(const Key& k) {
  if(isFull()) {
    return false; 
  }
  if(search(k)) {
    return false; 
  }
  data_.push_back(k);
  return true;
}

template <class Key>
void staticSequence<Key>::print() const {
  for (size_t i = 0; i < data_.size(); i++) {
    std::cout << "[" << (long)data_[i] << "] ";
  }
  for (size_t i = data_.size(); i < block_size_; i++) {
    std::cout << "[   ] ";
  }
}