// 214984932 Oriyas.07@gmail.com

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
        int edges;

    public:
        Graph()
        {
            // defult
            this->vertices = 5;
            this->adjacency_matrix = vector<vector<int>>(5, vector<int>(5, 0));
            edges=0;
        }

        void loadGraph(vector<vector<int>> g)
        {
            this->vertices = g.size();
            for (int i = 0; i < vertices; i++)
            {
                if (g[i].size() != vertices)
                {
                    throw std::invalid_argument("this is not a square matrix");
                }
            }
            this->adjacency_matrix = vector<vector<int>>(vertices, vector<int>(vertices));
            for (int i = 0; i < vertices; i++)
            {
                adjacency_matrix[i] = g[i];
            }
        }

        void printGraph()
        {
            
            for (size_t i = 0; i < vertices; i++)
            {
                for (size_t j = 0; j < vertices; j++)
                {
                    if (adjacency_matrix[vertices][vertices] != 0)
                    {
                        this->edges++;
                    }
                }
            }
            // if (isDirected)
            // {
            //     numOfEdges /= 2;
            // }
            std::cout << "Graph with " << adjacency_matrix.size() << "vertices and " << this->edges << "edges." << std::endl;
        }

        bool isDirected()
        {
            bool ans = true;
            for (size_t i = 0; i < vertices; i++)
            {
                for (size_t j = 0; j < vertices; j++)
                {
                    if (adjacency_matrix[vertices][vertices] != adjacency_matrix[vertices][vertices])
                    {
                        ans = false;
                        break;
                    }
                }
                if (!ans)
                {
                    break;
                }
            }
            return ans;
        }

        int getSize()
        {
            return vertices;
        }

        int getAt(int x, int y)
        {
            return adjacency_matrix[x][y];
        }
        int getEdges()
        {
            return edges;
        }
    };
}
