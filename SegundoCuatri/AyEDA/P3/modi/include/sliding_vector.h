/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P3
 * 
 * @file sliding_vector.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-09
 * @brief Implementation of a dynamic vector with configurable indices (possibly negative).
 * 
 *        This file contains the definition of the SlidingVector class, a template container that
 *        allows accessing elements using an arbitrary index range (min_value to max_value),
 *        unlike std::vector which only allows indices from 0. It also includes the SVException class
 *        for handling out-of-bounds accesses.
 * 
 *      Main features:
 *        - Support for negative indices and custom ranges
 *        - Overloaded [] operator for direct access with bounds validation
 *        - PushBack() and PushFront() methods for dynamic range expansion
 *        - Custom exception handling with SVException
 *        - Template implementation to support any data type
 * 
 */

#include <iostream>
#include <vector>

#ifndef SVEXCEPTION_H
#define SVEXCEPTION_H

/**
 * @class SVException
 * @brief Custom exception to handle out-of-bounds access in the SlidingVector.
 * It stores the invalid index that was accessed, as well as the current boundaries.
 */
class SVException : public std::exception {
 public:
  SVException(int invalid, int min, int max) : invalid_{invalid}, min_{min}, max_{max} {
    msg_ = "SVException: Out of bounds access";
  }

  int invalid() const {return invalid_;}
  int min() const {return min_;}
  int max() const {return max_;}
  const char* msg() {return msg_;}
 private:
  int invalid_;
  int min_;
  int max_;
  const char* msg_;
};

#endif

#ifndef SLIDING_VECTOR_H
#define SLIDING_VECTOR_H

/**
 * @class SlidingVector
 * @brief Template class for a dynamic vector with configurable boundaries.
 *        Unlike the standard std::vector, this vector allows negative or arbitrary indices.
 *        It throws an SVException if accessed out of bounds.
 * @tparam T The data type to be stored in the vector.
 */
template <typename T>
class SlidingVector {
  public:
  SlidingVector() = default;
  SlidingVector(int min_value, int max_value) : min_value_{min_value}, max_value_{max_value}, vector_{std::vector<T>(max_value - min_value + 1)} {}

  T& operator[](int index);
  const T& operator[](int index) const;
  
  // Element adding
  void PushBack(const T&);
  void PushFront(const T&);

  // Getters
  int GetMinValue() const {return min_value_;}
  int GetMaxValue() const {return max_value_;}
  size_t GetSize() const {return vector_.size();}

  void Resize(size_t size) {vector_.resize(size);} 
 private:
  int min_value_;
  int max_value_;
  std::vector<T> vector_;
};

#endif

/**
 * @brief Overload of the access operator [].
 * @param index Logical index to access.
 * @return T& Reference to the stored element.
 * @throw SVException If the index is out of the [min_value_, max_value_] range.
 */
template <typename T>
T& SlidingVector<T>::operator[](int index) {
  if(index > max_value_ || index < min_value_) {
    throw SVException(index, min_value_, max_value_);
  }
  return vector_[index - min_value_];
}

template <typename T>
const T& SlidingVector<T>::operator[](int index) const {
  if(index > max_value_ || index < min_value_) {
    throw SVException(index, min_value_, max_value_);
  }
  return vector_[index - min_value_];
}

/**
 * @brief Inserts an element at the back of the vector (expansion to the right/bottom).
 * @param element Element to be inserted.
 */
template <typename T>
void SlidingVector<T>::PushBack(const T& element) {
  vector_.push_back(element);
  max_value_++;
}

/**
 * @brief Inserts an element at the front of the vector (expansion to the left/top).
 * @param element Element to be inserted.
 */
template <typename T>
void SlidingVector<T>::PushFront(const T& element) {
  vector_.insert(vector_.begin(), element);
  min_value_--;
}