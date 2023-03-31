#include <iostream>
#include <cassert>

#include "connectedComponent.hpp"

int main()
{
    UndirectedGraph<int> g;

    for(int v = 1; v <= 8; v++)
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
    g.addEdge(7, 8);

    ConnectedComponent<int> cc(g);
    assert(cc.getCount() == 2);
    assert(cc.isConnected(1, 2));
    assert(cc.isConnected(2, 3));
    assert(cc.isConnected(3, 4));
    assert(cc.isConnected(4, 5));
    assert(cc.isConnected(5, 6));
    assert(!cc.isConnected(6, 7));
    assert(cc.isConnected(7, 8));
    assert(!cc.isConnected(8, 1));
    return 0;
}
