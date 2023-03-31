#ifndef __DIRECTED_GRAPH_HPP
#define __DIRECTED_GRAPH_HPP

#include "../../graph.hpp"

template <typename V>
class DirectedGraph : public Graph<V>
{
    public:
        DirectedGraph() = default;

        bool addEdge(const V& v, const V& u);
        bool removeEdge(const V& v, const V& u);

        void DOTprint(std::ostream& out = std::cout) const;
};

template <typename V>
bool DirectedGraph<V>::addEdge(const V& v, const V& u)
{
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
            return true;
        }
    }
    return false;
}

template <typename V>
bool DirectedGraph<V>::removeEdge(const V& v, const V& u)
{
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
                    return true;
                }
            }
        }
    }
    return false;
}

template <typename V>
void DirectedGraph<V>::DOTprint(std::ostream& out) const
{
    out << "digraph {" << std::endl;
    for(const std::pair<V, AdjList<V>>& p : this->adjacencyLists)
    {
        for(const V& v : p.second)
        {
            out << p.first << " -> " << v << ';' << std::endl;
        } 
    }
    out << "}" << std::endl;
}

#endif
