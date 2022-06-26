#pragma once
#include <cmath>

class TAObject {
  protected:
  float x, y;
  bool f = false;

  public:
  TAObject(float x, float y);
  ~TAObject() {}
};
