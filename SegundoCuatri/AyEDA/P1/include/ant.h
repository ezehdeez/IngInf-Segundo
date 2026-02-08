#include <iostream>

class Tape;

#ifndef ANT_H
#define ANT_H

class Ant {
 public:
  Ant(int orientation, int x, int y) : orientation_{orientation}, x_{x}, y_{y} {}

  void TurnRight();
  void TurnLeft();
  void Move(const Tape& cinta);
  void Step(Tape& cinta);

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