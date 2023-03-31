#include <iostream>
#include <cassert>

#include "cycle.hpp"

int main()
{
    DirectedGraph<int> g1;

    for(int v = 1; v <= 6; v++)
    {
       g1.addVertex(v);
    }

    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.addEdge(1, 3);
    g1.addEdge(3, 4);
    g1.addEdge(5, 4);
    g1.addEdge(3, 5);
    g1.addEdge(5, 2);
    g1.addEdge(5, 6);
    g1.addEdge(6, 2);

    Cycle<int> c1(g1);
    assert(c1.isCyclic());

    DirectedGraph<int> g2;

    for(int v = 1; v <= 6; v++)
    {
       g2.addVertex(v);
    }

    g2.addEdge(6, 4);
    g2.addEdge(4, 3);
    g2.addEdge(4, 5);
    g2.addEdge(3, 2);
    g2.addEdge(5, 1);
    g2.addEdge(5, 2);
    g2.addEdge(2, 1);

    Cycle<int> c2(g2);
    assert(!c2.isCyclic());
    return 0;
}
