#pragma once
#include <cmath>

class TAObject {
  protected:
  float dt = .5f, x, y;
  bool f = false;

  public:
  TAObject(float x, float y);
  ~TAObject() {}
};
