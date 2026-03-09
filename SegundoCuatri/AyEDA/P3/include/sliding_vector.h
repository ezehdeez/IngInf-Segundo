#include <iostream>
#include <vector>

#ifndef SVEXCEPTION_H
#define SVEXCEPTION_H

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

template <typename T>
void SlidingVector<T>::PushBack(const T& element) {
  vector_.push_back(element);
  max_value_++;
}

template <typename T>
void SlidingVector<T>::PushFront(const T& element) {
  vector_.insert(vector_.begin(), element);
  min_value_--;
}