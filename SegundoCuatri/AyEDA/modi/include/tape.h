/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P1
 * 
 * @file tape.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-02-09
 * @brief Tape class declaration, each object has its dimensions and the grid.
 */

#include "../include/colors.h"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

class Ant;

#ifndef COLORS_ENUM
#define COLORS_ENUM

enum class Color {
  WHITE_CELL = 0,
  GREEN_CELL = 1,
  RED_CELL = 2,
  BLUE_CELL = 3,
  MAGENTA_CELL = 4,
  CYAN_CELL = 5,
  ORANGE_CELL = 6,
  ROSE_CELL = 7,
  LBLUE_CELL = 8,
  LGREEN_CELL = 9,
  GRAY_CELL = 10,
  YELLOW_CELL = 11,
  BLACK_CELL = 12,
};

#endif

#ifndef TAPE_H
#define TAPE_H

class Tape {
 public:
  // Constructors
  Tape() : x_size_{0}, y_size_{0}, grid_{} {}
  Tape(size_t x_size, size_t y_size) : x_size_{x_size}, y_size_{y_size}, grid_{} {
    std::cout << "entro constructor tape" << std::endl;
    grid_.resize(x_size_);
    for(size_t i = 0; i < x_size_; i++) {
      grid_[i].resize(y_size_);
      for(size_t j = 0; j < y_size_; j++) {
        grid_[i][j] = Color::WHITE_CELL;
      }
    }
  }
  
  void ResetCell(size_t x, size_t y) {grid_[x][y] = Color::WHITE_CELL;}
  void DrawCell(size_t x, size_t y) {grid_[x][y] = Color::BLACK_CELL;}
  void DrawCell(size_t x, size_t y, const Color& color) {grid_[x][y] = color;}

  // Getters
  Color GetCell(const size_t row, const size_t column) const {return grid_[row][column];}
  size_t GetXSize() const {return x_size_;}
  size_t GetYSize() const {return y_size_;}
  std::string ColorToCode(const Color &color);

  // Print methods
  void PrintCell(const size_t x, const size_t y);

 private:
  size_t x_size_;
  size_t y_size_;
  std::vector<std::vector<Color>> grid_;

};

std::ostream& operator<<(std::ostream& out, const Tape& tape_to_print);

#endif