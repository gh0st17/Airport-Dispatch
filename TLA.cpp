#include "TLA.hpp" 

using namespace std;

TLA::TLA(unsigned n, float x, float y, float V, float xc, float yc) : TAObject (x, y) {
  this->n = n;
  this->V = V;
  this->xc = xc;
  this->yc = yc;
  R = sqrtf(powf(x - xc, 2) + powf(y - yc, 2));
  float b = [x, y, xc, yc]() {
      if (x > xc)
        return .0f;
      else if (x < xc && y < yc)
        return -0.1f;
      else if (x < xc && y > yc)
        return 1.0f;
    }();
  phi = b * (22/7) + atanf((y - yc) / (x - xc));
}