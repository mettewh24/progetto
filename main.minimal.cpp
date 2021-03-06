#include "pandemic.hpp"

#include <cassert>
#include <iomanip>
#include <iostream>

int number_of_digits(int const number) {
  int N = number;
  int size = floor(log10(N))+1;
  return size;
}

void print(std::vector<World_state> const& state) {
  int max_lenght =
      std::max(number_of_digits(state[0].N), number_of_digits(state.size()));
  if (max_lenght % 2 == 0) {
    ++max_lenght;
  }
  if (max_lenght < 5) {
    max_lenght = 5;
  }
  std::string bar = "+";
  std::string legend = "|";
  std::vector<std::string> variables = {"Day", "S", "I", "R", "N", "B", "G"};
  for (int b = 0; b < 7; ++b) {
    for (int a = 1; a <= max_lenght + 2; ++a) {
      bar.append("-");
    }
    for (int c = 0;
         c <= static_cast<int>((max_lenght - variables[b].length()) / 2); ++c) {
      legend.append(" ");
    }
    legend.append(variables[b]);
    for (int c = 0;
         c <= static_cast<int>((max_lenght - variables[b].length()) / 2); ++c) {
      legend.append(" ");
    }
    bar.append("+");
    legend.append("|");
  }
  std::cout << bar << '\n' << legend << '\n' << bar << '\n';
  int size = state.size();
  for (int i = 0; i < size; ++i) {
    std::cout << "| " << std::setw(max_lenght) << i << " | "
              << std::setw(max_lenght) << state[i].S << " | "
              << std::setw(max_lenght) << state[i].I << " | "
              << std::setw(max_lenght) << state[i].R << " | "
              << std::setw(max_lenght) << state[i].S + state[i].I + state[i].R
              << " | " << std::setw(max_lenght) << state[i].beta << " | "
              << std::setw(max_lenght) << state[i].gamma << " | " << '\n';
  }
  std::cout << bar << "\n";
}

int main() {
  World_state initial_state;
  int duration_in_days;

  std::cout << "Enter duration in days: ";
  std::cin >> duration_in_days;
  std::cout << "Enter total population: ";
  std::cin >> initial_state.N;
  std::cout << "Enter number of susceptibles: ";
  std::cin >> initial_state.S;
  std::cout << "Enter number of infected: ";
  std::cin >> initial_state.I;
  std::cout << "Enter number of people dead and healed: ";
  std::cin >> initial_state.R;
  std::cout << "Enter beta (0<beta<1): ";
  std::cin >> initial_state.beta;
  std::cout << "Enter gamma (0<gamma<1): ";
  std::cin >> initial_state.gamma; // lettura da input dei parametri dell'epidemia

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