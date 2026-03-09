#include "../include/derivated_ants.h"

void Ant_DDII::Step(Tape& cinta) {
  if(cinta.GetCell(GetX(), GetY()) == static_cast<Color>(0) || 
     cinta.GetCell(GetX(), GetY()) == static_cast<Color>(1)) {
      TurnRight();
    } else {
      TurnLeft();
    }
    cinta.DrawCell(GetX(), GetY(), static_cast<Color>((static_cast<int>(cinta.GetCell(GetX(), GetY())) + 3) % 4));
    Move(cinta);
}

void Ant_IDID::Step(Tape& cinta) {
  if(cinta.GetCell(GetX(), GetY()) == static_cast<Color>(1) || 
     cinta.GetCell(GetX(), GetY()) == static_cast<Color>(3)) {
      TurnRight();
    } else {
      TurnLeft();
    }
    cinta.DrawCell(GetX(), GetY(), static_cast<Color>((static_cast<int>(cinta.GetCell(GetX(), GetY())) + 1) % 4));
    Move(cinta);
}