// 214984932 Oriyas.07@gmail.com

#include <iostream>
#include <limits.h>
#include <string.h>
#include <bits/stdc++.h>
#include "Graph.hpp"
#include "Algorithms.hpp"
using std::string;
namespace ariel
{
    class Algorithms
    {
        void traverse(int u, bool *visited, Graph g)
        {
            visited[u] = true;
            for (int v = 0; v < g.getSize(); v++)
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
        bool isConnected(Graph g)
        {
            bool *visited = new bool[g.getSize()]; // save g.getSize as size instead of calling getSize so much times?
            for (int u = 0; u < g.getSize(); u++)
            {
                for (int i = 0; i < g.getSize(); i++)
                {
                    visited[i] = false;
                    traverse(u, visited, g);
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
        // Function that implements Dijkstra's single source shortest path algorithm
        string shortestPath(Graph g, int start, int end)
        {
            int vertices = g.getSize();
            int dist[vertices];
            int prev[vertices];
            bool sptSet[vertices];

            for (int i = 0; i < vertices; i++)
            {
                dist[i] = INT_MAX, sptSet[i] = false, prev[i] = NULL;
            }

            dist[start] = 0;
            for (int count = 0; count < vertices - 1; count++)
            {
                int u = minDist(dist, sptSet, vertices);
                sptSet[u] = true;
                for (int v = 0; v < vertices; v++)
                {
                    if (!sptSet[v] && g.getAt(u, v) && dist[u] != INT_MAX && dist[u] + g.getAt(u, v) < dist[v])
                    {
                        dist[v] = dist[u] + g.getAt(u, v);
                        prev[v] = u;
                    }
                }
            }
            if (dist[end] == INT_MAX)
            {
                return "-1";
            }
            string result = "";
            int i = end;
            while (i != start)
            {
                result = std::to_string(i) + result;
                result = "->" + result;
                i = prev[i];
            }
            result = std::to_string(start) + result;
            return result;
        }
        string isContainsCycle(Graph g)
        {
            if (g.isDirected())
            {
                return isContainsCycledirected(g);
            }
            return isContainsCycleUndirected(g);
        }
        string isContainsCycleUndirected(Graph g)
        {
            // Mark all the vertices as not
            // visited and not part of recursion
            // stack
            bool *visited = new bool[g.getSize()];
            bool *isBParent = new bool[g.getSize()];
            int parents[g.getSize()] = {-1};
            for (int i = 0; i < g.getSize(); i++)
            {
                visited[i] = false;
            }

            // Call the recursive helper
            // function to detect cycle in different
            // DFS trees
            for (int u = 0; u < g.getSize(); u++)
            {

                // Don't recur for u if
                // it is already visited
                if (!visited[u])
                {
                    vector<int> ans = isCyclicUtil_UD(u, visited, -1, g, parents);
                    if (ans.size() != 0)
                    {
                        int a = ans[0];
                        int b = ans[1];
                        int prev_b = parents[b];
                        int prev_a = parents[a];
                        string result = std::to_string(prev_a);
                        while (prev_b != -1)
                        {
                            isBParent[prev_b] = true;
                            prev_b = parents[prev_b];
                        }
                        while (!isBParent[prev_a])
                        {
                            result += std::to_string(prev_a);
                        }
                        result += std::to_string(prev_a);
                        prev_b = b;
                        string result2 = "";
                        while (prev_b != prev_a)
                        {
                            result2 = std::to_string(prev_b) + result2;
                        }
                        return result + result2;
                    }
                }
            }
            return "false";
        }
        vector<int> isCyclicUtil_UD(int v, bool visited[], int parent, Graph g, int parents[])
        {

            // Mark the current node as visited
            vector<int> ans;
            visited[v] = true;
            parents[v] = parent;
            // Recur for all the vertices
            // adjacent to this vertex
            for (int i = 0; i < g.getSize(); ++i)
            {
                if (g.getAt(v, i) != 0)
                {
                    // If an adjacent vertex is not visited,
                    // then recur for that adjacent
                    if (!visited[i])
                    {
                        vector<int> ans = isCyclicUtil_UD(i, visited, v, g, parents);
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
                        vector<int> ans;
                        ans.push_back(v);
                        ans.push_back(i);
                        return ans;
                    }
                }
            }
            return ans;
        }

        //////////////////////////
        bool isCyclicUtil_D(int v, bool visited[], bool *recStack, Graph g)
        {
            if (visited[v] == false)
            {
                // Mark the current node as visited
                // and part of recursion stack
                visited[v] = true;
                recStack[v] = true;

                // Recur for all the vertices adjacent to this
                // vertex

                for (int i = 0; i < g.getSize(); ++i)
                {
                    if (g.getAt(v, i) != 0)
                    {
                        if (!visited[i] && isCyclicUtil_D(i, visited, recStack, g))
                        {
                            return true;
                        }
                        else if (recStack[i])
                        {
                            return true;
                        }
                    }
                }
            }

            // Remove the vertex from recursion stack
            recStack[v] = false;
            return false;
        }
        string isContainsCycledirected(Graph g)
        {

            // Mark all the vertices as not visited
            // and not part of recursion stack
            bool *visited = new bool[g.getSize()];
            bool *recStack = new bool[g.getSize()];
            for (int i = 0; i < g.getSize(); i++)
            {
                visited[i] = false;
                recStack[i] = false;
            }

            // Call the recursive helper function
            // to detect cycle in different DFS trees
            for (int i = 0; i < g.getSize(); i++)
            {
                if (!visited[i] && isCyclicUtil_D(i, visited, recStack, g))
                {
                    string result = "";
                    for (int i = 0; i < g.getSize(); i++)
                    {
                        if (recStack[i])
                        {
                            result += std::to_string(i);
                        }
                    }
                    return result;
                }
            }
            return "false";
        }
        string isBipartite(Graph g)
        {

            // Create a color array to store colors assigned to all
            // vertices. Vertex/ number is used as index in this
            // array. The value '-1' of colorArr[i] is used to
            // indicate that no color is assigned to vertex 'i'.
            // The value 1 is used to indicate first color is
            // assigned and value 0 indicates second color is
            // assigned.
            int colorArr[g.getSize()];
            for (int i = 0; i < g.getSize(); ++i)
            {
                colorArr[i] = -1;
            }

            // This code is to handle disconnected graph
            for (int i = 0; i < g.getSize(); i++)
            {
                if (colorArr[i] == -1)
                {
                    if (isBipartiteUtil(g, i, colorArr) == false)
                    {
                        return "false";
                    }
                }
            }
            string A = "";
            string B = "";
            for (int i = 0; i < g.getSize(); i++)
            {
                if (colorArr[i] == 1)
                {
                    A += std::to_string(i);
                    A += " ";
                }
                else
                {
                    B += std::to_string(i);
                    B += " ";
                }
            }
            return "The graph is bipertite: A = {" + A + "} B = {" + B + "}";
        }
        bool isBipartiteUtil(Graph g, int src, int colorArr[])
        {
            colorArr[src] = 1;

            // Create a queue (FIFO) of vertex numbers a
            // nd enqueue source vertex for BFS traversal
            std::queue<int> q;
            q.push(src);

            // Run while there are vertices in queue (Similar to
            // BFS)
            while (!q.empty())
            {
                int u = q.front();
                q.pop();

                // Find all non-colored adjacent vertices
                for (int v = 0; v < g.getSize(); ++v)
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
        ////////////////

        string negativeCycle(Graph g)
        {
            int len=g.getSize();
            int dist[len][len];
            for (int i = 0; i < len; i++)
            {
                for (int j = 0; j < len; j++)
                {
                    dist[i][j] = 0;
                }
            }

            for (int i = 0; i < len; i++)
            {
                for (int j = 0; j < len; j++)
                {
                    if (g.getAt(i,j) > 0)
                    {
                        dist[i][j] = g.getAt(i,j);
                    }
                }
            }

            for (int k = 1; k < len; k++)
            {
                for (int i = 0; i < len; i++)
                {
                    for (int j = 0; j < len; j++)
                    {
                        if (i != j)
                        {
                            if (dist[i][j] == 0 || dist[i][j] > (dist[i][k] + dist[k][j]))
                            {
                                dist[i][j] = dist[i][k] + dist[k][j];
                            }
                        }
                    }
                }
            }
            for(int i=0;i<len;i++)
            {
                if (dist[i][i]<0)
                {
                    return "There is a negative cycle in the graph";
                }
            }
            return "There is no negative cycle in the graph";
        }
    };
}
