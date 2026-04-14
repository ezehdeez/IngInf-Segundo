/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P5
 * 
 * @file derivated_sort_methods.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-08
 * @brief  Declares and implements concrete sorting strategy classes 
 *         (SelectionSort, BubbleSort, MergeSort, HeapSort, DeltaSort) acting as
 *         object-oriented wrappers.
 */

#pragma once

#include "../include/sorting.h"
#include "../include/sort_method.h"

template <class Key>
class SelectionSort : public SortMethod<Key> {
 public:
  SelectionSort(const staticSequence<Key>& seq, bool trace) 
  : SortMethod<Key>(seq, trace) {}

  void Sort() override;
};

template <class Key>
class BubbleSort : public SortMethod<Key> {
 public:
  BubbleSort(const staticSequence<Key>& seq, bool trace) 
  : SortMethod<Key>(seq, trace) {}

  void Sort() override;
};

template <class Key>
class MergeSort : public SortMethod<Key> {
 public:
  MergeSort(const staticSequence<Key>& seq, bool trace) 
  : SortMethod<Key>(seq, trace) {}

  void Sort() override;
};

template <class Key>
class HeapSort : public SortMethod<Key> {
 public:
  HeapSort(const staticSequence<Key>& seq, bool trace) 
  : SortMethod<Key>(seq, trace) {}

  void Sort() override;
};

template <class Key>
class DeltaSort : public SortMethod<Key> {
 public:
  DeltaSort(const staticSequence<Key>& seq, bool trace) 
  : SortMethod<Key>(seq, trace) {}

  void Sort() override;
};

template <class Key>
class ModiSort : public SortMethod<Key> {
 public:
  ModiSort(const staticSequence<Key>& seq, bool trace)
  : SortMethod<Key>(seq, trace) {}

  void Sort() override;
};

template <class Key>
void SelectionSort<Key>::Sort() {
  if(this->dotrace_) {
    SelectionsortWTrace(this->sequence_, this->sequence_.size());
  } else {
    Selectionsort(this->sequence_, this->sequence_.size());
    this->sequence_.print();
    std::cout << "\n";
  }
}

template <class Key>
void BubbleSort<Key>::Sort() {
  if(this->dotrace_) {
    BubblesortWTrace(this->sequence_, this->sequence_.size());
  } else {
    Bubblesort(this->sequence_, this->sequence_.size());
    this->sequence_.print();
    std::cout << "\n";
  }
}

template <class Key>
void MergeSort<Key>::Sort() {
  if(this->dotrace_) {
    MergesortWTrace(this->sequence_, 0, this->sequence_.size() - 1);
  } else {
    std::cout << "INITIAL VALUES: " << std::endl;
    this->sequence_.print();
    std::cout << "\n\n";
    Mergesort(this->sequence_, 0, this->sequence_.size() - 1);
    this->sequence_.print();
    std::cout << "\n";
  }
}

template <class Key>
void HeapSort<Key>::Sort() {
  if(this->dotrace_) {
    HeapsortWTrace(this->sequence_, this->sequence_.size());
  } else {
    Heapsort(this->sequence_, this->sequence_.size());
    this->sequence_.print();
    std::cout << "\n";
  }
}

template <class Key>
void DeltaSort<Key>::Sort() {
  if(this->dotrace_) {
    DeltasortWTrace(this->sequence_, this->sequence_.size());
  } else {
    Deltasort(this->sequence_, this->sequence_.size());
    this->sequence_.print();
    std::cout << "\n";
  }
}

template <class Key>
void ModiSort<Key>::Sort() {
  size_t n = this->sequence_.size();
  if (n <= 1) return;
  size_t mid = n / 2;
  std::cout << "INITIAL VALUES:\n";
  this->sequence_.print();
  std::cout << "\n";
  // InsertionSort
  for(size_t i = 1; i < mid; i++) {
    Key x = this->sequence_[i];
    size_t j = i;
    while(j > 0 && x < this->sequence_[j - 1]) {
      this->sequence_[j] = this->sequence_[j - 1];
      j--;
    }
    this->sequence_[j] = x;
    this->sequence_.print();
    std::cout << "\n";
  }
  std::cout << "[INFO]: InsertionSort Finished\n";
  // SelectionSort
  for(size_t i = mid; i < n - 1; i++) {
    size_t min = i;
    for (size_t j = i + 1; j < n; j++) {
      if (this->sequence_[j] < this->sequence_[min]) {
        min = j;
      }
    }
    std::swap(this->sequence_[i], this->sequence_[min]);
    this->sequence_.print();
    std::cout << "\n";
  }
  std::cout << "[INFO]: SelectionSort Finished\n";
  this->sequence_.print();
  std::cout << "\n";
  // Merge
  staticSequence<Key> aux(n); 
  size_t i = 0;
  size_t j = mid;
  size_t k = 0;
  while(i < mid && j < n) {
    if(this->sequence_[i] < this->sequence_[j]) {
      aux[k] = this->sequence_[i];
      i++;
    } else {
      aux[k] = this->sequence_[j];
      j++;
    }
    k++;
  }
  while(i < mid) {
    aux[k] = this->sequence_[i];
    i++;
    k++;
  }
  while(j < n) {
    aux[k] = this->sequence_[j];
    j++;
    k++;
  }
  for (size_t idx = 0; idx < n; idx++) {
    this->sequence_[idx] = aux[idx];
  }
  std::cout << "[INFO]: Merge Finished\n";
  this->sequence_.print();
  std::cout << "\n";
}
