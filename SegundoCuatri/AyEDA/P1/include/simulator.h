#include "../include/ant.h"
#include "../include/tape.h"

#include <string>

class Simulator {
 public:
  Simulator(const std::string&);
 private:
  Ant ant_;
  Tape tape_;
};