#pragma once
#include <cmath>

class TAObject {
  protected:
  const float dt = .5f;
  float x, y;
  bool f = false;

  public:
  TAObject(float x, float y);
  ~TAObject() {}
};
