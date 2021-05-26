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

World_state approx(World_state& state) {  // non funziona, rivedi meglio
  double decimals_R = state.R - static_cast<int>(state.R);
  double decimals_S = state.S - static_cast<int>(state.S);
  double decimals_I = state.I - static_cast<int>(state.I);
  double decimal_sum = decimals_I + decimals_R + decimals_S;
  if (decimal_sum == 1.0) {
    if (decimals_S > decimals_R && decimals_S > decimals_I) {
      ++state.S;
    }
    if (decimals_I > decimals_R && decimals_I > decimals_S) {
      ++state.I;
    }
    if (decimals_R > decimals_S && decimals_S > decimals_I) {
      ++state.R;
    }
    if (decimals_S == decimals_I && decimals_S == .5) {
      ++state.S;
    }
    if (decimals_I == decimals_R && decimals_I == .5) {
      ++state.I;
    }
    if (decimals_R == decimals_S && decimals_R == .5) {
      ++state.R;
    }
  }
  if (decimal_sum == 2) {  // qua c'è un problema da qualche parte, non
                           // approssima correttamente  :_(
    if (decimals_S > decimals_R or decimals_S > decimals_I) {
      ++state.S;
    }
    if (decimals_I > decimals_R or decimals_I > decimals_S) {
      ++state.I;
    }
    if (decimals_R > decimals_S or decimals_S > decimals_I) {
      ++state.R;
    }
    if (decimals_S == decimals_I && decimals_S < decimals_R) {
      ++state.S;
    }
    if (decimals_I == decimals_R && decimals_I < decimals_S) {
      ++state.I;
    }
    if (decimals_R == decimals_S && decimals_R < decimals_I) {
      ++state.R;
    }
  }
  if (decimal_sum == 0) {
  }

  state.S = static_cast<int>(state.S);
  state.I = static_cast<int>(state.I);
  state.R = static_cast<int>(state.R);  // le parti intere di S I e R
  return state;
}

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
    assert(initial_state.N ==
           initial_state.S + initial_state.R + initial_state.I);
    assert(duration_in_days > 0);  // ha senso metterli qua??
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

    for (int day = 1; day <= m_duration_in_days; ++day) {
      double R = state.R + state.gamma * state.I;
      double S = state.S - state.beta * state.S * state.I / state.N;
      double I = state.I + state.beta * state.S * state.I / state.N -
                 state.gamma * state.I;
      state.S = S;
      state.I = I;
      state.R = R;
      state = approx(state);

      // assert(state.S + state.I + state.R == state.N);

      result.push_back(state);
    }

    return result;
  }
};

#endif