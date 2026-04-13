/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P5
 * 
 * @file sorting.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-04-07
 * @brief sorting library. Contains Selectionsort, Bubblesort, Mergesort, 
 *        Heapsort and Deltasort.
 */

#pragma once

#include "../include/static_sequence.h"

#include <utility>

template <class Key>
void Selectionsort(staticSequence<Key>& sec, size_t size) {
  std::cout << "INITIAL VALUES: " << std::endl;
  sec.print();
  std::cout << "\n\n";
  for(size_t i = 0; i < size - 1; i++){
    int min = i;
    for(size_t j = i + 1; j < size; j++) {
      if(sec[j] < sec[min]) {
        min = j;
      }
    }
    Key x = sec[min];
    sec[min] = sec[i];
    sec[i] = x;
  }
}

template <class Key>
void SelectionsortWTrace(staticSequence<Key>& sec, size_t size) {
  std::cout << "INITIAL VALUES: " << std::endl;
  sec.print();
  std::cout << "\n\n";
  for(size_t i = 0; i < size - 1; i++){
    int min = i;
    for(size_t j = i + 1; j < size; j++) {
      if(sec[j] < sec[min]) {
        min = j;
      }
    }
    Key x = sec[min];
    sec[min] = sec[i];
    sec[i] = x;
    std::cout << "Iteration " << i << ":" << std::endl;
    sec.print();
    std::cout << "\n";
  }
}

template <class Key>
void Bubblesort(staticSequence<Key>& sec, size_t size) {
  std::cout << "INITIAL VALUES: " << std::endl;
  sec.print();
  std::cout << "\n\n";
  for(size_t i = 1; i < size; i++){
    for(size_t j = size-1; j >= i; j--) {
      if(sec[j] < sec[j-1]) {
        std::swap(sec[j-1], sec[j]);
      }
    }
  }
}

template <class Key>
void BubblesortWTrace(staticSequence<Key>& sec, size_t size) {
  std::cout << "INITIAL VALUES: " << std::endl;
  sec.print();
  std::cout << "\n\n";
  for(size_t i = 1; i < size; i++){
    for(size_t j = size - 1; j >= i; j--) {
      if(sec[j] < sec[j-1]) {
        std::swap(sec[j-1], sec[j]);
      }
    }
    std::cout << "Iteration " << i << ":" << std::endl;
    sec.print();
    std::cout << "\n";
  }
}

template <class Key>
void Merge(staticSequence<Key>& sec, size_t ini, size_t cen, size_t fin) {
  staticSequence<Key> aux(fin + 1);
  size_t i = ini; 
  size_t j = cen + 1;
  size_t k = ini;
  while((i <= cen) && (j <= fin)) {
    if(sec[i] < sec[j]) {
      aux[k] = sec[i] ;
      i++;
    } else {
      aux[k] = sec[j] ;
      j++ ;
    }
    k++ ;
  }
  if(i > cen) {
    while(j <= fin) {
      aux[k] = sec[j];
      j++;
      k++;
    }
  } else {
    while(i <= cen) {
      aux[k] = sec[i];
      i++;
      k++;
    }
  }
  for(size_t k = ini; k <= fin; k++) {
    sec[k] = aux[k];
  }
}

template <class Key>
void Mergesort(staticSequence<Key>& sec, size_t ini, size_t fin) {
  if(ini < fin) {
    size_t cen = (ini + fin) / 2;
    Mergesort(sec, ini, cen);
    Mergesort(sec, cen+1, fin);
    Merge(sec, ini, cen, fin);
  }
}

template <class Key>
void MergesortWT_recursive(staticSequence<Key>& sec, size_t ini, size_t fin) {
  if(ini < fin) {
    size_t cen = (ini + fin) / 2;
    MergesortWT_recursive(sec, ini, cen);
    MergesortWT_recursive(sec, cen+1, fin);
    Merge(sec, ini, cen, fin);
    // std::cout << "Merged [" << ini << ".." << cen << "] and [" << cen+1 << ".." << fin << "]:" << std::endl;
    sec.print();
    std::cout << "\n";
  }
}

template <class Key>
void MergesortWTrace(staticSequence<Key>& sec, size_t ini, size_t fin) {
  std::cout << "INITIAL VALUES: " << std::endl;
  sec.print();
  std::cout << "\n\n";
  MergesortWT_recursive(sec, ini, fin);
}

template <class Key>
void baja(int i, staticSequence<Key> &sec, int n) {
  int h1, h2, h;
  while(2 * i + 1 < n ) {
    h1 = 2 * i + 1;
    h2 = 2 * i + 2;
    if(h2 < n && sec[h2] > sec[h1]){
      h = h2;
    } else {
      h = h1;
    }
    if(sec[h] <= sec[i]){
      break ;
    } else {
      std::swap(sec[i], sec[h]);
      i = h;
    }
  }
}

template <class Key>
void Heapsort(staticSequence<Key>& sec, size_t size) {
  std::cout << "INITIAL VALUES: " << std::endl;
  sec.print();
  std::cout << "\n\n";
  int n = static_cast<int>(size);
  for (int i = n / 2 - 1; i >= 0; i--) {
    baja(i, sec, n);
  }
  for (int i = n - 1; i > 0; i--) {
    std::swap(sec[0],sec[i]);
    baja(0, sec, i);
  }
}

template <class Key>
void HeapsortWTrace(staticSequence<Key>& sec, size_t size) {
  std::cout << "INITIAL VALUES: " << std::endl;
  sec.print();
  std::cout << "\n\n";
  int n = static_cast<int>(size);
  for (int i = n / 2 - 1; i >= 0; i--) {
    baja(i, sec, n);
  }
  int iteration = 0;
  for (int i = n - 1; i > 0; i--) {
    std::swap(sec[0],sec[i]);
    baja(0, sec, i);
    std::cout << "Iteration " << iteration++ << ":" << std::endl;
    sec.print();
    std::cout << "\n";
  }
}

template <class Key>
void deltasort(int delta, staticSequence<Key>& sec, int n) {
  Key x;
  int j;
  for(int i = delta; i < n; i++) {
      x = sec[i];
      j = i;
    while((j >= delta) && (x < sec[j - delta])) {
      sec[j] = sec[j - delta];
      j = j - delta;
    }
    sec[j] = x;
  }
}

template <class Key>
void Deltasort(staticSequence<Key>& sec, size_t size) {
  std::cout << "INITIAL VALUES: " << std::endl;
  sec.print();
  std::cout << "\n\n";
  double alpha = 0.5;
  std::cout << "Introduce the wanted alpha value (default is 0.5): " << std::endl;
  std::cin >> alpha;
  int delta = size * alpha;
  while(delta > 0) {
    deltasort(delta, sec, size);
    delta = delta * alpha;
  }
}

template <class Key>
void DeltasortWTrace(staticSequence<Key>& sec, size_t size) {
  std::cout << "INITIAL VALUES: " << std::endl;
  sec.print();
  std::cout << "\n\n";
  double alpha = 0.5;
  std::cout << "Introduce the wanted alpha value (default is 0.5): " << std::endl;
  std::cin >> alpha;
  std::cout << "\n";
  int delta = size * alpha;
  int iteration = 0;
  while(delta > 0) {
    deltasort(delta, sec, size);
    std::cout << "Iteration " << iteration++ << " (Delta = " << delta << "):" << std::endl;
    sec.print();
    std::cout << "\n";
    delta = delta * alpha;
  }
}