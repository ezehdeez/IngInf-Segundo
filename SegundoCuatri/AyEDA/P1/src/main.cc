#include "../include/ant.h"
#include "../include/functions.h"
#include "../include/tape.h"
#include "../include/simulator.h"

#include <iostream>

int main(int argc, char* argv[]) {
  // CheckCorrectParameters(argc, argv, 2);
  // FileCheck(argv[1]);
  Simulator simulator(argv[1]);
  simulator.RunSimulation();
  return 0;
}