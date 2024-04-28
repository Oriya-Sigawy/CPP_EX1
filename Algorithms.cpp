// 214984932 Oriyas.07@gmail.com

#include <iostream>
#include <limits.h>
#include "Graph.hpp"
#include "Algorithms.hpp"
namespace ariel
{
    void traverse(int u, bool *visited, int size)
    {
        visited[u] = true;
        for (int v = 0; v < size; v++)
        {
            if (g[u][v])
            {
                if (!visited[v])
                {
                    traverse(v, visited, g);
                }
            }
        }
    }
    bool isConnected(Graph g)
    {
        bool *visited = new bool[g.getSize()]; // save g.getSize as size instead of calling getSize so much times?
        for (int u = 0; u < g.getSize(); u++)
        {
            for (int i = 0; i < g.getSize(); i++)
            {
                visited[i] = false;
                traverse(u, visited, g.getSize());
            }
            for (int j = 0; j < g.getSize(); j++)
            {
                if (!visited[j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    int minDist(int *dist, bool *sptSet, int size)
    {
        int min = INT_MAX, min_index;

        for (int v = 0; v < size; v++)
        {
            if (sptSet[v] == false && dist[v] <= min)
            {
                min = dist[v], min_index = v;
            }
        }

        return min_index;
    }
    string shortestPath(Graph g, int start, int end)
    {
    }
    string isContainsCycle(Graph g)
    {
    }
    string isBipartite(Graph g)
    {
    }
    string negativeCycle(Graph g)
    {
    }
}
