// 214984932 Oriyas.07@gmail.com

#pragma once

#include <vector>

using std::vector;

namespace ariel
{
    class Graph
    {
    private:
        vector<vector<int>> adjacency_matrix;
        unsigned int vertices;
        int edges;
        bool directed;

    public:
        Graph(); // defult empty constructor
        void loadGraph(vector<vector<int>> g);
        void printGraph();
        unsigned int getSize();
        int getAt(unsigned int x, unsigned int y);
        bool isDirected();
        int getEdges();
        bool checkDirected();
    };
}