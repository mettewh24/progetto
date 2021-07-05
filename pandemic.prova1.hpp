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
  int integral_R = static_cast<int>(state.R);
  int integral_S = static_cast<int>(state.S);
  int integral_I = static_cast<int>(state.I);

  double decimals_R = state.R - integral_R;
  double decimals_S = state.S - integral_S;
  double decimals_I = state.I - integral_I;
  auto decimal_sum = decimals_I + decimals_R + decimals_S;

  if (0.9 <= decimal_sum && decimal_sum <= 1.1) {
    if (decimals_S > decimals_R && decimals_S > decimals_I) {
      ++integral_S;
    }
    if (decimals_I > decimals_R && decimals_I > decimals_S) {
      ++integral_I;
    }
    if (decimals_R > decimals_S && decimals_R > decimals_I) {
      ++integral_R;
    }
    if (decimals_S == decimals_I && decimals_S == .5) {
      ++integral_S;
    }
    if (decimals_I == decimals_R && decimals_I == .5) {
      ++integral_I;
    }
    if (decimals_R == decimals_S && decimals_R == .5) {
      ++integral_R;
    }
  }
  if (1.9 <= decimal_sum && decimal_sum <= 2.1) {
    if (decimals_S > decimals_R or decimals_S > decimals_I) {
      ++integral_S;
    }
    if (decimals_I > decimals_R or decimals_I > decimals_S) {
      ++integral_I;
    }
    if (decimals_R > decimals_S or decimals_R > decimals_I) {
      ++integral_R;
    }
    if (decimals_S == decimals_I && decimals_S < decimals_R) {
      ++integral_S;
    }
    if (decimals_I == decimals_R && decimals_I < decimals_S) {
      ++integral_I;
    }
    if (decimals_R == decimals_S && decimals_R < decimals_I) {
      ++integral_R;
    }
  }
  if (decimal_sum == 0) {
  } else {  // è solo uno strumeto di controllo che i nostri decimali rientirno
            // in uno dei tre casi sopra, va tolto in consegna del progetto
    state.I = 0;
    state.S = 0;
    state.R = 0;
  }

  state.S = integral_S;
  state.I = integral_I;
  state.R = integral_R;  // le parti intere di S I e R
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

    World_state state = result.back();  // state è l'ultimo elemento di
                                        // result(Forse va dentro al for?)

    for (int day = 1; day <= m_duration_in_days; ++day) {
      double R = state.R + state.gamma * state.I;
      double S =
          state.S - state.beta * state.S * state.I * std::pow(state.N, -1);
      double I = state.I +
                      state.beta * state.S * state.I * std::pow(state.N, -1) -
                      state.gamma * state.I;
      state.S = S;
      state.I = I;
      state.R = R;
      state = approx(state);

      assert(state.S + state.I + state.R == state.N);

      result.push_back(state);
    }

    return result;
  }
};

#endif