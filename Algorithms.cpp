// 214984932 Oriyas.07@gmail.com

#include <iostream>
#include "Graph.hpp"
#include "Algorithms.hpp"
namespace ariel
{
    bool isConnected(Graph g)
    {
        for (int i = 0; i < g.getSize(); i++)
        {
            for (int j = 0; j < g.getSize(); j++)
            {
                if (i != j && g.at(i).at(j) == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }
    string shortestPath(Graph g, int start, int end)
    {
    }
    bool isContainsCycle(Graph g)
    {
    }
    string isBipartite(Graph g)
    {
    }
    string negativeCycle(Graph g)
    {
    }
}
