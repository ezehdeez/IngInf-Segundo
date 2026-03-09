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

#include "../include/ant.h"
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
  Tape(int x_size, int y_size) : x_size_{x_size}, y_size_{y_size} {}

  virtual ~Tape() = default;
  
  virtual void DrawCell(int x, int y, const Color& color) = 0;

  // Getters
  virtual char GetType() const = 0;
  virtual Color GetCell(const int row, const int column) const = 0;
  int GetXSize() const {return x_size_;}
  int GetYSize() const {return y_size_;}
  std::string ColorToCode(const Color &color);

  // En tape.h
  virtual int GetMinX() const { return 0; }
  virtual int GetMaxX() const { return x_size_ - 1; }
  virtual int GetMinY() const { return 0; }
  virtual int GetMaxY() const { return y_size_ - 1; }

  // Setters
  void SetXSize(int x_size) {x_size_ = x_size;}
  void SetYSize(int y_size) {y_size_ = y_size;}

  // Print methods
  virtual void PrintCell(const int x, const int y) = 0;

  // Border
  virtual void CheckMove(Ant*) = 0;

 private:
  int x_size_;
  int y_size_;
  // std::vector<std::vector<Color>> grid_;
};

std::ostream& operator<<(std::ostream& out, const Tape& tape_to_print);

#endif