#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "D:/doctest.h"
#include "undirectedGraph.hpp"

TEST_CASE("Adding vertices and edges in a graph") 
{
    UndirectedGraph<int> g;
    for(int v = 1; v <= 6; v++)
    {
        REQUIRE(g.addVertex(v));
    }
    
    int v = 1;
    for(int u : g.vertices())
    {
        CHECK_EQ(u, v++);
    }

    CHECK_EQ(v, 7);

    REQUIRE(g.addEdge(1, 2));
    REQUIRE(g.addEdge(2, 3));
    REQUIRE(g.addEdge(1, 3));
    REQUIRE(g.addEdge(3, 4));
    REQUIRE(g.addEdge(5, 4));
    REQUIRE(g.addEdge(3, 5));
    REQUIRE(g.addEdge(5, 2));
    REQUIRE(g.addEdge(5, 6));
    REQUIRE(g.addEdge(6, 2));

    std::ofstream out("undirectedGraph.dot");
    g.DOTprint(out);

    CHECK(g.isEdge(1, 3));
    CHECK(g.isEdge(3, 1));
    CHECK(!g.isEdge(1, 4));

    CHECK_EQ(g.degree(1), 2);
    CHECK_EQ(g.degree(2), 4);
    CHECK_EQ(g.degree(9), -1);

    SUBCASE("Remove edges") 
    {
        REQUIRE(g.removeEdge(1, 3));
        CHECK(!g.isEdge(1, 3));
        CHECK(!g.isEdge(3, 1));
        REQUIRE(!g.removeEdge(1, 4));
    }

    SUBCASE("Traversing successors") 
    {
        std::forward_list<int> l = g.successors(1);
        std::forward_list<int>::iterator it = l.begin();
        int s = *it;
        CHECK((s == 2 || s == 3));
        ++it;
        CHECK_EQ(*it, 5 - s);
    }

    SUBCASE("Remove vertices")
    {
        REQUIRE(g.removeVertex(3));

        v = 1;
        for(int u : g.vertices())
        {
            CHECK(u != 3);

            if(v != 3)
                CHECK_EQ(u, v++);
            else
                v += 2;
        }

        CHECK_EQ(v, 7);

        CHECK(!g.isEdge(1, 3));
        CHECK(!g.isEdge(3, 1));
        CHECK(!g.isEdge(2, 3));
        CHECK(!g.isEdge(3, 2));
        CHECK(!g.isEdge(3, 4));
        CHECK(!g.isEdge(4, 3));
        CHECK(!g.isEdge(3, 5));
        CHECK(!g.isEdge(5, 3));
    }
}
