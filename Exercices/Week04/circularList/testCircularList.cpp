#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "D:/doctest.h"

#include "circularList.hpp"

TEST_CASE("Test default constructor")
{
    CircularList<int> l;
    CHECK(l.empty());
}

TEST_CASE("Test copy constructor")
{
    CircularList<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);

    CircularList<int> l2(l1);

    l1.pop_front();
    l1.pop_front();
    l1.pop_front();
    CHECK(l1.empty());

    CHECK(!l2.empty());
    CHECK_EQ(l2.size(), 3);
    CHECK_EQ(l2.front(), 1);
    CHECK_EQ(l2.back(), 3);
}

TEST_CASE("Test pop_front")
{
    CircularList<int> l;
    CHECK_THROWS(l.pop_front());

    l.push_back(1);
    l.push_back(2);
    l.pop_front();

    CHECK_EQ(l.front(), 2);
}

TEST_CASE("Test operator *")
{
    CircularList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    int i = 1;

    CircularList<int>::Iterator it = l.begin();
    for(; it != l.end(); ++it)
    {
        CHECK_EQ(*it, i);
        i++;
    }
    CHECK_EQ(*it, i);
}

TEST_CASE("Test insertAfter")
{
    CircularList<int> l;
    l.push_back(1);
    l.push_back(3);

    CircularList<int>::Iterator it = l.begin();
    l.insertAfter(it, 2);

    CHECK_EQ(*it, 1);
    it++;
    CHECK_EQ(*it, 2);
    it++;
    CHECK_EQ(*it, 3);
    it++;
}

TEST_CASE("Test removeAfter")
{
    CircularList<int> l;
    l.push_back(1);
    l.push_back(3);

    CircularList<int>::Iterator it = l.begin();
    l.removeAfter(it);

    CHECK_EQ(*it, 1);
    CHECK_EQ(l.size(), 1);
}
