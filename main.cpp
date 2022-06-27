#include <iostream>
#include "TAirport.hpp"
#include "TAircraft.hpp"
#include "THelicopter.hpp"

using namespace std;

int main() {
  unsigned n = 0;
  TAirport air(.0f, 300.f, 3000.f);

  air.addLA(new TAircraft(n++, .0f, 5500.f, 145.f, .0f, 1450.f));
  air.addLA(new THelicopter(n++, .0f, 500.f, 25.f, -1.f, 1.f));
  air.addLA(new THelicopter(n++, 2.5f, 520.f, 25.f, -2.f, 1.f));
  air.addLA(new TAircraft(n++, .0f, 5250.f, 200.f, .0f, 1550.f));
  air.addLA(new THelicopter(n++, 5.5f, 820.f, 30.f, -2.f, 10.f));

  air.Do();

  return 0;
}