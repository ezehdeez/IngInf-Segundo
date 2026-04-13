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