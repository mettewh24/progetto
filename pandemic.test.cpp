#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "pandemic.hpp"

#include "doctest.h"

TEST_CASE("Testing evolve") {
  SUBCASE("testing evolve") {
    World_state s0{};
    s0.S = 99;
    s0.I = 1;
    s0.R = 0;
    s0.N = 100;
    s0.gamma = 1;
    s0.beta = 1;

    World_state s1{};
    s1.S = round(98.01);
    s1.I = round(0.99);
    s1.R = 1;
    s1.N = 100;
    s1.gamma = 1;
    s1.beta = 1;

    Pandemic test0(s0, 1);
    auto a = test0.evolve();

    CHECK(a.back() == s1);  // devo definire l'operatore == per due World state
    CHECK(a.back().S == s1.S);
    CHECK(a.back().N == s1.N);
    CHECK(a.back().I == s1.I);
    CHECK(a.back().R == s1.R);
    CHECK(a.back().gamma == s1.gamma);
    CHECK(a.back().beta == s1.beta);
  }

  SUBCASE("testing asserts") {
    World_state s0{};
    s0.S = 0;
    s0.I = 0;
    s0.R = 0;
    s0.N = 0;
    s0.gamma = -1;
    s0.beta = -100;

    World_state s1{};
    s1.S = 1;
    s1.I = -1;
    s1.R = 100;
    s1.N = 100;
    s1.gamma = 1;
    s1.beta = 1;

    Pandemic test0(s0, 1);

    Pandemic test1(s1, 1);
  }
}