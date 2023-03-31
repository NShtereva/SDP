#ifndef __TOPOLOGICAL_SORT_HPP
#define __TOPOLOGICAL_SORT_HPP

#include "../task01/directedGraph.hpp"

#include <vector>
#include <queue>
#include <stdexcept>

template <typename V>
class TopologicalSort
{
private:
    std::vector<V> vertices;
    std::vector<bool> visited;
    DirectedGraph<V> graph;
    std::vector<V> result;

    bool hasPredecessor(const DirectedGraph<V>& G, const V& v) const;

    int findIndex(const V& v) const;
    void bfs(const V& v);

public:
    TopologicalSort(const DirectedGraph<V>& G);
    std::vector<V> sorted() const;
};

template <typename V>
TopologicalSort<V>::TopologicalSort(const DirectedGraph<V>& G)
    : vertices(G.vertices()), visited(std::vector<bool>(G.numberOfVertices(), false)), graph(G)
{
    int i = 0;
    for(; i < this->vertices.size(); i++)
    {
        if(!this->hasPredecessor(G, this->vertices[i]))
            break;
    }

    if(i < this->vertices.size())
    {
        this->bfs(this->vertices[i]);
    }
    else
    {
        throw std::logic_error("There is no topological sort because the graph is cyclic!");
    }
}

template <typename V>
bool TopologicalSort<V>::hasPredecessor(const DirectedGraph<V>& G, const V& v) const
{
    int vIndex = this->findIndex(v);
    for(int i = 0; i < this->vertices.size(); i++)
    {
        bool hasPred = false;

        if(i != vIndex)
            hasPred = G.isEdge(this->vertices[i], v);

        if(hasPred)
            return true;
    }
    return false;
}

template <typename V>
int TopologicalSort<V>::findIndex(const V& v) const
{
    for(int i = 0; i < this->vertices.size(); i++)
    {
        if(this->vertices[i] == v)
            return i;
    }
    return -1;
}

template <typename V>
void TopologicalSort<V>::bfs(const V& v)
{
    std::queue<V> q;
    q.push(v);

    while(!q.empty())
    {
        V curr = q.front();
        int currIndex = this->findIndex(curr);
        q.pop();

        if(!this->visited[currIndex] && !this->hasPredecessor(this->graph, curr))
        {
            this->result.push_back(curr);
            this->visited[currIndex] = true;

            for(const V& u : this->graph.successors(curr))
            {
                q.push(u);
            }

            this->graph.removeVertex(curr);
        }
    }
}

template <typename V>
std::vector<V> TopologicalSort<V>::sorted() const
{
    return this->result;
}

#endif
