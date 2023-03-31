#include <iostream>
#include <cassert>

#include "SimpleGraphProcessingAPI.hpp"

int main()
{
    UndirectedGraph<int> g;

    for(int v = 1; v <= 6; v++)
    {
       g.addVertex(v);
    }

    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(5, 4);
    g.addEdge(3, 5);
    g.addEdge(5, 2);
    g.addEdge(5, 6);
    g.addEdge(6, 2);

    assert(SimpleGraphProcessingAPI<int>::degree(g, 1) == 2);
    assert(SimpleGraphProcessingAPI<int>::degree(g, 2) == 4);
    assert(SimpleGraphProcessingAPI<int>::degree(g, 3) == 4);
    assert(SimpleGraphProcessingAPI<int>::degree(g, 4) == 2);
    assert(SimpleGraphProcessingAPI<int>::degree(g, 5) == 4);
    assert(SimpleGraphProcessingAPI<int>::degree(g, 6) == 2);
    assert(SimpleGraphProcessingAPI<int>::degree(g, 9) == -1);

    assert(SimpleGraphProcessingAPI<int>::maxDegree(g) == 4);

    assert(std::abs(SimpleGraphProcessingAPI<int>::avgDegree(g) - 3) == 0);

    assert(SimpleGraphProcessingAPI<int>::numberOfSelfLoops(g) == 0);
    return 0;
}
