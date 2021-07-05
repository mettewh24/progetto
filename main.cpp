#include <iomanip>
#include <iostream>

#include "pandemic.prova1.hpp"
//#include"pandemic.hpp"

void print(std::vector<World_state> const& state) {
  std::cout << "+-----------+-----------+-----------+-----------+\n"
               "|     S     |     I     |     R     |     N     |\n"
               "+-----------+-----------+-----------+-----------+\n"
            << std::fixed;
  for (auto& state : state) {
    std::cout <<std::setprecision(1)<< "| " << std::setw(9) << state.S << " | " << std::setw(9)
              << state.I << " | " << std::setw(9) << state.R << " | "
              << std::setw(9) << state.N << " |\n";
  }
  std::cout << "+-----------+-----------+-----------+-----------+\n";
}

int main() {
  World_state initial_state;
  int duration_in_days;
  std::cin >> duration_in_days >>
      initial_state
          .N;  // lettura da input di durata e grandezza della popolazione
  std::cin >> initial_state.S >> initial_state.I >>
      initial_state.R;  // lettura da input della ripartizione della popolazione
  std::cin >> initial_state.beta >>
      initial_state.gamma;  // lettura da input dei paramentri dell'epidemia

  Pandemic sir{initial_state, duration_in_days};
  auto a = sir.evolve();
  print(a);
}