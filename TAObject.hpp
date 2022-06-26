#pragma once
#include <cmath>

class TAObject {
  protected:
  float dt = .1f, x, y;
  bool f = false;

  public:
  TAObject(float x, float y);
  ~TAObject() {}
};
