#include <iostream>
#include "TAirport.hpp"
#include "TAircraft.hpp"
#include "THelicopter.hpp"

using namespace std;

int main() {
  TAirport air(.0f, 300.0f, 3000.0f);
  air.addLA(new TAircraft(1500.0f, 500.0f, 200.0f, 200.0f, 450.0f));
  air.addLA(new THelicopter(.0f, 500.0f, 25.0f, -1.0f, 1.0f));
  air.addLA(new THelicopter(2.5f, 520.0f, 25.0f, -2.0f, 1.0f));
  air.addLA(new TAircraft(-600.0f, 250.0f, 200.0f, .0f, 550.0f));

  air.Do(.0f, 3600.0f);

  return 0;
}