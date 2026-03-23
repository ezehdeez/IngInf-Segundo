/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 *  
 * @subject: AyEDA - P3
 *  
 * @file hash_table.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-22
 * @brief Implementation of the generic Hash Table data structure,
 * utilizing partial template specialization for open/closed hashing.
 */

#pragma once

#include "../include/dispersion_function.h"
#include "../include/dynamic_sequence.h"
#include "../include/exploration_function.h"
#include "../include/sequence.h"
#include "../include/static_sequence.h"

template<class Key, class Container = staticSequence<Key>>
class HashTable : public Sequence<Key> {
 public:
  HashTable(unsigned table_size, DispersionFunction<Key>& fd, ExplorationFunction<Key>& fe, unsigned block_size) 
  : table_size_{table_size}, table_{nullptr}, fd_{&fd}, fe_{&fe}, block_size_{block_size} {
    table_ = new Container*[table_size_];
    for(unsigned i = 0; i < table_size_; i++) {
      table_[i] = new Container(block_size_);
    }
  }

  ~HashTable() {
    for (unsigned i = 0; i < table_size_; i++) {
      delete table_[i]; 
    }
    delete[] table_; 
    delete fd_;
    delete fe_;
  }

  // Evitar copias para quitar warnings a la hora de compilar
  HashTable(const HashTable&) = delete;
  HashTable& operator=(const HashTable&) = delete;

  bool search(const Key& k) const override {
    unsigned initial_index = (*fd_)(k);
    for(size_t i = 0; i < table_size_; i++) {
      if(table_[initial_index]->search(k)) return true;
      if(!table_[initial_index]->isFull()) return false;
      initial_index = (*fd_)(k) + (*fe_)(k, i);
    }
    return false;
  }

  bool insert(const Key& k) override {
    unsigned initial_index = (*fd_)(k);
    for(size_t i = 0; i < table_size_; i++) {
      if(table_[initial_index]->search(k)) return false;
      if(!table_[initial_index]->isFull()) {
        table_[initial_index]->insert(k);
        return true;
      } else {
        initial_index = (*fd_)(k) + (*fe_)(k, i);
      }
    }
    return false;
  }

  bool isFull() const override {return false;};
  void print() const override {
    for(unsigned i = 0; i < table_size_; i++) {
      std::cout << "Celda [" << i << "]: ";
      table_[i]->print();
      std::cout << "\n";
    }
  }

 private:
  unsigned table_size_;
  Container** table_;
  DispersionFunction<Key>* fd_;
  ExplorationFunction<Key>* fe_;
  unsigned block_size_;
};

template<class Key>
class HashTable<Key, dynamicSequence<Key>> : public Sequence<Key> {
 public:
  HashTable(unsigned table_size, DispersionFunction<Key>& fd) : table_size_{table_size}, table_{nullptr}, fd_{&fd} {
    table_ = new dynamicSequence<Key>*[table_size_];
    for (unsigned i = 0; i < table_size_; i++) {
      table_[i] = new dynamicSequence<Key>(); 
    }
  }

  ~HashTable() {
    for (unsigned i = 0; i < table_size_; i++) {
      delete table_[i];
    }
    delete fd_;
  }

  // Evitar copias para quitar warnings a la hora de compilar
  HashTable(const HashTable&) = delete;
  HashTable& operator=(const HashTable&) = delete;

  bool search(const Key& k) const override {
    unsigned index = (*fd_)(k);
    return table_[index]->search(k);
  }

  bool insert(const Key& k) override {
    unsigned index = (*fd_)(k);
    return table_[index]->insert(k);
  }

  bool isFull() const override {return false;};
  void print() const override {
    for (unsigned i = 0; i < table_size_; i++) {
      std::cout << "Celda [" << i << "]: ";
      table_[i]->print();
      std::cout << "\n";
    }
  }

 private:
  unsigned table_size_;
  dynamicSequence<Key>** table_;
  DispersionFunction<Key>* fd_;
};