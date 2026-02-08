#include "../include/ant.h"
#include "../include/tape.h"
#include "../include/simulator.h"

#include <iostream>

int main(int argc, char* argv[]) {
  std::cout << "This is Langton's Ant" << std::endl;
  size_t R,C;
  std::cin >> R >> C;
  Tape tape1(R,C);
  tape1.DrawCell(4, 4);
  Ant ant1(0,5,5);
  tape1.PrintUntilAnt(&ant1);
  std::cout << ant1;
  tape1.PrintPostAnt(&ant1);
  // std::cout << ant1 << " - POSX: " << ant1.GetX() << " POSY: " << ant1.GetY() << std::endl;
  return 0;
}