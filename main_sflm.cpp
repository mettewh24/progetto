#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <cmath>
//#include <SelbaWard/PieChart.hpp>
#include <SFML/OpenGL.hpp>


using namespace std;

#include "pandemic.prova1.hpp"
//#include"pandemic.hpp"

void print(std::vector<World_state> const& state) {
  std::cout << "+-----------+-----------+-----------+-----------+-----------+\n"
               "|    Day    |     S     |     I     |     R     |     N     |\n"
               "+-----------+-----------+-----------+-----------+-----------+\n"
            << std::fixed;
  int size = state.size();
  for (int i = 0; i < size; ++i) {
    std::cout << std::setprecision(0) << "| " << std::setw(9) << i << " | "
              << std::setw(9) << state[i].S << " | " << std::setw(9)
              << state[i].I << " | " << std::setw(9) << state[i].R << " | "
              << std::setw(9) << state[i].S + state[i].I + state[i].R << " |\n";
  }
  std::cout << "+-----------+-----------+-----------+-----------+-----------+\n"
      /*<< state.size()*/;
}

void print_on_file(std::vector<World_state> const& state) {
  std::ofstream ostrm("pandemic.txt");
  ostrm << "+-----------+-----------+-----------+-----------+-----------+\n"
           "|    Day    |     S     |     I     |     R     |     N     |\n"
           "+-----------+-----------+-----------+-----------+-----------+\n"
        << std::fixed;
  int size = state.size();
  for (int i = 0; i < size; ++i) {
    ostrm << std::setprecision(0) << "| " << std::setw(9) << i << " | "
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

  std::ifstream istrm("data.txt");
  if (!istrm.is_open() && choice_1 == 'y') {
    std::cerr << "failed to open data.txt" << '\n';
    choice_1 =
        'n';  // il programma va avanti, ma è mandatorio mettere di dati a mano
  }
  choice_1 = static_cast<int>(choice_1);

  switch (choice_1) {
    case 110:  // char n(no) risposta a enable read from file
      std::cin >> duration_in_days >> initial_state.N >> initial_state.S >>
          initial_state.I >> initial_state.R >> initial_state.beta >>
          initial_state.gamma;  // lettura da input dei paramentri dell'epidemia
      break;
    case 121:  // char y(yes)
      istrm >> duration_in_days >> initial_state.N >> initial_state.S >>
          initial_state.I >> initial_state.R >> initial_state.beta >>
          initial_state.gamma;
      break;

    default:
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
    
    //grafico S asse x e giorni asse y
    sf::RenderWindow window(sf::VideoMode(200, 200), "Graph of S");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    sf::VertexArray chart(sf::LinesStrip, duration_in_days);
    for (unsigned int i = 0; i <= duration_in_days; ++i){
        unsigned int x = i;
        unsigned int y = a[i].S;
        chart.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Blue));
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed) window.close();

        window.clear(sf::Color::Yellow);
        window.draw(chart);
        window.display();
    }
    return 0;


  /*double percentage_S_lastday = state[size-1].S * pow(state[size-1].S + state[size-1].I + state[size-1].R, -1);
  double percentage_I_lastday = state[size-1].I * pow(state[size-1].S + state[size-1].I + state[size-1].R, -1);
  double percentage_R_lastday = state[size-1].R * pow(state[size-1].S + state[size-1].I + state[size-1].R, -1);
    
    sf::RenderWindow window(sf::VideoMode(200, 200), "Pie Chart of the last day");
    sw::PieChart pieChart;
    pieChart.slices.resize(3);
    pieChart.slices[0].color = sf::Color::Red;
    pieChart.slices[1].color = sf::Color::Green;
    pieChart.slices[2].color = sf::Color::Blue;
    pieChart.slices[0].size = (percentage_S_lastday)f; //ma così non funziona, vuole un numero
    pieChart.slices[1].size = (percentage_S_lastday)f;
    pieChart.slices[2].size = (percentage_S_lastday)f;
    pieChart.setSize({ 150.f, 150.f });
    pieChart.update();
    pieChart.setOrigin(pieChart.getSize() / 2.f);
    pieChart.setPosition(window.getView().getCenter());
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(pieChart);
        window.display();
    }
    return EXIT_SUCCESS;*/
}