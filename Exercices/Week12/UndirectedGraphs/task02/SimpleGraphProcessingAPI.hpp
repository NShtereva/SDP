#ifndef __SIMPLE_GRAPH_PROCESSING_API_HPP
#define __SIMPLE_GRAPH_PROCESSING_API_HPP

#include "../task01/undirectedGraph.hpp"

template <typename V>
class SimpleGraphProcessingAPI
{
    public:
        SimpleGraphProcessingAPI() = delete;

        static int degree(const UndirectedGraph<V>& G, const V& v);
        static int maxDegree(const UndirectedGraph<V>& G);
        static double avgDegree(const UndirectedGraph<V>& G);
        static int numberOfSelfLoops(const UndirectedGraph<V>& G);
};

template <typename V>
int SimpleGraphProcessingAPI<V>::degree(const UndirectedGraph<V>& G, const V& v)
{
    return G.degree(v);
}

template <typename V>
int SimpleGraphProcessingAPI<V>::maxDegree(const UndirectedGraph<V>& G)
{
    int maxDeg = 0;

    for(const V& v : G.vertices())
        maxDeg = std::max(maxDeg, G.degree(v));

    return maxDeg;
}

template <typename V>
double SimpleGraphProcessingAPI<V>::avgDegree(const UndirectedGraph<V>& G)
{
    double sum = 0;
    std::vector<V> vertices = G.vertices();

    for(const V& v : vertices)
        sum += G.degree(v);
    
    return sum / vertices.size();
}

template <typename V>
int SimpleGraphProcessingAPI<V>::numberOfSelfLoops(const UndirectedGraph<V>& G)
{
    int counter = 0;
    for(const V& v : G.vertices())
    {
        for(const V& u : G.successors(v))
        {
            if(v == u)
            {
                counter++;
                break;
            }
        }
    }
    return counter;
}

#endif
