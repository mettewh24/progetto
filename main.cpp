#include <fstream>
#include <iomanip>
#include <iostream>

#include "pandemic.prova1.hpp"
//#include"pandemic.hpp"

void print(std::vector<World_state> const& state) {
  std::cout << "+-----------+-----------+-----------+-----------+-----------+\n"
               "|    Day    |     S     |     I     |     R     |     N     |\n"
               "+-----------+-----------+-----------+-----------+-----------+\n"
            << std::fixed;
  int size = state.size();
  for (int i = 0; i < size; ++i) {
    std::cout << std::setprecision(0) << "| " << std::setw(9) << i  << " | "
              << std::setw(9) << state[i].S << " | " << std::setw(9)
              << state[i].I << " | " << std::setw(9) << state[i].R << " | "
              << std::setw(9) << state[i].N << " |\n";
  }
  std::cout << "+-----------+-----------+-----------+-----------+-----------+\n"
            << state.size();
}

void print_on_file(std::vector<World_state> const& state) {
  std::ofstream ostrm("pandemic.txt");
  ostrm << "+-----------+-----------+-----------+-----------+-----------+\n"
           "|    Day    |     S     |     I     |     R     |     N     |\n"
           "+-----------+-----------+-----------+-----------+-----------+\n"
        << std::fixed;
  int size = state.size();
  for (int i = 0; i < size; ++i) {
    ostrm << std::setprecision(0) << "| " << std::setw(9) << i + 1 << " | "
          << std::setw(9) << state[i].S << " | " << std::setw(9) << state[i].I
          << " | " << std::setw(9) << state[i].R << " | " << std::setw(9)
          << state[i].N << " |\n";
  }
  ostrm << "+-----------+-----------+-----------+-----------+-----------+\n";

  ostrm.close();
};

int main() {
  World_state initial_state;
  int duration_in_days;

  char choice_1;
  std::cin >> choice_1;
  choice_1 = static_cast<int>(choice_1);
  std::ifstream istrm("data.txt");
  if (!istrm.is_open() && choice_1 == 121) {
    std::cerr << "failed to open data.txt" << '\n';
    choice_1 =
        110;  // il programma va avanti, ma è mandatorio mettere di dati a mano
  }
  switch (choice_1) {
    case 110:  // char n(no) risposta a enable read from file
      std::cin >> duration_in_days >>
          initial_state
              .N;  // lettura da input di durata e grandezza della popolazione
      std::cin >> initial_state.S >> initial_state.I >>
          initial_state
              .R;  // lettura da input della ripartizione della popolazione
      std::cin >> initial_state.beta >>
          initial_state.gamma;  // lettura da input dei paramentri dell'epidemia
      break;
    case 121:  // char y(yes)
      istrm >> duration_in_days >> initial_state.N >> initial_state.S >>
          initial_state.I >> initial_state.R >> initial_state.beta >>
          initial_state.gamma;
      break;

    default:
      std::cin >> duration_in_days >>
          initial_state
              .N;  // lettura da input di durata e grandezza della popolazione
      std::cin >> initial_state.S >> initial_state.I >>
          initial_state
              .R;  // lettura da input della ripartizione della popolazione
      std::cin >> initial_state.beta >>
          initial_state.gamma;  // lettura da input dei paramentri dell'epidemia
      break;
  }

  try {
    Pandemic sir{initial_state, duration_in_days};
  } catch (std::runtime_error const& e) {
    std::cerr << e.what() << '\n';
  };

  Pandemic sir{initial_state, duration_in_days};
  auto a = evolve(sir.get_state(), sir.get_duration());

  char choice_2;
  std::cin >> choice_2;
  choice_2 = static_cast<int>(choice_2);
  switch (choice_2) {
    case 110:  // corrisponde al char n(no)
      print(a);
      break;

    case 97:  // corrisponde al char a (all)
      print(a);
      print_on_file(a);
      break;

    case 121:  // corrisponde al char y (yes)
      print_on_file(a);
      break;

    default:
      print(a);
      print_on_file(a);
      break;
  }
}