#include <iostream>
#include "TAirport.hpp"
#include "TAircraft.hpp"
#include "THelicopter.hpp"

using namespace std;

int main() {
  unsigned n = 0;
  TAirport air(.0f, 300.0f, 3000.0f);
  air.addLA(new TAircraft(n++, 575.0f, 400.0f, 210.0f, 15.0f, 600.0f));
  air.addLA(new THelicopter(n++, .0f, 580.0f, 28.0f, -1.0f, 1.0f));
  air.addLA(new THelicopter(n++, 2.0f, 450.0f, 25.0f, -2.0f, 1.0f));
  air.addLA(new TAircraft(n++, -600.0f, 350.0f, 220.0f, .0f, 100.0f));

  air.Do(.0f, 3600.0f);

  return 0;
}