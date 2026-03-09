/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P1
 * 
 * @file ant.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-02-09
 * @brief Ant class inicialitazion
 */

#include "../include/ant.h"
#include "../include/tape.h"

#include <cassert>

Ant::Ant(char orientation, int life_time, int x, int y) : orientation_{}, life_time_{life_time}, x_{x}, y_{y} {
  switch(orientation) {
    case '<':
      orientation_ = 0;
      break;
    case '>':
      orientation_ = 1;
      break;
    case '^':
      orientation_ = 2;
      break;
    case 'v':
      orientation_ = 3;
      break;
  }
}

/**
 * @brief Ant turns right by changing its direction, we are using a premade array
 *        to let the code knows where to look when turning right
 */
void Ant::TurnRight() {
  static const int rightOf[4] = {2, 3, 1, 0}; // L->U, R->D, U->R, D->L
  orientation_ = rightOf[orientation_];
}

/**
 * @brief Ant turns left by changing its direction, we are using a premade array
 *        to let the code knows where to look when turning left
 */
void Ant::TurnLeft() {
  static const int leftOf[4]  = {3, 2, 0, 1}; // L->D, R->U, U->L, D->R
  orientation_ = leftOf[orientation_];
} 

/**
 * @brief The ant moves itself in a given tape by increasing or decreasing the x
 *        or y coordinate
 * 
 * @param cinta 
 */
void Ant::Move() {
  switch(orientation_) {
    case 0:
    y_--;
    break;
    case 1:
    y_++;
    break;
    case 2:
    x_--;
    break;
    case 3:
    x_++;
    break;
  }
}

void Ant::SumToLifeTime(int number) {
  life_time_ += number;
}

/**
 * @brief << operator overloading
 * 
 * @param out 
 * @param ant 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& out, const Ant& ant) {
  char c;
  switch(ant.GetOrientation()) {
    case 0:
      c = '<';
      break;
    case 1:
      c = '>';
      break;
    case 2:
      c = '^';
      break;
    case 3:
      c = 'v';
      break;
  }
  out << c;
  return out;
}