#include <iostream>
#include "TAirport.hpp"
#include "TAircraft.hpp"
#include "THelicopter.hpp"

using namespace std;

int main() {
  unsigned n = 0;
  TAirport air(.0f, 300.f, 3000.f);
  air.addLA(new TAircraft(n++, 375.f, 400.f, 210.f, 15.f, 30.f));
  air.addLA(new THelicopter(n++, .0f, 380.f, 35.f, -1.f, 1.f));
  air.addLA(new THelicopter(n++, 2.f, 350.f, 40.f, -2.f, 1.f));
  air.addLA(new TAircraft(n++, -300.f, 350.f, 220.f, .0f, 25.f));

  air.Do();

  return 0;
}