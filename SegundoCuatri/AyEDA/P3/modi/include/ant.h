/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P3
 * 
 * @file ant.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-02-09
 * @brief Ant class declaration 
 */

#include <iostream>
#include <memory>
#include <string>

class Tape;

#ifndef ANT_H
#define ANT_H

class Ant {
 public:
  // Constructors
  Ant() : orientation_{0}, life_time_{0}, x_{0}, y_{0} {}
  virtual ~Ant() = default;
  Ant(int orientation, int life_time, int x, int y) : orientation_{orientation}, life_time_{life_time}, x_{x}, y_{y} {}
  Ant(char orientation, int life_time, int x, int y);

  // Movement related methods
  void TurnRight();
  void TurnLeft();
  void Move(); 
  virtual void Step(Tape*) = 0;

  // Getters
  virtual std::string GetType() const = 0;
  virtual char GetAlimentation() const = 0;
  int GetOrientation() const {return orientation_;}
  int GetLifeTime() const {return life_time_;}
  int GetX() const {return x_;}
  int GetY() const {return y_;}

  //Setters
  void SetX(int x) {x_ = x;}
  void SetY(int y) {y_ = y;}
  void SetOrientation(int ori) {orientation_ = ori;}

  void SumToLifeTime(int);

 private:
  int orientation_;
  int life_time_;
  int x_;
  int y_;
};

std::ostream& operator<<(std::ostream& out, const Ant& ant);

#endif