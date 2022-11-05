#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "D:/doctest.h"

#include "queueWith2Stacks.hpp"

TEST_CASE("Test default constructor")
{
    QueueWith2Stacks<int> q;
    CHECK(q.empty());
}

TEST_CASE("Test enqueue") 
{
    QueueWith2Stacks<int> q;
    q.enqueue(42);
    CHECK_FALSE(q.empty());
}

TEST_CASE("Removing items in the oder they were added") 
{
    QueueWith2Stacks<int> q;
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
