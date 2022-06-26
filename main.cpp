#include <iostream>
#include "TAirport.hpp"
#include "TAircraft.hpp"
#include "THelicopter.hpp"

using namespace std;

int main() {
  unsigned n = 0;
  TAirport air(.0f, 300.0f, 3000.0f);
  air.addLA(new TAircraft(n++, 1500.0f, 500.0f, 200.0f, 200.0f, 450.0f));
  air.addLA(new THelicopter(n++, .0f, 500.0f, 25.0f, -1.0f, 1.0f));
  air.addLA(new THelicopter(n++, 2.5f, 520.0f, 25.0f, -2.0f, 1.0f));
  air.addLA(new TAircraft(n++, -600.0f, 250.0f, 200.0f, .0f, 550.0f));

  air.update(.0f, 3600.0f);

  return 0;
}