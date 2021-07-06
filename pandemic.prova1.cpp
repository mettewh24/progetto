#include "pandemic.prova1.hpp"

#include <cassert>
#include <cmath>
#include <vector>

World_state approx(World_state& state) {
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

World_state Pandemic::next(World_state& state)
    const  // funzione (return type vector<state>) che fa evolvere allo
           // stadio successivo(mettere nome significativo)
{
  double R = state.R + state.gamma * state.I;
  double S = state.S - state.beta * state.S * state.I * std::pow(state.N, -1);
  double I = state.I + state.beta * state.S * state.I * std::pow(state.N, -1) -
             state.gamma * state.I;
  state.S = S;
  state.I = I;
  state.R = R;
  state = approx(state);

  assert(state.S + state.I + state.R == state.N);//!

  return state;
}

std::vector<World_state> Pandemic::evolve() const {
  std::vector<World_state> result{
      p_initial_state};     // result ha già lo stato iniziale come elemento
  assert(!result.empty());  // Result non vuoto(sennò è errore)

  for (int i = 1; i < p_duration_in_days; ++i) {
    result.push_back(next(result.back()));
  }
  return result;
}
