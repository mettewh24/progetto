#include <algorithm>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "pandemic.hpp"

// MAIN TROPPO INCASINATO, NON SI CAPISCE COSA SI DEVE INSERIRE A TERMINALE,
// MEGLIO FAR STAMPARE QUALCHE COSA PER GUIDARE ALL'INSERIMENTO DEI CARATTERI E
// DEI VARI NUMERI CHE SONO NECESSARI

int number_of_digits(int const number) {
  int i = 1;
  int N = number;
  for (; N / 10 >= 1; ++i) {
    N = N / 10;
  }
  return i;
}  // sostituisci con qualcosa da algorithm per trovare la lunghezza di un
   // numero, non saprei però guidarti su cosa

namespace print {
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
}  // namespace print

namespace print_on_file {
void print_on_file(std::vector<World_state> const& state) {
  int max_lenght =
      std::max(number_of_digits(state[0].N), number_of_digits(state.size()));
  if (max_lenght < 5) {
    max_lenght = 5;
  }
  if (max_lenght % 2 == 0) {
    ++max_lenght;
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
  std::ofstream ostrm(
      "pandemic.txt");  // if file already exists, it's overwritten
  ostrm << bar << '\n' << legend << '\n' << bar << '\n';
  int size = state.size();
  for (int i = 0; i < size; ++i) {
    ostrm << "| " << std::setw(max_lenght) << i << " | "
          << std::setw(max_lenght) << state[i].S << " | "
          << std::setw(max_lenght) << state[i].I << " | "
          << std::setw(max_lenght) << state[i].R << " | "
          << std::setw(max_lenght) << state[i].S + state[i].I + state[i].R
          << " | " << std::setw(max_lenght) << state[i].beta << " | "
          << std::setw(max_lenght) << state[i].gamma << " | " << '\n';
  }
  ostrm << bar << "\n";

  ostrm.close();
}
}  // namespace print_on_file

void out(std::vector<World_state> const& states) {
  char choice_2;
  std::cin >> choice_2;
  switch (choice_2) {
    case 'n':  // print on terminal
      print::print(states);
      break;

    case 'a':  // print both on file and on terminal
      print::print(states);
      print_on_file::print_on_file(states);
      break;

    case 'y':  // print on file
      print_on_file::print_on_file(states);
      break;

    default:  // if char is wrong, print both on file and on terminal
      std::cerr << "Invalid char" << '\n';
      print::print(states);
      print_on_file::print_on_file(states);
      break;
  }
}

int main() {
  World_state initial_state;
  int duration_in_days;

  char choice_1;
  std::cin >> choice_1;
  std::ifstream istrm(
      "data.txt");  // Ha avuto da ridire che il programma cerca comunque di
                    // apire il file anche se uno sceglie la lettura da
                    // terminale, ma non so sincermante come risolvere
  if (!istrm.is_open() && choice_1 == 'y') {
    std::cerr << "failed to open data.txt" << '\n';
    choice_1 =
        'n';  // goes on, but now its necessary to read data from terminal
  }

  auto giorgio = [&]() -> std::istream& {
    if (choice_1 == 'n') {
      return std::cin;

    } else {
      return istrm;
    }
  };  // Giaco voleva un oggetto che puntasse alternativamente a cin o a
      // ifstream, per leggere rispettivamente da terminale o da file, è stato
      // fatto all'orale sfruttando qualcosa che non ho capito sull'ereditarietà
      // virtuale(sia cin che ifstrea discendono da istream)
      // NOTA TROVA NOME DECENTE, IO AVEVO FRETTA E NON MI ANDAVA DI PENSARCI

  std::istream& is = giorgio();

  is >> duration_in_days;
  switch (choice_1) {
    case 'n':  // read from terminal
      is >> duration_in_days >> initial_state.N >> initial_state.S >>
          initial_state.I >> initial_state.R >> initial_state.beta >>
          initial_state.gamma;
      break;
    case 'y':  // read from file
      is >> duration_in_days >> initial_state.N >> initial_state.S >>
          initial_state.I >> initial_state.R >> initial_state.beta >>
          initial_state.gamma;
      break;

    default:  // if char is wrong, read from terminal
      std::cerr << "Invalid char, insert data:" << '\n';
      std::cin >> duration_in_days >> initial_state.N >> initial_state.S >>
          initial_state.I >> initial_state.R >> initial_state.beta >>
          initial_state.gamma;  // lettura da input dei paramentri dell'epidemia
      break;
  }

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
  out(a);

  auto past_simulation = a;
  char choice;
  std::cin >> choice;
  for (; choice == 'y' && std::cin.good();) {
    if (choice == 'y') {
      int start;
      int new_duration_in_days;
      double beta;
      double gamma;
      std::cin >> start >> new_duration_in_days >> beta >> gamma;

      past_simulation =
          modify(past_simulation, start, new_duration_in_days, beta, gamma);
      for (int i = 0; i < static_cast<int>(past_simulation.size()); ++i) {
        past_simulation[i] = approx(past_simulation[i]);
        assert(past_simulation[i].S + past_simulation[i].I +
                   past_simulation[i].R - past_simulation[i].N ==
               0);
      }
      out(past_simulation);
      std::cin >> choice;
    } else {
    }
  }
}

// COMMENTO GENERALE
// Alla fine più che sulla correttezza del programma(che mi pare di capire che
// tutto sommato simulasse bene l'epidemia), il prof ha avuto da ridire molto su
// fatti di ottimizzazione poco intelligente