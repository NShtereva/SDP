#include <cassert>

#include "dfs_bfsPaths.hpp"

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

    Paths<int> p(g, 1);
    
    assert(p.hasDFSRecPath(4));

    // 1 3 5 6 2 4
    for(int v : p.dfsRecPath(4))
    {
        std::cout << v << ' ';
    }
    std::cout << std::endl;

    assert(p.hasDFSIterPath(4));

    // 1 3 5 6 2 4
    for(int v : p.dfsIterPath(4))
    {
        std::cout << v << ' ';
    }
    std::cout << std::endl;

    assert(p.hasBFSPath(6));

    // 1 3 2 5 4 6
    for(int v : p.bfsPath(6))
    {
        std::cout << v << ' ';
    }
    std::cout << std::endl;
    return 0;
}
