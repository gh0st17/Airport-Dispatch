#include <iostream>
#include "TAirport.hpp"
#include "TAircraft.hpp"
#include "THelicopter.hpp"

using namespace std;

int main() {
  unsigned n = 0;
  TAirport air(.0f, 300.f, 3000.f);
  air.addLA(new TAircraft(n++, 1500.f, 500.f, 200.f, 200.f, 450.f));
  air.addLA(new THelicopter(n++, .0f, 500.f, 25.f, -1.f, 1.f));
  air.addLA(new THelicopter(n++, 2.5f, 520.f, 25.f, -2.f, 1.f));
  air.addLA(new TAircraft(n++, -600.f, 250.f, 200.f, .0f, 550.f));

  air.Do();

  return 0;
}