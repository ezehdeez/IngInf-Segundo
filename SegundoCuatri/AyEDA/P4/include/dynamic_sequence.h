/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: 
 * 
 * @file dynamic_sequence.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief 
 */

#pragma once

#include <iostream>
#include <vector>

template<class Key> 
class dynamicSequence: public Sequence<Key> {
 public:
  dynamicSequence() = default;
  ~dynamicSequence() override = default;

  bool search(const Key& k) const override;
  bool insert(const Key& k) override;

  bool isFull() const override {return false;}
  void print() const override;
 private:
  std::vector<Key> data_;
};

template <class Key>
bool dynamicSequence<Key>::search(const Key& k) const {
  for(size_t i = 0; i < data_.size(); i++) {
    if(data_[i] == k) {
      return true;
    }
  }
  return false;
}

template <class Key>
bool dynamicSequence<Key>::insert(const Key& k) {
  if(search(k)) {
    return false;
  }
  data_.push_back(k);
  return true;
}

/**
 * @brief Method used for depuration
 * 
 * @tparam Key 
 */
template <class Key>
void dynamicSequence<Key>::print() const {
  for (const auto& key : data_) {
    std::cout << (long)key << " -> "; 
  }
  std::cout << "NULL";
}