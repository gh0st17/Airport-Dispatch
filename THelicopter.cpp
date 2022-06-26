#include <iostream>
#include "THelicopter.hpp"

using namespace std;

void THelicopter::move(float t, bool a) {
  x -= -a * V * cosf(phi) * dt;
  y -= a * V * sinf(phi) * dt;
}

bool THelicopter::get_a(bool& air_f, float& air_x, float& air_y, float& air_l) {
  if (!(air_f && !f)) {
    f = true;
    return true;
  }
  else {
    f = false;
    return false;
  }
}

void THelicopter::updateLanding(float& air_x, float& air_y, float& air_l, unsigned* air_f, unsigned& n) {
  float x = powf(this->x - air_x, 2), y = powf(this->y - air_y, 2), air = powf(air_l / 50, 2);
  
  if (x + y < air && f) {
    landing = true;
    (*air_f)++;
    cout << "Helicopter " << n + 1 << " landed\n";
  }
  else if (f)
    landing = false;
}