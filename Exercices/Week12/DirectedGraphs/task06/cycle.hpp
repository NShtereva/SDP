#ifndef __CYCLE_HPP
#define __CYCLE_HPP

#include "../task01/directedGraph.hpp"

#include <vector>

template <typename V>
class Cycle
{
    private:
        std::vector<bool> visited;
        std::vector<V> vertices;
        bool cycle;

        int findIndex(const V& v) const;
        void dfs(const DirectedGraph<V>& G, const V& v);

    public:
        Cycle(const DirectedGraph<V>& G);
        bool isCyclic() const;
};

template <typename V>
Cycle<V>::Cycle(const DirectedGraph<V>& G)
    : visited(std::vector<bool>(G.numberOfVertices(), false)), vertices(std::vector<V>(G.vertices())), cycle(false)
{
    for(const V& v : this->vertices)
    {
        this->dfs(G, v);
    }
}

template <typename V>
int Cycle<V>::findIndex(const V& v) const
{
    for(int i = 0; i < this->vertices.size(); i++)
    {
        if(this->vertices[i] == v)
            return i;
    }
    return -1;
}

template <typename V>
void Cycle<V>::dfs(const DirectedGraph<V>& G, const V& v)
{
    int vIndex = this->findIndex(v);
    this->visited[vIndex] = true;

    for(const V& u : G.successors(v))
    {
        int uIndex = this->findIndex(u);

        if(!this->visited[uIndex])
        {
            this->dfs(G, u);
        }
        else
        {
            this->cycle = true;
        }
    }
    this->visited[vIndex] = false;
}

template <typename V>
bool Cycle<V>::isCyclic() const
{
    return this->cycle;
}

#endif
