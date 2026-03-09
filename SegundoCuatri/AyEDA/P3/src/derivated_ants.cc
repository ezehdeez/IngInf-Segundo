#include "../include/derivated_ants.h"

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