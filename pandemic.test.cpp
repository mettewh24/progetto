#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#include "pandemic.hpp"
#include "pandemic.prova1.hpp"

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
    s1.S = 98;
    s1.I = 1;
    s1.R = 1;
    s1.N = 100;
    s1.gamma = 1;
    s1.beta = 1;

    Pandemic test0(s0, 1);
    auto a = evolve(test0.get_state(),test0.get_duration());
    a[1]=approx(a[1]);

    CHECK(a[1] == s1);
    CHECK(a[1].S == s1.S);
    CHECK(a[1].N == s1.N);
    CHECK(a[1].I == s1.I);
    CHECK(a[1].R == s1.R);
    CHECK(a[1].gamma == s1.gamma);
    CHECK(a[1].beta == s1.beta);
  }

  SUBCASE("testing exeptions") {
    World_state s0{};
    s0.S = 0;
    s0.I = 0;
    s0.R = 10;
    s0.N = 10;
    s0.gamma = 5;
    s0.beta = 0;

    World_state s1{};
    s1.S = 1;
    s1.I = 0;
    s1.R = 98;
    s1.N = 100;
    s1.gamma = 1;
    s1.beta = 1;

    Pandemic test0(s0, 1);

    Pandemic test1(s1, 1);
  }
}