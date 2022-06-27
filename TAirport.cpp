#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <thread>
#include <atomic>
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

void TAirport::land(atomic<bool>& allow_landing, TLA* la) {
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
      if (allow_landing && !la->getTook()) {
        allow_landing = false;
        la->setTook(true);
      }
      if (la->getTook()) {
        locker.lock();
        cout << "LA " << la->n + 1 << setprecision(2) << " (" << setw(7) << pos[0];
        cout << ',' << setw(7) << pos[1] << ")[landing]\n";
        locker.unlock();
        this_thread::sleep_for(chrono::milliseconds(150));
        la->move(time, la->get_a(f, x, y, l));
        la->updateLanding(x, y, l);
        if (la->getLanding()) {
          stats_data.push_back(stats(la->n,
            (stats_data.size() > 0 ? time - stats_data.back().t_landing : 0), time));
          if(dynamic_cast<TAircraft*>(la) != nullptr)
            cout << "Aircraft " << la->n + 1 << " landed\n";
          else if(dynamic_cast<THelicopter*>(la) != nullptr)
            cout << "Helicopter " << la->n + 1 << " landed\n";
          allow_landing = true;
          break;
        }
      }
      else if (!la->getLanding() && !la->getTook()) {
        locker.lock();
        cout << "LA " << la->n + 1 << setprecision(2) << " (" << setw(7) << pos[0];
        cout << ',' << setw(7) << pos[1] << ")[waiting]\n";
        locker.unlock();
        this_thread::sleep_for(chrono::milliseconds(1500));
        if(dynamic_cast<TAircraft*>(la) != nullptr)
          la->move(time, la->get_a(f, x, y, l));
      }
    }
}

void TAirport::Do() {
  atomic<bool> allow_landing = true;
  vector<thread> threads;
  cout.setf(ios::fixed);
  for (const auto& x : LA)
    threads.push_back(thread(&TAirport::land, this, ref(allow_landing), x));

  for_each(threads.begin(), threads.end(), mem_fn(&thread::join));

  for (const auto& x : stats_data) {
    cout << "LA " << x.LA_n + 1 << " landed at " << setprecision(3) << x.t_landing;
    cout << " sec, wait " << x.t_wait << " sec\n";
  }
  cout << "Done\n";
}