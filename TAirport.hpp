#pragma once
#include "TAObject.hpp"
#include "TLA.hpp"
#include <vector>

using namespace std;

struct stats{
  unsigned LA_n = 0;
  float t_wait = 0, t_landing = 0;
};


class TAirport : public TAObject {
  private:
  float l;
  vector<TLA*> LA;
  vector<stats> stats_data;

  bool isAllLanded();

  public:
  TAirport(float x, float y, float l);
  ~TAirport();
  void addLA(TLA* LA);
  void Do(float t0, float tk);
};