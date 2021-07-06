#ifndef PANDEMIC_PROVA1_HPP
#define PANDEMIC_PROVA1_HPP

#include <cassert>
#include <cmath>
#include <vector>

struct World_state {
  double S;
  double I;
  double R;
  double beta;
  double gamma;
  int N;
};

World_state approx(World_state& state);

inline bool operator==(World_state const& l, World_state const& r);

class Pandemic {
  World_state p_initial_state;
  int p_duration_in_days;  // in days

 public:
  Pandemic(World_state const& initial_state, int duration_in_days)
      : p_initial_state{initial_state}, p_duration_in_days{duration_in_days} {
    assert(initial_state.beta >= 0 && initial_state.beta <= 1);
    assert(initial_state.gamma >= 0 && initial_state.gamma <= 1);
    assert(initial_state.N > 0 && initial_state.S >= 0 &&
           initial_state.R >= 0 && initial_state.I >= 0);
    assert(initial_state.N ==
           initial_state.S + initial_state.R + initial_state.I);
    assert(duration_in_days > 0);  // ha senso metterli qua??
  }

  std::vector<World_state> evolve()
      const;
};

#endif