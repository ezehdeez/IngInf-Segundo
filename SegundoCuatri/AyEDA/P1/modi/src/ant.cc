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
void Ant::Move(const Tape& cinta) {
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
  assert(static_cast<size_t>(x_) < cinta.GetXSize() && static_cast<size_t>(y_) < cinta.GetYSize());
}

/**
 * @brief As we have a method to move, we know need to know how we move, so here
 *        we have the step method. It follows the Langton's Ant instrucions.
 * 
 * @param cinta 
 */
void Ant::Step(Tape& cinta) {
  if(cinta.GetCell(x_, y_)) {
    // CELDA NEGRA
    cinta.ResetCell(x_, y_);
    TurnRight();
    Move(cinta);
  } else {
    // CELDA BLANCA
    cinta.DrawCell(x_, y_);
    TurnLeft();
    Move(cinta);
  }
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