#include <iostream>

#include "topologicalSort.hpp"

int main()
{
    DirectedGraph<int> g;

    for(int v = 1; v <= 6; v++)
    {
       g.addVertex(v);
    }

    g.addEdge(4, 1);
    g.addEdge(4, 5);
    g.addEdge(1, 2);
    g.addEdge(5, 2);
    g.addEdge(5, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 6);

    TopologicalSort<int> ts(g);     // 4 5 1 2 3 6
    for(int v : ts.sorted())
    {
        std::cout << v << ' ';
    }
    std::cout << std::endl;
    return 0;
}
