#pragma once
#include "TAObject.hpp"
#include "TLA.hpp"
#include <vector>

using namespace std;

class TAirport : public TAObject {
  private:
  float l;
  vector<TLA*> LA;

  bool isAllLanded();

  public:
  TAirport(float x, float y, float l);
  ~TAirport();
  void addLA(TLA* LA);
  void Do(float t0, float tk);
};