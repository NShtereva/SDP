#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "D:/doctest.h"
#include "vector.hpp"

TEST_CASE("Test default constructor")
{
    Vector<int> v;

    REQUIRE(v.getSize() == 0);
    REQUIRE(v.getCapacity() == 0);
    REQUIRE(v.empty());
    REQUIRE(!v.data());
}

TEST_CASE("Test constructor with parameters")
{
    Vector<int> v(8);

    REQUIRE(v.getSize() == 8);
    REQUIRE(!v.empty());
}

TEST_CASE("Test resize")
{
    Vector<int> v;
    v.resize(3);

    REQUIRE(v.getSize() == 3);
    REQUIRE(v.getCapacity() == 3);
    REQUIRE(!v.empty());
}

TEST_CASE("Test reserve")
{
    Vector<int> v;
    v.reserve(3);

    REQUIRE(v.getSize() == 0);
    REQUIRE(v.empty());
    REQUIRE(v.getCapacity() == 3);
}

TEST_CASE("Test operator []")
{
    Vector<int> v(8);

    REQUIRE(v[2] == 0);

    v[0] = 9;
    REQUIRE(v[0] == 9);
}

TEST_CASE("Test At")
{
    Vector<int> v(8);

    REQUIRE(v.at(2) == 0);

    v.at(0) = 9;
    REQUIRE(v.at(0) == 9);

    REQUIRE_THROWS_AS(v.at(9), std::out_of_range);
}

TEST_CASE("Test front")
{
    Vector<int> v(8);
    v[0] = 9;

    REQUIRE(v.front() == 9);
}

TEST_CASE("Test back")
{
    Vector<int> v(8);
    v[7] = 3;

    REQUIRE(v.back() == 3);
}

TEST_CASE("Test push_back")
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
}

TEST_CASE("Test pop_back")
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    
    v.pop_back();
    REQUIRE(v.getSize() == 2);

    v.pop_back();
    v.pop_back();
    REQUIRE(v.getSize() == 0);

    v.pop_back();
    REQUIRE(v.getSize() == 0);
}

TEST_CASE("Test begin")
{
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    VectorIterator<int> it = v1.begin();
    REQUIRE(*it == 1);
}

TEST_CASE("Test end")
{
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    VectorIterator<int> it1 = v1.end();
    REQUIRE(*(--it1) == 3);
}
