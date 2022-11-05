#include <iostream>
#include <cassert>

#include "staticQueue.hpp"
#include "linkedQueue.hpp"

// using Queue = StaticQueue<int>;
using Queue = LinkedQueue<int>;

bool isSorted(Queue& q)
{
    size_t size = q.size();
    if(size == 0 || size == 1)
    {
        return true;
    }

    bool isSorted = true;

    int prev = q.front();
    q.pop();

    while(size > 1)
    {
        int curr = q.front();
        q.pop();

        if(prev > curr)
        {
            isSorted = false;
        }

        q.push(prev);
        prev = curr;

        size--;
    }

    q.push(prev);
    return isSorted;
}

int main()
{
    Queue q1;
    q1.push(1);
    q1.push(2);
    q1.push(9);
    q1.push(15);
    q1.push(43);

    Queue q2;
    q2.push(-3);
    q2.push(16);
    q2.push(9);
    q2.push(0);
    q2.push(13);

    assert(isSorted(q1));
    assert(!isSorted(q2));
    return 0;
}
