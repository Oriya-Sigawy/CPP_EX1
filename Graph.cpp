// 214984932 Oriyas.07@gmail.com

#include <iostream>
#include <vector>
#include <stdexcept>
#include "Graph.hpp"

using std::vector;

namespace ariel
{
    Graph::Graph()
    {
        // defult
        this->vertices = 5;
        this->adjacency_matrix = vector<vector<int>>(5, vector<int>(5, 0));
        this->edges = 0;
        this->directed = false;
    }

    void Graph::loadGraph(vector<vector<int>> g)
    {
        this->vertices = g.size();
        for (unsigned int i = 0; i < vertices; i++)
        {
            if (g[i].size() != vertices)
            {
                throw std::invalid_argument("this is not a square matrix");
            }
        }
        this->adjacency_matrix = vector<vector<int>>(vertices, vector<int>(vertices));
        for (unsigned int i = 0; i < vertices; i++)
        {
            adjacency_matrix[i] = g[i];
        }
        this->directed = isDirected();
        for (size_t i = 0; i < vertices; i++)
        {
            for (size_t j = 0; j < vertices; j++)
            {
                if (adjacency_matrix[i][j] != 0)
                {
                    this->edges++;
                }
            }
        }
        if(checkDirected())
        {
                    edges/=2;
        }
    }

    void Graph::printGraph()
    {
        std::cout << "Graph with " << adjacency_matrix.size() << " vertices and " << this->edges << " edges." << std::endl;
    }

    bool Graph::isDirected()
    {
        bool ans = true;
        for (size_t i = 0; i < vertices; i++)
        {
            for (size_t j = 0; j < vertices; j++)
            {
                if (adjacency_matrix[i][j] != adjacency_matrix[j][i])
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

    unsigned int Graph::getSize()
    {
        return this->vertices;
    }

    int Graph::getAt(unsigned int x, unsigned int y)
    {
        return this->adjacency_matrix[x][y];
    }
    int Graph::getEdges()
    {
        return this->edges;
    }
    bool Graph::checkDirected()
    {
        return this->directed;
    }
}
