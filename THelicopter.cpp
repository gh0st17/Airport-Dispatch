#include <iostream>
#include "THelicopter.hpp"

using namespace std;

void THelicopter::move(const float& t, const bool a) {
  x -= -1 * a * V * cosf(phi);
  y -= a * V * sinf(phi);
}

bool THelicopter::get_a(const bool& air_f, const float& air_x,
  const float& air_y, const float& air_l) {

  if (!(air_f)) {
    return true;
  }
  else {
    return false;
  }
}

void THelicopter::updateLanding(float& air_x, float& air_y, float& air_l) {
  float x = powf(this->x - air_x, 2), y = powf(this->y - air_y, 2), air = powf(air_l / 50, 2);
  
  if (x + y < air)
    landing = true;
}