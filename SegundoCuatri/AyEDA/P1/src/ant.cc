#include "../include/ant.h"
#include "../include/tape.h"

#include <cassert>

void Ant::TurnRight() {
  orientation_ = (orientation_ + 2) % 4;
}

void Ant::TurnLeft() {
  orientation_ = (orientation_ + 3) % 4;
}

void Ant::Move(const Tape& cinta) {
  switch(orientation_) {
    case 0:
    y_--;
    break;
    case 1:
    y_++;
    break;
    case 2:
    x_++;
    break;
    case 3:
    x_--;
    break;
  }
  assert(x_ < cinta.GetXSize() && y_ < cinta.GetYSize());
}

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
std::ostream& operator<<(std::ostream& out, const Ant& ant) {
  char c;
  switch(ant.GetOrientation()) {
    case 0:
      c = '>';
      break;
    case 1:
      c = '<';
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