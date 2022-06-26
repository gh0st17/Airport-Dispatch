#pragma once
#include "TAObject.hpp"
#include <vector>

class TLA : public TAObject {
  protected:
    float xc, yc, R, phi, V;
    bool landing = false;

  public:
    TLA(float x, float y, float V, float xc, float yc);
    virtual void move(float t, bool a) {};
    virtual bool get_a(bool& air_f, float& air_x, float& air_y, float& air_l) { return false; };
    bool get_f() { return f; }
    bool getLanding() { return landing; }
    virtual void updateLanding(float& air_x, float& air_y, float& air_l) {};
    std::vector<float> getPos() { return std::vector<float>{ x, y }; }
};