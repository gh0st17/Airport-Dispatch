#include <iostream>
#include "TAircraft.hpp"

using namespace std;

void TAircraft::move(float t, bool a) {
  float omega = -(V/R);
  x = -(xc + R * cosf(phi + omega * t)) * (a - 1) + a * (x - V * dt);
  y = -(yc + R * sinf(phi + omega * t)) * (a - 1) + a * y;
}

bool TAircraft::get_a(bool& air_f, float& air_x, float& air_y, float& air_l) {
  if (!(air_f && !f) &&
    x > air_x &&
    abs(air_y - y) < air_l / 50) {

    f = true;
    return true;
  }
  else {
    f = false;
    return false;
  }
}

void TAircraft::updateLanding(float& air_x, float& air_y, float& air_l, unsigned* air_f, unsigned& n) {
  if (x < air_x + air_l && f) {
    landing = true;
    (*air_f)++;
    cout << "Aircraft " << n + 1 << " landed\n";
  }
  else if (f)
    landing = false;
}