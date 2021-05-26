#include <iostream>
#include"pandemic.prova1.hpp"
//#include"pandemic.hpp"

void print();



int main() {
  World_state initial_state;
  int duration_in_days;
  std::cin >> duration_in_days >>
      initial_state.N;                                                 // lettura da input di durata e grandezza della popolazione
  std::cin >> initial_state.S >> initial_state.I >>initial_state.R;    // lettura da input della ripartizione della popolazione
  std::cin>> initial_state.beta>>initial_state.gamma; //lettura da input dei paramentri dell'epidemia

  Pandemic sir{initial_state,duration_in_days};
  auto a=sir.evolve();
  for (int i=0;i<duration_in_days;++i){
      std::cout<<a[i].S<<'\n'<<a[i].I<<'\n'<<a[i].R<<'\n'<<'\n';
  }
  
}