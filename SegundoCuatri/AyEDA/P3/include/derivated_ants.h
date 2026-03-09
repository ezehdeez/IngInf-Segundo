#include "../include/ant.h"
#include "../include/tape.h"

#ifndef ANT_C_
#define ANT_C_

class Ant_C : public Ant {
 public:
  Ant_C(char ori, int life_time, int x, int y, float voracity) : Ant(ori, life_time, x, y), voracity_{voracity} {}
  float GetVoracity() const {return voracity_;}
  void DiagonalMove(char);
 private:
  float voracity_;
};

#endif

#ifndef ANT_H_DDII_
#define ANT_H_DDII_

class Ant_H_DDII : public Ant {
 public:
  Ant_H_DDII(char orientation, int life_time, int x, int y) : Ant(orientation, life_time, x, y) {}
  void Step(Tape*) override;
  std::string GetType() const override {return "DDII";}
  char GetAlimentation() const override {return 'H';}
};

#endif

#ifndef ANT_C_IDID_
#define ANT_C_IDID_

class Ant_C_IDID : public Ant_C {
 public:
  Ant_C_IDID(char orientation, int life_time, int x, int y) : Ant_C(orientation, life_time, x, y, 0.10f) {}
  void Step(Tape*) override;
  std::string GetType() const override {return "IDID";}
  char GetAlimentation() const override {return 'C';}
};

#endif