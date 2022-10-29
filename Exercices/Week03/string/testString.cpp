#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "D:/doctest.h"
#include "string.hpp"

#include <cstring>

TEST_CASE("Test default constructor")
{
    String s;

    REQUIRE(s.getSize() == 0);
    REQUIRE(s.empty() == true);
    REQUIRE(s.c_str() == nullptr);
}

TEST_CASE("Test constructor with parameters")
{
    String s("ala bala");

    REQUIRE(s.getSize() == 8);
    REQUIRE(s.empty() == false);
    REQUIRE(strcmp(s.c_str(), "ala bala") == 0);
}

TEST_CASE("Test At")
{
    String s("ala bala");

    REQUIRE(s.at(2) == 'a');

    s.at(3) = '_';
    REQUIRE(s.at(3) == '_');
    REQUIRE(strcmp(s.c_str(), "ala_bala") == 0);

    REQUIRE_THROWS_AS(s.at(9), std::out_of_range);
}

TEST_CASE("Test operator []")
{
    String s("ala bala");

    REQUIRE(s[2] == 'a');

    s[3] = '_';
    REQUIRE(s[3] == '_');
    REQUIRE(strcmp(s.c_str(), "ala_bala") == 0);
}

TEST_CASE("Test front")
{
    String s("ala bala");

    REQUIRE(s.front() == 'a');
}

TEST_CASE("Test back")
{
    String s("ala bala");

    REQUIRE(s.back() == 'a');
}

TEST_CASE("Test push_back")
{
    String s("ala_bala");
    s.push_back('_');

    REQUIRE(strcmp(s.c_str(), "ala_bala_") == 0);
}

TEST_CASE("Test pop_back")
{
    String s("ala_bala_");
    s.pop_back();
    
    REQUIRE(strcmp(s.c_str(), "ala_bala") == 0);
}

TEST_CASE("Test operator +=")
{
    String s("ala bala");

    s += ' ';
    REQUIRE(strcmp(s.c_str(), "ala bala ") == 0);
    s += "jakdfhk";
    REQUIRE(strcmp(s.c_str(), "ala bala jakdfhk") == 0);
}

TEST_CASE("Test operator ==")
{
    String s1("ala bala"), s2("123"), s3(s1);

    REQUIRE(s1 == s3);
    REQUIRE_FALSE(s1 == s2);
}

TEST_CASE("Test operator <")
{
    String s1("123"), s2("ala bala");

    REQUIRE(s1 < s2);
}
