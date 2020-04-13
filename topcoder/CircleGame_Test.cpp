#include <string>
#include "CircleGame.hpp"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("CircleGame - 01")
{
    std::string str("");
    int correct_value = 0;

    SECTION("0")
    {
    str="KKKKKKKKKK";
    correct_value=0;
    }
    SECTION("1")
    {
    str="KKKKKAQT23";
    correct_value=1;
    }
    SECTION("2")
    {
    str="KKKKATQ23J";
    correct_value=6;
    }
    SECTION("3")
    {
    str="AT68482AK6875QJ5K9573Q";
    correct_value=4;
    }
    SECTION("4")
    {
    str="AQK262362TKKAQ6262437892KTTJA332";
    correct_value=24;
    }
    SECTION("5")
    {
    str="KTQ55662JJ3KAAKK2235QKKAK253525KKJKKT";
    correct_value=22;
    }
    SECTION("6")
    {
    str="J92J43KT5T879QA2QK3";
    correct_value=9;
    }
    SECTION("7")
    {
    str="7879J4JQK24Q46K2A3TQ7T4256632TQ738JA6KA8K959J5T895";
    correct_value=42;
    }
    SECTION("8")
    {
    str="A8929JTAQ6J247759TKK5K3K947JQA284Q4256Q36587T6833A";
    correct_value=30;
    }
    SECTION("9")
    {
    str="AJJTKK29T883J2JJT9329JAJJTJKK2JTJKQQ88TJ2A";
    correct_value=31;
    }
    SECTION("10")
    {
    str="AT26532AQJT87J3Q";
    correct_value=0;
    }
    SECTION("11")
    {
    str="AKKKQAATT8AAAQ9A9ATQ";
    correct_value=11;
    }
    SECTION("12")
    {
    str="26834658972634985629856986587465872987369535";
    correct_value=28;
    }
    SECTION("13")
    {
    str="AQKTQKATQAKTKTQTQTAKTQKATQKATQ";
    correct_value=13;
    }
    SECTION("14")
    {
    str="A23456789TJQA23456789TJQ";
    correct_value=0;
    }
    SECTION("15")
    {
    str="553553553553";
    correct_value=12;
    }
    SECTION("16")
    {
    str="AQTKKKKKKQ";
    correct_value=2;
    }
    SECTION("17")
    {
    str="TTTTTTTTTTT3TTT3";
    correct_value=12;
    }
    SECTION("18")
    {
    str="4454454454";
    correct_value=10;
    }
    SECTION("19")
    {
    str="AKKKKKKKKKT3JJ";
    correct_value=3;
    }

    CircleGame cg;
    REQUIRE(correct_value == cg.cardsLeft(str));
}