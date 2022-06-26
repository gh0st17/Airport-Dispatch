#pragma once
#include "TAObject.hpp"
#include "TLA.hpp"
#include <vector>
#include <mutex>

using namespace std;

struct stats{
  unsigned LA_n = 0;
  float t_wait = 0, t_landing = 0;

  stats(unsigned LA_n, float t_wait, float t_landing) {
    this->LA_n = LA_n;
    this->t_wait = t_wait;
    this->t_landing = t_landing;
  }
};

class TAirport : public TAObject {
  private:
  mutex locker;
  float l;
  vector<TLA*> LA;
  vector<stats> stats_data;
  chrono::steady_clock::time_point t1 = chrono::high_resolution_clock::now();

  void land(atomic_bool& allow_landing, TLA* la);
  bool isAllLanded();

  public:
  TAirport(float x, float y, float l);
  ~TAirport();
  void addLA(TLA* LA);
  void Do();
};