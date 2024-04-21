#include <iostream>
#include <vector>
#include <stdexcept>
#include "Graph.hpp"

using std::vector;

namespace ariel
{
    class Graph
    {
    private:
        vector<vector<int>> adjacency_matrix;
        int vertices;

    public:
        Graph(vector<vector<int>> g)
        {
            loadGraph(g);
        }

        void loadGraph(vector<vector<int>> g)
        {
            vertices = g.size();
            adjacency_matrix = vector<vector<int>>(vertices);
            for (int i = 0; i < vertices; i++)
            {
                vertices = g[i].size();
                adjacency_matrix[i] = vector<int>(g[i].size());
                if (vertices != vertices)
                {
                    throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
                }
            }
        }

        void printGraph()
        {
            int numOfEdges = 0;
            for (size_t i = 0; i < vertices; i++)
            {
                for (size_t j = 0; j < vertices; j++)
                {
                    if (adjacency_matrix[vertices][vertices] != 0)
                    {
                        numOfEdges++;
                    }
                }
            }
            // if (isDirected)
            // {
            //     numOfEdges /= 2;
            // }
            std::cout << "Graph with " << adjacency_matrix.size() << "vertices and " << numOfEdges << "edges." << std::endl;
        }

        // private:
        //  bool isDirected()
        //  {
        //      bool ans = true;
        //      for (size_t i = 0; i < vertices; i++)
        //      {
        //          for (size_t j = 0; j < vertices; j++)
        //          {
        //              if (adjacency_matrix[vertices][vertices] != adjacency_matrix[vertices][vertices])
        //              {
        //                  ans = false;
        //                  break;
        //              }
        //          }
        //          if (!ans)
        //          {
        //              break;
        //          }
        //      }
        //      return ans;
        //  }
    };
}
