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
        if(!directed)
        {
                    edges/=2;
        }
    }

    std::string Graph::to_string()
    {
        std::string str_v=std::to_string(this->vertices);
        std::string str_e=std::to_string(this->edges);
        return "Graph with " +str_v + " vertices and " + str_e + " edges.";
    }

    unsigned int Graph::getNumOfVertices()
    {
        return this->vertices;
    }

    int Graph::getAt(unsigned int x, unsigned int y)
    {
        return this->adjacency_matrix[x][y];
    }
    unsigned int Graph::getEdges()
    {
        return this->edges;
    }
    bool Graph::isDirected()
    {
        return this->directed;
    }

       bool Graph::checkDirected()
    {
        bool ans = false;
        for (size_t i = 0; i < vertices; i++)
        {
            for (size_t j = 0; j < vertices; j++)
            {
                if (adjacency_matrix[i][j] != adjacency_matrix[j][i])
                {
                    ans = true;
                    break;
                }
            }
            if (ans)
            {
                break;
            }
        }
        return ans;
    }
}
