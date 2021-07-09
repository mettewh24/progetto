#include "pandemic.prova1.hpp"

#include <cassert>
#include <cmath>
#include <vector>

World_state approx(World_state const& state) {
  World_state state_approx = state;
  int integral_R = static_cast<int>(state_approx.R);
  int integral_S = static_cast<int>(state_approx.S);
  int integral_I = static_cast<int>(state_approx.I);

  double decimals_R = state_approx.R - integral_R;
  double decimals_S = state_approx.S - integral_S;
  double decimals_I = state_approx.I - integral_I;
  auto decimal_sum = decimals_I + decimals_R + decimals_S;

  if (decimal_sum <= 1.0001 && decimal_sum >= 0.9999) {
    if (decimals_S > decimals_R && decimals_S > decimals_I) {
      ++integral_S;
    }
    if (decimals_I > decimals_R && decimals_I > decimals_S) {
      ++integral_I;
    }
    if (decimals_R > decimals_S && decimals_R > decimals_I) {
      ++integral_R;
    }
    if (std::abs(decimals_S - decimals_I) < 0.0000001 &&
        std::abs(decimals_S - .5) == 0.0000001) {
      ++integral_S;
    }
    if (std::abs(decimals_I - decimals_R) < 0.0000001 &&
        std::abs(decimals_I - .5) == 0.0000001) {
      ++integral_I;
    }
    if (std::abs(decimals_R - decimals_S) < 0.0000001 &&
        std::abs(decimals_R - .5) == 0.0000001) {
      ++integral_R;
    }
  }
  if (decimal_sum <= 2.0001 && decimal_sum >= 1.9999) {
    if (decimals_S > decimals_R or decimals_S > decimals_I) {
      ++integral_S;
    }
    if (decimals_I > decimals_R or decimals_I > decimals_S) {
      ++integral_I;
    }
    if (decimals_R > decimals_S or decimals_R > decimals_I) {
      ++integral_R;
    }
    if (std::abs(decimals_S - decimals_I) < 0.0000001 &&
        decimals_S < decimals_R) {
      ++integral_S;
    }
    if (std::abs(decimals_I - decimals_R) < 0.0000001 &&
        decimals_I < decimals_S) {
      ++integral_I;
    }
    if (std::abs(decimals_R - decimals_S) < 0.0000001 &&
        decimals_R < decimals_I) {
      ++integral_R;
    }
  }
  if (decimal_sum < 0.0000001) {
  } else {
  }
  assert(integral_S + integral_I + integral_R == state_approx.N);

  state_approx.S = integral_S;
  state_approx.I = integral_I;
  state_approx.R = integral_R;  // integral parts of S I e R
  return state_approx;
}

bool operator==(World_state const& l, World_state const& r) {
  bool alpha = l.S == r.S && l.I == r.I && l.R == r.R && l.beta == r.beta &&
               l.gamma == r.gamma && l.N == r.N;
  return alpha;
};

World_state const& Pandemic::get_state() { return p_initial_state; }

int const& Pandemic::get_duration() { return p_duration_in_days; }

World_state const next(
    World_state const& state)  // function that computes the next state
{
  World_state next_state = state;
  double R = state.R + state.gamma * state.I;
  double S = state.S - state.beta * state.S * state.I * std::pow(state.N, -1);
  double I = state.I + state.beta * state.S * state.I * std::pow(state.N, -1) -
             state.gamma * state.I;
  next_state.S = S;
  next_state.I = I;
  next_state.R = R;

  double diff = next_state.S + next_state.I + next_state.R - next_state.N;
  assert(diff < 0.0001 && diff > -0.0001);  //N must be preserved

  return next_state;
}

std::vector<World_state> evolve(World_state const& initial_state,
                                int const& duration_in_days) {
  std::vector<World_state> result{
      initial_state};       // result has already initial state inside
  assert(!result.empty());  // Result non empty(empty== error)

  for (int i = 1; i <= duration_in_days; ++i) {
    auto a = next(result.back());
    result.push_back(a);
  }
  return result;
}

std::vector<World_state> evolve(std::vector<World_state> states, int start,
                                int new_duration_in_days, double beta,
                                double gamma) {
  std::vector<World_state> result = states;
  int size = static_cast<int>(result.size());
  assert(start < size && start >= 0);
  result[start].beta = beta;
  result[start].gamma = gamma;
  if (new_duration_in_days <= size - 1) {
    for (int i = start; i < size - 1;
         ++i) {  // size()-1 matches the number of the last day(numeration starts from 0)
      auto a = next(result[i]);  // compute day after start
      result[i + 1] = a;
    }
  } else {
    for (int i = start; i < size - 1; ++i) {
      auto a = next(result[i]);
      result[i + 1] = a;
    }
    for (int i = size - 1; i < new_duration_in_days; ++i) {
      auto a = next(result[i - 1]);
      result.push_back(a);
    }
  }
  return result;
}