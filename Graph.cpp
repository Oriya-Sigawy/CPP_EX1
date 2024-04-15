#include <iostream>
#include <vector>
#include <stdexcept>
#include "Graph.hpp"
using namespace std;
class Graph
{
    vector<vector<float>> graph;
    int rows;
    int cols;
    void loadGraph(vector<vector<int>> g)
    {
        rows=g.size();
        graph= vector<vector<float>> (rows);
        for(int i=0; i<rows;i++)
        {
            cols=g[i].size();
            graph[i] = vector<float>(g[i].size());
            if(cols!=rows)
            {
                throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
        }
    }

    void printGraph()
    {
        int numOfEdges=0;
        for (size_t i = 0; i < rows; i++)
        {
           for (size_t j = 0; j < cols; j++)
           {
            if (graph[rows][cols]!=0)
            {
                numOfEdges++;
            }
           } 
        }
        if (isDirected)
        {
            numOfEdges/=2;
        }
        cout << "Graph with " << graph.size() << "vertices and " << numOfEdges <<"edges." << endl;
    }
    bool isDirected()
    {
        bool ans = true;
        for (size_t i = 0; i < rows; i++)
        {
           for (size_t j = 0; j < cols; j++)
           {
            if (graph[rows][cols]!=graph[cols][rows])
            {
                ans=false;
                break;
            }
           }
           if(!ans)
           {
            break;
           } 
        }
        return ans;
    }

};
