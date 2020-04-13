#include <catch.hpp>
#include <string>
#include "CircleGame.hpp"

#define CATCH_CONFIG_MAIN

TEST_CASE("CircleGame - 01")
{
    std::string str("AQK262362TKKAQ6262437892KTTJA332");
    int correct_value = 24;

    CircleGame cg;
    REQUIRE(correct_value == cg.cardsLeft(str));
}