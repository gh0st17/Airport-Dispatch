#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
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

typedef chrono::duration<float> fsec;

void TAirport::land(atomic_bool& allow_landing, TLA* la) {
  vector<float> pos;
  auto t2 = chrono::high_resolution_clock::now();
  fsec duration;
  float time;
  if (la != nullptr)
    while (!la->getLanding()) {
      t2 = chrono::high_resolution_clock::now();
      duration = t2 - t1;
      time = duration.count();
      pos = la->getPos();
      if (allow_landing && !la->took) {
        allow_landing = false;
        la->took = true;
      }
      if (la->took) {
        locker.lock();
        cout << "LA " << la->n + 1 << setprecision(2) << " (" << setw(7) << pos[0];
        cout << ',' << setw(7) << pos[1] << ")[landing]\n";
        locker.unlock();
        la->move(time, la->get_a(f, x, y, l));
        la->updateLanding(x, y, l);
        if (la->getLanding()) {
          locker.lock();
          stats_data.push_back(stats(la->n,
            (stats_data.size() > 0 ? time - stats_data.back().t_landing : 0), time));
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
        locker.lock();
        cout << "LA " << la->n + 1 << setprecision(2) << " (" << setw(7) << pos[0];
        cout << ',' << setw(7) << pos[1] << ")[waiting]\n";
        locker.unlock();
        if(dynamic_cast<TAircraft*>(la) != nullptr)
          la->move(time, la->get_a(f, x, y, l));
      }
    }
}

void TAirport::Do() {
  atomic_bool allow_landing = true;
  vector<thread> threads;
  cout.setf(ios::fixed);
  for (const auto& x : LA)
    threads.push_back(thread(&TAirport::land, this, ref(allow_landing), x));

  //threads.push_back(thread(&TAirport::update, this));
	for_each(threads.begin(), threads.end(), mem_fn(&thread::join));

  for (const auto& x : stats_data) {
    cout << "LA " << x.LA_n + 1 << " landed at " << setprecision(3) << x.t_landing;
    cout << " sec, wait " << x.t_wait << " sec\n";
  }
  cout << "Done\n";
}

bool TAirport::isAllLanded() {
  for (const auto& la : LA)
    if (!la->getLanding())
      return false;

  return true;
}