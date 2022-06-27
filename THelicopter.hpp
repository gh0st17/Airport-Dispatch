#pragma once
#include "TLA.hpp"

class THelicopter : public TLA {
public:
  THelicopter(unsigned n, float x, float y, float V, float xc, float yc) : TLA(n, x, y, V, xc, yc) {}
  void move(const float& t, const bool a);
  bool get_a(const bool& air_f, const float& air_x,
    const float& air_y, const float& air_l);
  void updateLanding(float& air_x, float& air_y, float& air_l);
};