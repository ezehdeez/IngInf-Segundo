/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P1
 * 
 * @file ant.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-02-09
 * @brief Ant class declaration
 */

#include <iostream>
#include <string>

class Tape;

#ifndef ANT_H
#define ANT_H

class Ant {
 public:
  // Constructors
  Ant() : orientation_{0}, x_{0}, y_{0} {}
  virtual ~Ant() = default;
  Ant(int orientation, int x, int y) : orientation_{orientation}, x_{x}, y_{y} {}
  Ant(char orientation, int x, int y);

  // Movement related methods
  void TurnRight();
  void TurnLeft();
  void Move(const Tape& cinta);
  virtual void Step(Tape& cinta) = 0;

  // Getters
  virtual std::string GetType() const = 0;
  int GetOrientation() const {return orientation_;}
  int GetX() const {return x_;}
  int GetY() const {return y_;}

 private:
  int orientation_;
  int x_;
  int y_;
};

std::ostream& operator<<(std::ostream& out, const Ant& ant);

#endif