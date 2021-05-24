#ifndef PANDEMIC_HPP
#define PANDEMIC_HPP

#include <cassert>
#include <cmath>
#include <vector>

struct World_state {
  int S;
  int I;
  int R;
  double beta;
  double gamma;
  int N;
};

inline bool operator==(World_state const& l, World_state const& r) {
  bool alpha = l.S == r.S && l.I == r.I && l.R == r.R && l.beta == r.beta &&
               l.gamma == r.gamma && l.N == r.N;
  return alpha;
};

class Pandemic {
  World_state m_initial_state;
  int m_duration_in_days;  // in days

 public:
  Pandemic(World_state const& initial_state, int duration_in_days)
      : m_initial_state{initial_state}, m_duration_in_days{duration_in_days} {
    assert(initial_state.beta >= 0 && initial_state.beta <= 1);
    assert(initial_state.gamma >= 0 && initial_state.gamma <= 1);
    assert(initial_state.N > 0 && initial_state.S >= 0 &&
           initial_state.R >= 0 && initial_state.I >= 0);
    assert(initial_state.N == initial_state.S + initial_state.R +
                                  initial_state.I);  // ha senso metterli qua??
  }

  std::vector<World_state> evolve()
      const  // funzione (return type vector<state>) che fa evolvere allo
             // stadio successivo(mettere nome significativo)
  {
    std::vector<World_state> result{
        m_initial_state};     // result ha già lo stato iniziale come elemento
    assert(!result.empty());  // Result non vuoto(sennò è errore)

    World_state state =
        result.back();  // state è l'ultimo elemento di result(ossia quello di
                        // inizializzazione!!!!!!!!)
    World_state next;
    for (int day = 1; day <= m_duration_in_days; ++day) {
      next.R = state.R + std::round(state.gamma * state.I);
      next.S = state.S - std::round(state.beta * state.S * state.I / state.N);
      next.I = state.I + std::round(state.beta * state.S * state.I / state.N -
                                    state.gamma * state.I);
      state.R=next.R;
      state.S=next.S;
      state.I=next.I;
      assert(next.R+next.S+next.I==next.N);
      result.push_back(next);
    }  // RIVEDERE I NOMI, SONO SOLO PROVVISORI

    return result;
  }
};

#endif