#include "../include/colors.h"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

class Ant;

#ifndef TAPE_H
#define TAPE_H

class Tape {
 public:
  Tape() = default;
  Tape(size_t x_size, size_t y_size) : x_size_{x_size}, y_size_{y_size}, grid_{} {
    grid_.resize(x_size_);
    for(int i = 0; i < x_size; i++) {
      grid_[i].resize(y_size_);
      for(int j = 0; j < y_size_; j++) {
        grid_[i][j] = 0;
      }
    }
  }

  bool GetCell(const size_t row, const size_t column) const {return grid_[row][column] != 0;}

  void DrawCell(const size_t row, const size_t column) {grid_[row][column] = 1;}

  void ResetCell(const size_t row, const size_t column) {grid_[row][column] = 0;}

  size_t GetXSize() const {return x_size_;}
  size_t GetYSize() const {return y_size_;}

  void PrintUntilAnt(Ant*);
  void PrintPostAnt(Ant*);

 private:
  size_t x_size_;
  size_t y_size_;
  std::vector<std::vector<uint8_t>> grid_;

};

std::ostream& operator<<(std::ostream& out, const Tape& tape_to_print);

#endif