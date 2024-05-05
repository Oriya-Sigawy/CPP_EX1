// 214984932 Oriyas.07@gmail.com
// TODO- check delete
#include <iostream>
#include <limits.h>
#include <string.h>
#include <bits/stdc++.h>
#include <vector>
#include "Graph.hpp"
#include "Algorithms.hpp"
using std::string;
using std::vector;
namespace ariel
{
    // checks strong connectivity
    bool Algorithms::isConnected(Graph g)
    {
        unsigned int vertices = g.getNumOfVertices();
        bool *visited = new bool[vertices];
        for (unsigned int u = 0; u < vertices; u++)
        {
            for (unsigned int i = 0; i < vertices; i++)
            {
                visited[i] = false;
            }
            traverse(u, visited, g);
            for (unsigned int j = 0; j < vertices; j++)
            {
                if (!visited[j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    void Algorithms::traverse(unsigned int u, bool *visited, Graph g)
    {
        visited[u] = true;
        for (unsigned int v = 0; v < g.getNumOfVertices(); v++)
        {
            if (g.getAt(u, v))
            {
                if (!visited[v])
                {
                    traverse(v, visited, g);
                }
            }
        }
    }
    //  Function that implements Dijkstra's single source shortest path algorithm
    // TODO- test with a neg cycle
    vector<unsigned int> Algorithms::shortestPath(Graph g, unsigned int start, unsigned int end)
    {
        unsigned int vertices = g.getNumOfVertices();
        if (start >= vertices || end >= vertices)
        {
            throw std::out_of_range("");
        }
        int dist[vertices];
        unsigned int prev[vertices];
        bool shortestPathSet[vertices];

        for (unsigned int i = 0; i < vertices; i++)
        {
            dist[i] = INT_MAX, shortestPathSet[i] = false, prev[i] = INT_MAX;
        }
        dist[start] = 0;
        for (unsigned int count = 0; count < vertices - 1; count++)
        {
            unsigned int u = minDist(dist, shortestPathSet, vertices);
            shortestPathSet[u] = true;
            for (unsigned int v = 0; v < vertices; v++)
            {
                if (!shortestPathSet[v] && g.getAt(u, v) && dist[u] != INT_MAX && dist[u] + g.getAt(u, v) < dist[v])
                {
                    dist[v] = dist[u] + g.getAt(u, v);
                    prev[v] = u;
                }
            }
        }
        if (dist[end] == INT_MAX)
        {
            return vector<unsigned int>();
        }
        vector<unsigned int> ans;
        unsigned int i = end;
        while (i != start)
        {
            ans.push_back(i);
            i = prev[i];
        }
        ans.push_back(start);
        std::reverse(ans.begin(), ans.end());
        return ans;
    }

    unsigned int Algorithms::minDist(int *dist, bool *shortestPathSet, unsigned int size)
    {
        int min = INT_MAX;
        unsigned int min_index;

        for (unsigned int v = 0; v < size; v++)
        {
            if (shortestPathSet[v] == false && dist[v] <= min)
            {
                min = dist[v], min_index = v;
            }
        }
        return min_index;
    }

    vector<unsigned int> Algorithms::getCycle(Graph g)
    {
        bool directed = g.isDirected();
        // Mark all the vertices as not visited
        // and not part of recursion stack
        unsigned int vertices = g.getNumOfVertices();
        vector<unsigned int> result;
        bool *black = new bool[vertices];
        bool *gray = new bool[vertices];
        unsigned int *parents = new unsigned int[vertices];
        for (unsigned int i = 0; i < vertices; i++)
        {
            black[i] = false;
            gray[i] = false;
            parents[i] = INT_MAX;
        }

        // Call the recursive helper function
        // to detect cycle in different DFS trees
        for (unsigned int i = 0; i < vertices; i++)
        {
            if (!black[i])
            {
                std::array<unsigned int, 2> ans = dfs_visit(directed, i, black, gray, parents, g);
                if (ans[0] != INT_MAX && ans[1] != INT_MAX)
                {
                    unsigned int p = ans[0];
                    while (p != ans[1])
                    {
                        result.push_back(p);
                        p = parents[p];
                    }
                    result.push_back(ans[1]);
                    std::reverse(result.begin(), result.end());
                    return result;
                }
            }
        }
        delete[] black;
        delete[] gray;
        delete[] parents;
        return result;
    }

    std::array<unsigned int, 2> Algorithms::dfs_visit(bool directed, unsigned int v, bool black[], bool *gray, unsigned int parents[], Graph g)
    {
        std::array<unsigned int, 2> ans = {INT_MAX, INT_MAX};
        // Mark the current node as visited
        // and part of recursion stack
        gray[v] = true;

        // Recur for all the vertices adjacent to this
        // vertex
        for (unsigned int i = 0; i < g.getNumOfVertices(); ++i)
        {
            if (g.getAt(v, i) != 0)
            {
                if (gray[i] && (directed || !(i == parents[v])))
                {
                    ans[0] = v;
                    ans[1] = i;
                    return ans;
                }
                else if (!black[i] && !gray[i])
                {
                    parents[i] = v;
                    ans = dfs_visit(directed, i, black, gray, parents, g);
                    if (ans[0] != INT_MAX && ans[1] != INT_MAX)
                    {
                        return ans;
                    }
                }
            }
        }

        // Remove the vertex from recursion stack
        gray[v] = false;
        black[v] = true;
        return ans;
    }

    std::array<vector<unsigned int>, 2> Algorithms::bipartitePartition(Graph g)
    {

        // Create a color array to store colors assigned to all
        // vertices. Vertex/ number is used as index in this
        // array. The value '-1' of colorArr[i] is used to
        // indicate that no color is assigned to vertex 'i'.
        // The value 1 is used to indicate first color is
        // assigned and value 0 indicates second color is
        // assigned.
        std::array<vector<unsigned int>, 2> ans;
        unsigned int vertices = g.getNumOfVertices();
        int colorArr[vertices];
        for (unsigned int i = 0; i < vertices; ++i)
        {
            colorArr[i] = -1;
        }
        for (unsigned int i = 0; i < vertices; i++)
        {
            if (colorArr[i] == -1)
            {
                if (!bipartite(g, i, colorArr))
                {
                    return ans;
                }
            }
        }
        for (unsigned int i = 0; i < vertices; i++)
        {
            if (colorArr[i] == 1)
            {
                ans[0].push_back(i);
            }
            else
            {
                ans[1].push_back(i);
            }
        }
        return ans;
    }
    bool Algorithms::bipartite(Graph g, unsigned int src, int colorArr[])
    {
        colorArr[src] = 1;

        // Create a queue (FIFO) of vertex numbers a
        // nd enqueue source vertex for BFS traversal
        std::queue<unsigned int> q;
        q.push(src);

        // Run while there are vertices in queue (Similar to
        // BFS)
        while (!q.empty())
        {
            unsigned int u = q.front();
            q.pop();

            // Find all non-colored adjacent vertices
            for (unsigned int v = 0; v < g.getNumOfVertices(); ++v)
            {
                // An edge from u to v exists and
                // destination v is not colored
                if (g.getAt(u, v) && colorArr[v] == -1)
                {
                    // Assign alternate color to this
                    // adjacent v of u
                    colorArr[v] = 1 - colorArr[u];
                    q.push(v);
                }

                // An edge from u to v exists and destination
                // v is colored with same color as u
                else if (g.getAt(u, v) && colorArr[v] == colorArr[u])
                    return false;
            }
        }

        // If we reach here, then all adjacent vertices can
        // be colored with alternate color
        return true;
    }

    //     vector<unsigned int> Algorithms::getNegativeCycle(Graph g)
    //     {
    //         vector<unsigned int> ans;
    //         unsigned int vertices = g.getNumOfVertices();
    //         unsigned int parents[vertices];
    //         int dist[vertices][vertices];
    //         for (unsigned int i = 0; i < vertices; i++)
    //         {
    //             parents[i] = INT_MAX;
    //             for (unsigned int j = 0; j < vertices; j++)
    //             {
    //                 dist[i][j] = 0;
    //             }
    //         }

    //         for (unsigned int i = 0; i < vertices; i++)
    //         {
    //             for (unsigned int j = 0; j < vertices; j++)
    //             {
    //                 if (g.getAt(i, j) != 0)
    //                 {
    //                     dist[i][j] = g.getAt(i, j);
    //                 }
    //             }
    //         }

    //         for (unsigned int k = 1; k < vertices; k++)
    //         {
    //             for (unsigned int i = 0; i < vertices; i++)
    //             {
    //                 for (unsigned int j = 0; j < vertices; j++)
    //                 {
    //                     if (i != j)
    //                     {
    //                         if (dist[i][j] == 0 || dist[i][j] > (dist[i][k] + dist[k][j]))
    //                         {
    //                             dist[i][j] = dist[i][k] + dist[k][j];
    //                             parents[i] = k;
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //         for (unsigned int i = 0; i < vertices; i++)
    //         {
    //             if (dist[i][i] < 0)
    //             {
    //                 unsigned int p = parents[i];
    //                 while (p != i)
    //                 {
    //                     ans.push_back(p);
    //                     p = parents[p];
    //                 }
    //             }
    //         }
    //         return ans;
    //     }
    // }
//TODO
    vector<unsigned int> Algorithms::getNegativeCycle(Graph g)
    {
        unsigned int vertices = g.getNumOfVertices();
        for (unsigned int source = 0; source < vertices; source++)
        {
            unsigned int parents[vertices];
            bool *connectedToCycle = new bool[vertices];
            int dist[vertices];
            for (unsigned int i = 0; i < vertices; i++)
            {
                parents[i] = INT_MAX;
                dist[i] = INT_MAX;
                connectedToCycle[i] = false;
            }
            dist[source] = 0;
            for (unsigned int k = 0; k < vertices; k++)
            {
                for (unsigned int i = 0; i < vertices; i++)
                {
                    for (unsigned int j = 0; j < vertices; j++)
                    {
                        if (g.getAt(i, j) != 0 && dist[i] != INT_MAX && dist[j] > dist[i] + g.getAt(i, j) && !parents[i] == j)
                        {
                            dist[j] = dist[i] + g.getAt(i, j);
                            parents[j] = i;
                        }
                    }
                }
            }
            unsigned int cycleStart = INT_MAX;
            for (unsigned int i = 0; i < vertices; i++)
            {
                for (unsigned int j = 0; j < vertices; j++)
                {
                    if (g.getAt(i, j) != 0 && dist[i] != INT_MAX && dist[j] > dist[i] + g.getAt(i, j) && !parents[i] == j)
                    {
                        while (!connectedToCycle[j])
                        {
                            connectedToCycle[j] = true;
                            j = parents[j];
                        }
                        cycleStart = j;
                        break;
                    }
                }
                if (cycleStart != INT_MAX)
                {
                    break;
                }
            }
            if (cycleStart != INT_MAX)
            {
                vector<unsigned int> ans;
                ans.push_back(cycleStart);
                unsigned int traverseCycle = parents[cycleStart];
                while (traverseCycle != cycleStart)
                {
                    ans.push_back(traverseCycle);
                    traverseCycle = parents[traverseCycle];
                }
                std::reverse(ans.begin(), ans.end());
                return ans;
            }
        }
        return vector<unsigned int>();
    }
}