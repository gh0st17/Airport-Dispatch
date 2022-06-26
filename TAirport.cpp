#include <iostream>
#include <iomanip>
#include <vector>
#include "TAirport.hpp"
#include "TAircraft.hpp"
#include "THelicopter.hpp"

using namespace std;

TAirport::TAirport(float x, float y, float l) : TAObject(x, y) {
  this->l = l;
}

TAirport::~TAirport() {
  for (const auto& x : LA)
    delete x;
}

void TAirport::addLA(TLA* LA) {
  this->LA.push_back(LA);
}

void TAirport::Do(float t0, float tk) {
  unsigned LA_n = 0, LA_cur = 0;
  vector<float> pos;
  bool a;
  for (float t = t0; t <= tk; t += dt) {
    LA_n = 0;
    cout << fixed << setprecision(2) << '[' << t << "s]\n";
    for (auto& la : LA) {
      pos = la->getPos();
      if (!la->getLanding() && LA_cur == LA_n) {
        cout << "LA " << LA_n + 1 << "[landing]: x: " << pos[0] << " y : " << pos[1] << endl;
        la->move(t, la->get_a(f, x, y, l));
        la->updateLanding(x, y, l, &LA_cur, LA_n);
      }
      else if (!la->getLanding()) {
        cout << "LA " << LA_n + 1 << "[waiting]: x: " << pos[0] << " y : " << pos[1] << endl;
        if(dynamic_cast<TAircraft*>(la) != nullptr)
          la->move(t, la->get_a(f, x, y, l));
      }
      LA_n++;
    }
    if (isAllLanded())
      break;
  }
  cout << "Done\n";
}

bool TAirport::isAllLanded() {
  for (const auto& la : LA)
    if (!la->getLanding())
      return false;

  return true;
}