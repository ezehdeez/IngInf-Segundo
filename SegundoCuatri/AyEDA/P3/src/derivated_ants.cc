/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: AyEDA - P3
 * 
 * @file derivated_ants.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-03-09
 * @brief 
 */

#include "../include/derivated_ants.h"

/**
 * @brief Performs the diagonal movement exclusive to carnivore ants.
 * @param direction Direction of the diagonal ('L' for left, 'R' for right) 
 *                  relative to the ant's current orientation.
 */
void Ant_C::DiagonalMove(char direction) {
  if(direction == 'L') {
    switch(GetOrientation()) {
      case 0:
        SetY(GetY() - 1);
        SetX(GetX() + 1);
        break;
      case 1:
        SetY(GetY() + 1);
        SetX(GetX() - 1);
        break;
      case 2:
        SetY(GetY() - 1);
        SetX(GetX() - 1);
        break;
      case 3:
        SetY(GetY() + 1);
        SetX(GetX() + 1);
        break;
  }
  } else if(direction == 'R') {
    switch(GetOrientation()) {
      case 0:
        SetY(GetY() - 1);
        SetX(GetX() - 1);
        break;
      case 1:
        SetY(GetY() + 1);
        SetX(GetX() + 1);
        break;
      case 2:
        SetX(GetX() - 1);
        SetY(GetY() + 1);
        break;
      case 3:
        SetY(GetY() - 1);
        SetX(GetX() + 1);
        break;
    }
  }
}

/**
 * @brief Executes the turn of a Herbivore ant (Rule: DDII).
 * The ant reads the color, absorbs its nutritional value, turns, 
 * paints the current cell, and moves to the next cell.
 * @param cinta Pointer to the tape where the ant is located.
 */
void Ant_H_DDII::Step(Tape* cinta) {
  int nutrition = static_cast<int>(cinta->GetCell(GetX(), GetY()));
  SumToLifeTime(nutrition);

  if(cinta->GetCell(GetX(), GetY()) == static_cast<Color>(0) || 
     cinta->GetCell(GetX(), GetY()) == static_cast<Color>(1)) {
      TurnRight();
    } else {
      TurnLeft();
    }
    cinta->DrawCell(GetX(), GetY(), static_cast<Color>((static_cast<int>(cinta->GetCell(GetX(), GetY())) + 1) % 4));
    Move();
}

/**
 * @brief Executes the turn of a Carnivore ant (Rule: IDID).
 * The ant reads the color, turns, paints the current cell, 
 * and performs a diagonal jump based on its turn direction.
 * @param cinta Pointer to the tape where the ant is located.
 */
void Ant_C_IDID::Step(Tape* cinta) {
  bool right_turn = false;
  if(cinta->GetCell(GetX(), GetY()) == static_cast<Color>(1) || 
    cinta->GetCell(GetX(), GetY()) == static_cast<Color>(3)) {
    TurnRight();
    right_turn = true;
  } else {
    TurnLeft();
  }
  cinta->DrawCell(GetX(), GetY(), static_cast<Color>((static_cast<int>(cinta->GetCell(GetX(), GetY())) + 1) % 4));
  if(right_turn) {
    DiagonalMove('R');
  } else {
    DiagonalMove('L');
  }
}