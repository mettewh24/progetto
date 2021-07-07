#ifndef PANDEMIC_PROVA1_HPP
#define PANDEMIC_PROVA1_HPP

#include <cassert>
#include <cmath>
#include <stdexcept>
#include <vector>

struct World_state {
  double S;
  double I;
  double R;
  double beta;
  double gamma;
  int N;
};

World_state approx(World_state&);

bool operator==(World_state const& l, World_state const& r);

class Pandemic {
  World_state p_initial_state;
  int p_duration_in_days;  // in days

 public:
  Pandemic(World_state const& initial_state, int duration_in_days)
      : p_initial_state{initial_state}, p_duration_in_days{duration_in_days} {
    if (initial_state.beta < 0 || initial_state.beta > 1) {
      throw std::runtime_error("Invalid beta value");
    };
    if (initial_state.gamma < 0 || initial_state.gamma > 1) {
      throw std::runtime_error("Invalid gamma value");
    };
    if (initial_state.N <= 0) {
      throw std::runtime_error("Invalid N value");
    };
    if (initial_state.S < 0) {
      throw std::runtime_error("Invalid S value");
    };
    if (initial_state.I < 0) {
      throw std::runtime_error("Invalid I value");
    };
    if (initial_state.R < 0) {
      throw std::runtime_error("Invalid R value");
    };
    if (initial_state.S + initial_state.I + initial_state.R !=
        initial_state.N) {
      throw std::runtime_error(
          "Sum of S,I,R doesn't match total number of people");
    };
    if (duration_in_days < 0) {
      throw std::runtime_error("Invalid time duration");
    };
  }

  World_state const& get_state();
  //World_state get_state(){
    //return p_initial_state;
  //}
  int const get_duration(){
    return p_duration_in_days;
  }
};
std::vector<World_state> const evolve(World_state const&, int);
World_state const next(World_state const&);
#endif