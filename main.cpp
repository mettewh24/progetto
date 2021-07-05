#include <fstream>
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
    std::cout << std::setprecision(0) << "| " << std::setw(9) << state.S
              << " | " << std::setw(9) << state.I << " | " << std::setw(9)
              << state.R << " | " << std::setw(9) << state.N << " |\n";
  }
  std::cout << "+-----------+-----------+-----------+-----------+\n";
}

void print_on_file(std::vector<World_state> const& state) {
  std::ofstream fout("pandemic.txt");
  fout << "+-----------+-----------+-----------+-----------+\n"
          "|     S     |     I     |     R     |     N     |\n"
          "+-----------+-----------+-----------+-----------+\n"
       << std::fixed;
  for (auto& state : state) {
    fout << std::setprecision(0) << "| " << std::setw(9) << state.S << " | "
         << std::setw(9) << state.I << " | " << std::setw(9) << state.R << " | "
         << std::setw(9) << state.N << " |\n";
  }
  fout << "+-----------+-----------+-----------+-----------+\n";

  fout.close();
};

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
  
  
  char choice;
  std::cin >> choice;
  choice=static_cast<int>(choice);
  switch (choice) {
    case 110:// corrisponde al char n(no)
      print(a);
      break;

    case 97://corrisponde al char a (all)
      print(a);
      print_on_file(a);
      break;

    case 121://corrisponde al char y (yes)
      print_on_file(a);
      break;

    default:
      print(a);
      print_on_file(a);
      break;
  }
}