// 214984932 Oriyas.07@gmail.com

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
        if (g.isDirected())
        {
            return getCycledirected(g);
        }
        return getCycleUndirected(g);
    }

    vector<unsigned int> Algorithms::getCycleUndirected(Graph g)
    {
        // Mark all the vertices as not
        // visited and not part of recursion
        // stack
        unsigned int vertices = g.getNumOfVertices();
        bool *visited = new bool[vertices];
        bool *bParents = new bool[vertices];
        unsigned int parents[vertices];
        for (unsigned int i = 0; i < vertices; i++)
        {
            visited[i] = false;
            parents[i] = INT_MAX;
            bParents[i] = false;
        }

        // Call the recursive helper
        // function to detect cycle in different
        // DFS trees
        vector<unsigned int> ans;
        vector<unsigned int> ans2;
        for (unsigned int u = 0; u < vertices; u++)
        {

            // Don't recur for u if
            // it is already visited
            if (!visited[u])
            {
                ans = isCyclic_UD(u, visited, INT_MAX, g, parents);
                if (ans.size() != 0)
                {
                    unsigned int a = ans[0];
                    unsigned int b = ans[1];
                    unsigned int prev_b = parents[b];
                    unsigned int prev_a = a;
                    while (parents[prev_b] != INT_MAX && !bParents[prev_b])
                    {
                        bParents[prev_b] = true;
                        prev_b = parents[prev_b];
                    }
                    while (!bParents[prev_a])
                    {
                        ans.push_back(prev_a);
                        prev_a = parents[prev_a];
                    }
                    ans.push_back(prev_a);
                    prev_b = b;
                    while (prev_b != prev_a)
                    {
                        ans2.push_back(prev_b);
                        prev_b = parents[prev_b];
                    }
                    std::reverse(ans2.begin(), ans2.end());
                    ans.insert(ans.end(), ans2.begin(), ans2.end());
                    return ans;
                }
            }
        }
        return ans;
    }
    vector<unsigned int> Algorithms::isCyclic_UD(unsigned int v, bool visited[], unsigned int parent, Graph g, unsigned int parents[])
    {

        // Mark the current node as visited
        vector<unsigned int> ans;
        visited[v] = true;
        parents[v] = parent;
        // Recur for all the vertices
        // adjacent to this vertex
        for (unsigned int i = 0; i < g.getNumOfVertices(); ++i)
        {
            if (g.getAt(v, i) != 0)
            {
                // If an adjacent vertex is not visited,
                // then recur for that adjacent
                if (!visited[i])
                {
                    ans = isCyclic_UD(i, visited, v, g, parents);
                    if (ans.size() != 0)
                    {
                        return ans;
                    }
                }

                // If an adjacent vertex is visited and
                // is not parent of current vertex,
                // then there exists a cycle in the graph.
                else if (i != parent)
                {
                    ans.push_back(v);
                    ans.push_back(i);
                    return ans;
                }
            }
        }
        return ans;
    }

    //////////////////////////
    vector<unsigned int> Algorithms::getCycledirected(Graph g)
    {
        // Mark all the vertices as not visited
        // and not part of recursion stack
        unsigned int vertices = g.getNumOfVertices();
        vector<unsigned int> result;
        bool *visited = new bool[vertices];
        bool *recStack = new bool[vertices];
        for (unsigned int i = 0; i < vertices; i++)
        {
            visited[i] = false;
            recStack[i] = false;
        }

        // Call the recursive helper function
        // to detect cycle in different DFS trees
        for (unsigned int i = 0; i < vertices; i++)
        {
            result = isCyclic_D(i, visited, recStack, g);
            if (!visited[i] && result.size() != 0)
            {
                return result;
            }
        }
        return result;
    }

    vector<unsigned int> Algorithms::isCyclic_D(unsigned int v, bool visited[], bool *recStack, Graph g)
    {
        vector<unsigned int> ans;
        if (visited[v] == false)
        {
            // Mark the current node as visited
            // and part of recursion stack
            visited[v] = true;
            recStack[v] = true;

            // Recur for all the vertices adjacent to this
            // vertex
            for (unsigned int i = 0; i < g.getNumOfVertices(); ++i)
            {
                if (g.getAt(v, i) != 0)
                {
                    ans = isCyclic_D(i, visited, recStack, g);
                    if (!visited[i] && (ans.size() != 0))
                    {
                        return ans;
                    }
                    else if (recStack[i])
                    {
                        for (unsigned int i = 0; i < g.getNumOfVertices(); i++)
                        {
                            if (recStack[i])
                            {
                                ans.push_back(i);
                                return ans;
                            }
                        }
                    }
                }
            }
        }

        // Remove the vertex from recursion stack
        recStack[v] = false;
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

    vector<unsigned int> Algorithms::getNegativeCycle(Graph g)
    {
        vector<unsigned int> ans;
        unsigned int vertices = g.getNumOfVertices();
        unsigned int parents[vertices];
        int dist[vertices][vertices];
        for (unsigned int i = 0; i < vertices; i++)
        {
            for (unsigned int j = 0; j < vertices; j++)
            {
                dist[i][j] = 0;
                parents[i] = INT_MAX;
            }
        }

        for (unsigned int i = 0; i < vertices; i++)
        {
            for (unsigned int j = 0; j < vertices; j++)
            {
                if (g.getAt(i, j) > 0)
                {
                    dist[i][j] = g.getAt(i, j);
                }
            }
        }

        for (unsigned int k = 1; k < vertices; k++)
        {
            for (unsigned int i = 0; i < vertices; i++)
            {
                for (unsigned int j = 0; j < vertices; j++)
                {
                    if (i != j)
                    {
                        if (dist[i][j] == 0 || dist[i][j] > (dist[i][k] + dist[k][j]))
                        {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            parents[i] = k;
                        }
                    }
                }
            }
        }
        for (unsigned int i = 0; i < vertices; i++)
        {
            if (dist[i][i] < 0)
            {
                unsigned int p = parents[i];
                while (p != i)
                {
                    ans.push_back(p);
                    p = parents[p];
                }
            }
        }
        return ans;
    }
}
