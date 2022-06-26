#pragma once
#include "TLA.hpp"

class THelicopter : public TLA {
public:
  THelicopter(float x, float y, float V, float xc, float yc) : TLA(x, y, V, xc, yc) {}
  void move(float t, bool a);
  bool get_a(bool& air_f, float& air_x, float& air_y, float& air_l);
  void updateLanding(float& air_x, float& air_y, float& air_l);
};