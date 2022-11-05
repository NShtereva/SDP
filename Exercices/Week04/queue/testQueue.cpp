#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "D:/doctest.h"

#include "staticQueue.hpp"
#include "linkedQueue.hpp"

TYPE_TO_STRING(StaticQueue<int>);
TYPE_TO_STRING(LinkedQueue<int>);

TEST_CASE_TEMPLATE("Test default constructor", 
                   TestQueue, StaticQueue<int>, LinkedQueue<int>)
{
    TestQueue q;
    CHECK(q.empty());
}

TEST_CASE_TEMPLATE("Test enqueue",
                   TestQueue, StaticQueue<int>, LinkedQueue<int>) 
{
    TestQueue q;
    q.enqueue(42);
    CHECK_FALSE(q.empty());
}

TEST_CASE_TEMPLATE("Throwing an exeption on invalid empty queue operations",
                   TestQueue, StaticQueue<int>, LinkedQueue<int>) 
{
    TestQueue q;
    CHECK_THROWS(q.front());
    CHECK_THROWS(q.dequeue());
}

TEST_CASE_TEMPLATE("Test dequeue",
                    TestQueue, StaticQueue<int>, LinkedQueue<int>) 
{
    TestQueue q;
    for(int i = 1; i <= 10; i++)
    {
        q.enqueue(i);
    }

    CHECK_EQ(q.front(), 1);
    CHECK_EQ(q.dequeue(), 1);
    CHECK_NE(q.front(), 1);
}

TEST_CASE_TEMPLATE("Removing items in the oder they were added",
                    TestQueue, StaticQueue<int>, LinkedQueue<int>) 
{
    TestQueue q;
    for(int i = 1; i <= 10; i++)
    {
        q.enqueue(i);
        CHECK_EQ(q.back(), i);
        
    }

    for(int i = 1; i <= 10; i++)
    {
        CHECK_EQ(q.dequeue(), i);
    }

    CHECK(q.empty());
}
