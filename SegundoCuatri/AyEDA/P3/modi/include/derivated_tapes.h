/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P3
 * 
 * @file derivated_tapes.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-09
 * @brief Derivated tapes classes declarations, inheritance from Tape class
 */

#include "../include/sliding_vector.h"
#include "../include/tape.h"

#ifndef TAPE_PERIODIC_H
#define TAPE_PERIODIC_H

class TapePeriodic : public Tape {
 public:
  TapePeriodic(int x_size, int y_size) : Tape(x_size, y_size), grid_{} {
    std::cout << "entro constructor tape" << std::endl;
    grid_.resize(x_size);
    for(int i = 0; i < x_size; i++) {
      grid_[i].resize(y_size);
      for(int j = 0; j < y_size; j++) {
        grid_[i][j] = Color::WHITE_CELL;
      }
    }
  }
  void PrintCell(const int x, const int y);
  void CheckMove(Ant*) override;

  void DrawCell(int x, int y, const Color& color) override {grid_[x][y] = color;}
  Color GetCell(const int row, const int column) const override {return grid_[row][column];}
  char GetType() const override { return 'P'; }
 private:
  std::vector<std::vector<Color>> grid_;
};

#endif

#ifndef TAPE_REFLECTIVE_H
#define TAPE_REFLECTIVE_H

class TapeReflective : public Tape {
 public:
  TapeReflective(int x_size, int y_size) : Tape(x_size, y_size), grid_{} {
    std::cout << "entro constructor tape" << std::endl;
    grid_.resize(x_size);
    for(int i = 0; i < x_size; i++) {
      grid_[i].resize(y_size);
      for(int j = 0; j < y_size; j++) {
        grid_[i][j] = Color::WHITE_CELL;
      }
    }
  }
  void PrintCell(const int x, const int y);
  void CheckMove(Ant*) override;

  void DrawCell(int x, int y, const Color& color) override {grid_[x][y] = color;}
  Color GetCell(const int row, const int column) const override {return grid_[row][column];}
  char GetType() const override { return 'R'; }
 private:
  std::vector<std::vector<Color>> grid_;
};

#endif

#ifndef TAPE_SLIDING_H
#define TAPE_SLIDING_H

class TapeSliding : public Tape {
 public:
  TapeSliding(int x_size, int y_size) : Tape(x_size, y_size), grid_(0, x_size - 1) {
    std::cout << "entro constructor tape" << std::endl;
    grid_.Resize(x_size);
    for(int i = 0; i < x_size; i++) {
      grid_[i] = SlidingVector<Color>(0, y_size - 1);
      for(int j = 0; j < y_size; j++) {
        grid_[i][j] = Color::WHITE_CELL;
      }
    }
  }
  void PrintCell(const int x, const int y);
  void FillVectorAsDefalult(SlidingVector<Color>&);
  Color GetCell(int x, int y) const override;
  void DrawCell(int x, int y, const Color& color) override;
  void CheckMove(Ant* ant) override {}
  char GetType() const override { return 'S'; }

  int GetMinX() const override { return grid_.GetMinValue(); }
  int GetMaxX() const override { return grid_.GetMaxValue(); }
  int GetMinY() const override { return grid_[grid_.GetMinValue()].GetMinValue(); }
  int GetMaxY() const override { return grid_[grid_.GetMinValue()].GetMaxValue(); }
 private:
  SlidingVector<SlidingVector<Color>> grid_;
};

#endif