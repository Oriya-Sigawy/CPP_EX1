// 214984932 Oriyas.07@gmail.com

#pragma once
#include <array>
#include <string>
#include <vector>
#include "Graph.hpp"

using std::string;
using std::vector;

namespace ariel
{
    class Algorithms
    {
    public:
        static bool isConnected(Graph);
        static vector<unsigned int> shortestPath(Graph, unsigned int, unsigned int);
        static vector<unsigned int> getCycle(Graph);
        static std::array<vector<unsigned int>,2> bipartitePartition(Graph);
        static vector<unsigned int> getNegativeCycle(Graph);

    private:
        static void traverse(unsigned int, bool*, Graph);
        static unsigned int minDist(int *, bool *, unsigned int);
        static vector<unsigned int> getCycleUndirected(Graph);    
        static vector<unsigned int> isCyclic_UD(unsigned int, bool[], unsigned int, Graph, unsigned int[]);  
        static vector<unsigned int> isCyclic_D(unsigned int, bool[], bool *, Graph);   
        static vector<unsigned int> getCycledirected(Graph);
        static bool bipartite(Graph, unsigned int, int[]);
    };
}