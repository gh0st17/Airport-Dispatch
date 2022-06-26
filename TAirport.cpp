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
      locker.lock();
      if (allow_landing && !la->took) {
        allow_landing = false;
        la->took = true;
      }
      if (la->took) {
        cout << "LA " << la->n + 1 << setprecision(2) << " (" << setw(8) << pos[0];
        cout << ',' << setw(8) << pos[1] << ")[landing]\n";
        la->move(t, la->get_a(f, x, y, l));
        la->updateLanding(x, y, l);
        if (la->getLanding()) {
          stats_data.push_back(stats(la->n,
            (stats_data.size() > 0 ? t - stats_data.back().t_landing : 0), t));
          if(dynamic_cast<TAircraft*>(la) != nullptr)
            cout << "Aircraft " << la->n + 1 << " landed\n";
          else if(dynamic_cast<THelicopter*>(la) != nullptr)
            cout << "Helicopter " << la->n + 1 << " landed\n";
          allow_landing = true;
          locker.unlock();
          break;
        }
      }
      else if (!la->getLanding() && !la->took) {
        cout << "LA " << la->n + 1 << setprecision(2) << " (" << setw(8) << pos[0];
        cout << ',' << setw(8) << pos[1] << ")[waiting]\n";
        if(dynamic_cast<TAircraft*>(la) != nullptr)
          la->move(t, la->get_a(f, x, y, l));
      }
      locker.unlock();
    }
}

void TAirport::Do(float t0, float tk) {
  bool allow_landing = true;
  vector<thread> threads;
  cout.setf(ios::fixed);
  for (const auto& x : LA)
    threads.push_back(thread(&TAirport::land, this, ref(allow_landing), x));

  threads.push_back(thread(&TAirport::update, this, ref(t0), ref(tk)));
	for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
}

void TAirport::update(float& t0, float& tk) {
  t = t0;
  while (!isAllLanded()) {
    locker.lock();
    t += dt;
    locker.unlock();
  }
  locker.lock();
  for (const auto& x : stats_data) {
    cout << "LA " << x.LA_n + 1 << " landed at " << x.t_landing;
    cout << " sec, wait " << x.t_wait << " sec\n";
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