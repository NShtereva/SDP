#ifndef __GRAPH_HPP
#define __GRAPH_HPP

#include <iostream>
#include <vector>
#include <forward_list>
#include <utility>

template <typename T>
using AdjList = std::forward_list<T>;

template <typename V>
class Graph
{
    public:
        virtual ~Graph() {}
        
        std::vector<V> vertices() const;
        size_t numberOfVertices() const;

        AdjList<V> successors(const V& v) const;

        bool isEdge(const V& v, const V& u) const;

        bool addVertex(const V& v);
        bool removeVertex(const V& v);

        virtual bool addEdge(const V& v, const V& u) = 0;
        virtual bool removeEdge(const V& v, const V& u) = 0;

        virtual void DOTprint(std::ostream& out = std::cout) const = 0;

    protected:
        std::vector<std::pair<V, AdjList<V>>> adjacencyLists;
};

template <typename V>
std::vector<V> Graph<V>::vertices() const
{
    std::vector<V> result;
    for(const std::pair<V, AdjList<V>>& p : this->adjacencyLists)
    {
        result.push_back(p.first);
    }
    return result;
}

template <typename V>
size_t Graph<V>::numberOfVertices() const
{
    return this->adjacencyLists.size();
}

template <typename V>
AdjList<V> Graph<V>::successors(const V& v) const
{
    for(const std::pair<V, AdjList<V>>& p : this->adjacencyLists)
    {
        if(p.first == v)
            return p.second;
    }
    return AdjList<V>();
}

template <typename V>
bool Graph<V>::isEdge(const V& v, const V& u) const
{
    for(const std::pair<V, AdjList<V>>& p : this->adjacencyLists)
    {
        if(p.first == v)
        {
            for(const V& curr : p.second)
            {
                if(curr == u)
                    return true;
            }
        }
    }
    return false;
}

template <typename V>
bool Graph<V>::addVertex(const V& v)
{
    for(const std::pair<V, AdjList<V>>& p : this->adjacencyLists)
    {
        if(p.first == v)
            return false;
    }

    this->adjacencyLists.push_back(std::make_pair(v, AdjList<V>()));
    return true;
}

template <typename V>
bool Graph<V>::removeVertex(const V& v)
{
    bool found = false;
    typename std::vector<std::pair<V, AdjList<V>>>::iterator it = this->adjacencyLists.begin();

    for(; it != this->adjacencyLists.end(); ++it)
    {
        if((*it).first == v)
        {
            this->adjacencyLists.erase(it);
            found = true;
            --it;
        }
        else
        {
            typename AdjList<V>::iterator prev = (*it).second.before_begin();
            typename AdjList<V>::iterator curr = (*it).second.begin();

            for(; curr != (*it).second.end(); ++curr, ++prev)
            {
                if(*curr == v)
                {
                    (*it).second.erase_after(prev);
                    break;
                }
            }
        }
    }

    return found;
}

#endif
