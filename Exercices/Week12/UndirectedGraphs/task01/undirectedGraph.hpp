#ifndef __DIRECTED_GRAPH_HPP
#define __DIRECTED_GRAPH_HPP

#include "../../graph.hpp"

template <typename V>
class UndirectedGraph : public Graph<V>
{
    public:
        UndirectedGraph() = default;

        bool addEdge(const V& v, const V& u);
        bool removeEdge(const V& v, const V& u);

        int degree(const V& v) const;

        void DOTprint(std::ostream& out = std::cout) const;
};

template <typename V>
bool UndirectedGraph<V>::addEdge(const V& v, const V& u)
{
    unsigned int count = 0;
    for(std::pair<V, AdjList<V>>& p : this->adjacencyLists)
    {
        if(p.first == v)
        {
            for(const V& curr : p.second)
            {
                if(curr == u)
                    return false;
            }

            p.second.push_front(u);
            count++;
        }
        else if(p.first == u)
        {
            for(const V& curr : p.second)
            {
                if(curr == v)
                    return false;
            }

            p.second.push_front(v);
            count++;
        }
    }
    return count == 2;
}

template <typename V>
bool UndirectedGraph<V>::removeEdge(const V& v, const V& u)
{
    unsigned int count = 0;
    for(std::pair<V, AdjList<V>>& p : this->adjacencyLists)
    {
        if(p.first == v)
        {
            typename AdjList<V>::iterator prev = p.second.before_begin();
            typename AdjList<V>::iterator it = p.second.begin();

            for(; it != p.second.end(); ++it, ++prev)
            {
                if(*it == u)
                {
                    p.second.erase_after(prev);
                    count++;
                    break;
                }
            }
        }
        else if(p.first == u)
        {
            typename AdjList<V>::iterator prev = p.second.before_begin();
            typename AdjList<V>::iterator it = p.second.begin();

            for(; it != p.second.end(); ++it, ++prev)
            {
                if(*it == v)
                {
                    p.second.erase_after(prev);
                    count++;
                    break;
                }
            }
        }
    }
    return count == 2;
}

template <typename V>
int UndirectedGraph<V>::degree(const V& v) const
{
    unsigned int count = 0;
    for(const std::pair<V, AdjList<V>>& p : this->adjacencyLists)
    {
        if(p.first == v)
        {
            typename AdjList<V>::const_iterator it = p.second.begin();
            for(; it != p.second.end(); ++it)
            {
                count++;
            }
            return count;
        }
    }
    return -1;
}

template <typename V>
void UndirectedGraph<V>::DOTprint(std::ostream& out) const
{
    out << "graph {" << std::endl;
    for(const std::pair<V, AdjList<V>>& p : this->adjacencyLists)
    {
        for(const V& v : p.second)
        {
            if(p.first < v)
                out << p.first << " -- " << v << ';' << std::endl;
        } 
    }
    out << "}" << std::endl;
}

#endif
