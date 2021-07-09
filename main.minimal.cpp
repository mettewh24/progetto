#include <cassert>
#include <iomanip>
#include <iostream>

#include "pandemic.hpp"
//#include"pandemic.hpp"

void print(std::vector<World_state> const& state) {
  std::cout << "+-----------+-----------+-----------+-----------+-----------+\n"
               "|    Day    |     S     |     I     |     R     |     N     |\n"
               "+-----------+-----------+-----------+-----------+-----------+\n"
            << std::fixed;
  for (int i = 0; i < static_cast<int>(state.size()); ++i) {
    std::cout << std::setprecision(0) << "| " << std::setw(9) << i << " | "
              << std::setw(9) << state[i].S << " | " << std::setw(9)
              << state[i].I << " | " << std::setw(9) << state[i].R << " | "
              << std::setw(9) << state[i].N << " |\n";
  }
  std::cout << "+-----------+-----------+-----------+-----------+-----------+\n"
            << state.size();
}

int main() {
  World_state initial_state;
  int duration_in_days;

  std::cin >> duration_in_days >> initial_state.N >> initial_state.S >>
      initial_state.I >> initial_state.R >> initial_state.beta >>
      initial_state.gamma;  // lettura da input dei paramentri dell'epidemia

  try {
    Pandemic sir{initial_state, duration_in_days};
  } catch (std::runtime_error const& e) {
    std::cerr << e.what() << '\n';
  };

  Pandemic sir{initial_state, duration_in_days};
  std::vector<World_state> a = evolve(sir.get_state(), sir.get_duration());
  for (int i = 0; i <= duration_in_days; ++i) {
    a[i] = approx(a[i]);
    assert(a[i].S + a[i].I + a[i].R - a[i].N == 0);
  }
  print(a);
}