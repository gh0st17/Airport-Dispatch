#include <iostream>
#include <iomanip>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
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

void TAirport::land(bool& allow_landing, TLA* la) {
  vector<float> pos;
  if (la != nullptr)
    while (!la->getLanding()) {
      pos = la->getPos();
      if (allow_landing && !la->took) {
        allow_landing = false;
        la->took = true;
      }
      if (la->took) {
        locker.lock();
        cout << "LA " << la->n + 1 << setprecision(2) << " (" << setw(8) << pos[0];
        cout << ',' << setw(8) << pos[1] << ")[landing]\n";
        locker.unlock();
        la->move(t, la->get_a(f, x, y, l));
        la->updateLanding(x, y, l);
        if (la->getLanding()) {
          locker.lock();
          stats_data.push_back(stats(la->n,
            (stats_data.size() > 0 ? t - stats_data.back().t_landing : 0), t));
          if(dynamic_cast<TAircraft*>(la) != nullptr)
            cout << "Aircraft " << la->n + 1 << " landed\n";
          else if(dynamic_cast<THelicopter*>(la) != nullptr)
            cout << "Helicopter " << la->n + 1 << " landed\n";
          locker.unlock();
          allow_landing = true;
          break;
        }
      }
      else if (!la->getLanding() && !la->took) {
        locker.lock();
        cout << "LA " << la->n + 1 << setprecision(2) << " (" << setw(8) << pos[0];
        cout << ',' << setw(8) << pos[1] << ")[waiting]\n";
        locker.unlock();
        if(dynamic_cast<TAircraft*>(la) != nullptr)
          la->move(t, la->get_a(f, x, y, l));
      }
    }
}

void TAirport::update(float t0, float tk) {
  bool allow_landing = true;
  vector<thread> threads;
  cout.setf(ios::fixed);
  for (const auto& x : LA)
    threads.push_back(thread(&TAirport::land, this, ref(allow_landing), x));

  threads.push_back(thread(&TAirport::Do, this, ref(t0), ref(tk)));
	for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
}

void TAirport::Do(float& t0, float& tk) {
  t = t0;
  while (!isAllLanded())
    t += dt;
  locker.lock();
  for (const auto& x : stats_data) {
    cout << "LA " << x.LA_n << " landed at " << x.t_landing;
    cout << " seconds, wait time " << x.t_wait << " seconds\n";
  }
  cout << "Done\n";
  locker.unlock();
}

bool TAirport::isAllLanded() {
  for (const auto& la : LA)
    if (!la->getLanding())
      return false;

  return true;
}