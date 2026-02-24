#include "../include/ant.h"
#include "../include/tape.h"

class Ant_DDII : public Ant {
 public:
  Ant_DDII(char orientation, int x, int y) : Ant(orientation, x, y) {}
  void Step(Tape& cinta) override;
  std::string GetType() const override {return "DDII";}
};

class Ant_IDID : public Ant {
 public:
  Ant_IDID(char orientation, int x, int y) : Ant(orientation, x, y) {}
  void Step(Tape& cinta) override;
  std::string GetType() const override {return "IDID";}
};