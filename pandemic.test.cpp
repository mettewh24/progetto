#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#include "pandemic.hpp"
#include "pandemic.prova1.hpp"

#include "doctest.h"

TEST_CASE("Testing") {
  SUBCASE("testing evolve simple") {
    World_state s0{99,1,0,1,1,100};
    /*s0.S = 99;
    s0.I = 1;
    s0.R = 0;
    s0.beta = 1;
    s0.gamma = 1;
    s0.N = 100;*/

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

    SUBCASE("testing evolve 2") {
    World_state s00{145050,5000,0,0.5,0.6,150050};

    World_state s01{142633,4417,3000,0.5,0.6,150050};

    World_state s02{140534,3866,5650,0.5,0.6,150050};

    World_state s03{138724,3357,7969,0.5,0.6,150050};

    World_state s04{137172,2894,9984,0.5,0.6,150050};

    World_state s05{135849,2481,11720,0.5,0.6,150050};


    Pandemic test00(s00, 1);
    auto b = evolve(test00.get_state(),test00.get_duration());
    b[1]=approx(b[1]);

    CHECK(b[1] == s01);
    
    Pandemic test01(s00, 2);
    auto c = evolve(test01.get_state(),test01.get_duration());
    c[2]=approx(c[2]);

    CHECK(c[2] == s02);

    Pandemic test02(s00, 3);
    auto d = evolve(test02.get_state(),test02.get_duration());
    d[3]=approx(d[3]);
    
    CHECK(d[3] == s03);

    Pandemic test03(s00, 4);
    auto e = evolve(test03.get_state(),test03.get_duration());
    e[4]=approx(e[4]);
    
    CHECK(e[4] == s04);

    Pandemic test04(s00, 5);
    auto f = evolve(test04.get_state(),test04.get_duration());
    f[5]=approx(f[5]);
    
    CHECK(f[5] == s05); 

  }

  SUBCASE("testing evolve 3"){ //Higher numbers and days

  World_state s000{100000001,950000,35,0.7777,0.9345,100950036};
  World_state s010{96465463,129566,4355007,0.7777,0.9345,100950036};
  World_state s062{95967882,2,4982152,0.7777,0.9345,100950036};
  World_state s115{95967876,0,4982160,0.7777,0.9345,100950036};
  World_state s999{95967876,0,4982160,0.7777,0.9345,100950036};

  Pandemic test010(s000, 10);
    auto g = evolve(test010.get_state(),test010.get_duration());
    g[10]=approx(g[10]);
    
    CHECK(g[10] == s010);

  Pandemic test062(s000, 62);
    auto h = evolve(test062.get_state(),test062.get_duration());
    h[62]=approx(h[62]);
    
    CHECK(h[62] == s062);

    Pandemic test115(s062, 53);
    auto l = evolve(test115.get_state(),test115.get_duration());
    l[53]=approx(l[53]);
    
    CHECK(l[53] == s115);

    Pandemic test999(s000, 999);
    auto m = evolve(test999.get_state(),test999.get_duration());
    m[999]=approx(m[999]);
    
    CHECK(m[999] == s999);

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