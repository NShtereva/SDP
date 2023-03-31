#ifndef __CONNECTED_COMPONENT_HPP
#define __CONNECTED_COMPONENT_HPP

#include "../task01/undirectedGraph.hpp"

#include <vector>
#include <stdexcept>

template <typename V>
class ConnectedComponent
{
private:
    std::vector<V> vertices;
    std::vector<bool> visited;
    std::vector<int> component;
    int currComponent;

    int findIndex(const V& v) const;
    void dfs(const UndirectedGraph<V>& G, const V& v);

public:
    ConnectedComponent(const UndirectedGraph<V>& G);

    size_t getCount() const;
    bool isConnected(const V& v, const V& u) const;
};

template <typename V>
ConnectedComponent<V>::ConnectedComponent(const UndirectedGraph<V>& G)
    : vertices(G.vertices()), visited(std::vector<bool>(G.numberOfVertices(), false)), component(std::vector<int>(G.numberOfVertices())), currComponent(0)
{
    for(int i = 0; i < this->vertices.size(); i++)
    {
        this->component[i] = i;
    }

    for(const V& v : this->vertices)
    {
        int vIndex = this->findIndex(v);
        if(!this->visited[vIndex])
        {
            this->dfs(G, v);
            this->currComponent++;
        }
    }
}

template <typename V>
size_t ConnectedComponent<V>::getCount() const
{
    return this->currComponent;
}

template <typename V>
bool ConnectedComponent<V>::isConnected(const V& v, const V& u) const
{
    int vIndex = this->findIndex(v);
    int uIndex = this->findIndex(u);

    if(vIndex == -1 || uIndex == -1)
        throw std::logic_error("Invalid vertices!");

    return this->component[vIndex] == this->component[uIndex];
}

template <typename V>
int ConnectedComponent<V>::findIndex(const V& v) const
{
    for(int i = 0; i < this->vertices.size(); i++)
    {
        if(this->vertices[i] == v)
            return i;
    }
    return -1;
}

template <typename V>
void ConnectedComponent<V>::dfs(const UndirectedGraph<V>& G, const V& v)
{
    int vIndex = this->findIndex(v);
    this->visited[vIndex] = true;
    this->component[vIndex] = this->currComponent;

    for(const V& u : G.successors(v))
    {
        int uIndex = this->findIndex(u);

        if(!this->visited[uIndex])
            this->dfs(G, u);
    }
}

#endif
