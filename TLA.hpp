#pragma once
#include "TAObject.hpp"
#include <vector>

class TLA : public TAObject {
  protected:
    float xc, yc, R, phi, V;
    bool landing = false;
    bool took = false;

  public:
    unsigned n;
    TLA(unsigned n, float x, float y, float V, float xc, float yc);
    virtual void move(const float& t, const bool a) {};
    virtual bool get_a(const bool& air_f, const float& air_x,
      const float& air_y, const float& air_l) { return false; };
    bool get_f() { return f; }
    bool getLanding() { return landing; }
    bool getTook() { return took; }
    void setTook(const bool took) { this->took = took; }
    virtual void updateLanding(float& air_x, float& air_y, float& air_l) {};
    std::vector<float> getPos() { return std::vector<float>{ x, y }; }
};