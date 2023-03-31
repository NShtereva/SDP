#ifndef __DFS_BFS_Paths_HPP
#define __DFS_BFS_Paths_HPP

#include "../task01/undirectedGraph.hpp"

#include <deque>

template <typename V>
class Paths
{
    private:
        UndirectedGraph<V> graph;
        V from;

        void dfsRecHelper(const V& curr, std::vector<V>& visited) const;
        std::vector<V> dfsRec() const;

        std::vector<V> dfsIter() const;

        std::vector<V> bfs() const;

    public:
        Paths(const UndirectedGraph<V>& G, const V& from);

        std::vector<V> dfsRecPath(const V& to) const;
        bool hasDFSRecPath(const V& to) const;

        std::vector<V> dfsIterPath(const V& to) const;
        bool hasDFSIterPath(const V& to) const;

        std::vector<V> bfsPath(const V& to) const;
        bool hasBFSPath(const V& to) const;
};

template <typename V>
Paths<V>::Paths(const UndirectedGraph<V>& G, const V& from) 
    : graph(G), from(from)
{ }

template <typename V>
void Paths<V>::dfsRecHelper(const V& curr, std::vector<V>& visited) const
{
    visited.push_back(curr);

    for(int v : this->graph.successors(curr))
    {
        bool found = false;

        for(int u : visited)
        {
            if(v == u)
            {
                found = true;
                break;
            }
        }

        if(!found)
            this->dfsRecHelper(v, visited);
    }
}

template <typename V>
std::vector<V> Paths<V>::dfsRec() const
{
    std::vector<V> result;
    this->dfsRecHelper(this->from, result);
    return result;
}

template <typename V>
std::vector<V> Paths<V>::dfsRecPath(const V& to) const
{
    std::vector<V> dfs = this->dfsRec();
    std::vector<V> result;

    for(const V& v : dfs)
    {
        result.push_back(v);

        if(v == to)
            break;
    }

    if(result.back() != to)
        return std::vector<V>();

    return result;
}

template <typename V>
bool Paths<V>::hasDFSRecPath(const V& to) const
{
    std::vector<V> path = this->dfsRecPath(to);
    return path.size() > 0;
}

template <typename V>
std::vector<V> Paths<V>::dfsIter() const
{
    std::vector<V> visited;

    std::deque<V> q;
    q.push_back(this->from);

    while(!q.empty())
    {
        visited.push_back(q.front());
        AdjList<V> l = this->graph.successors(q.front());
        q.pop_front();

        int i = 0;
        for(const V& v : l)
        {
            bool found = false;

            for(const V& u : visited)
            {
                if(v == u)
                {
                    found = true;
                    break;
                }
            }

            if(!found)
            {
                found = false;

                for(const V& u : q)
                {
                    if(v == u)
                    {
                        found = true;
                        break;
                    }
                }

                if(i == 0 && !found) 
                {
                    q.push_front(v);
                }
                else if(i != 0 && !found) 
                {
                    q.push_back(v);
                }
            }

            i++;
        }
    }

    return visited;
}

template <typename V>
std::vector<V> Paths<V>::dfsIterPath(const V& to) const
{
    std::vector<V> dfs = this->dfsIter();
    std::vector<V> result;

    for(const V& v : dfs)
    {
        result.push_back(v);

        if(v == to)
            break;
    }

    if(result.back() != to)
        return std::vector<V>();

    return result;
}

template <typename V>
bool Paths<V>::hasDFSIterPath(const V& to) const
{
    std::vector<V> path = this->dfsIterPath(to);
    return path.size() > 0;
}

template <typename V>
std::vector<V> Paths<V>::bfs() const
{
    std::vector<V> visited;

    std::deque<V> q;
    q.push_back(this->from);

    while(!q.empty())
    {
        visited.push_back(q.front());
        AdjList<V> l = this->graph.successors(q.front());
        q.pop_front();

        for(const V& v : l)
        {
            bool found = false;

            for(const V& u : visited)
            {
                if(v == u)
                {
                    found = true;
                    break;
                }
            }

            if(!found)
            {
                found = false;

                for(const V& u : q)
                {
                    if(v == u)
                    {
                        found = true;
                        break;
                    }
                }

                if(!found) 
                {
                    q.push_back(v);
                }
            }
        }
    }

    return visited;
}

template <typename V>
std::vector<V> Paths<V>::bfsPath(const V& to) const
{
    std::vector<V> bfs = this->bfs();
    std::vector<V> result;

    for(const V& v : bfs)
    {
        result.push_back(v);

        if(v == to)
            break;
    }

    if(result.back() != to)
        return std::vector<V>();

    return result;
}

template <typename V>
bool Paths<V>::hasBFSPath(const V& to) const
{
    std::vector<V> path = this->bfsPath(to);
    return path.size() > 0;
}

#endif
