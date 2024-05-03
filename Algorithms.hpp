// 214984932 Oriyas.07@gmail.com

#pragma once
#include <array>
#include <string>
#include "Graph.hpp"

using std::string;

namespace ariel
{
    class Algorithms
    {
    public:
        static bool isConnected(Graph);
        static std::vector<unsigned int> shortestPath(Graph, unsigned int, unsigned int);
        static std::vector<unsigned int> getCycle(Graph);
        static string bipartitePartition(Graph);
        static std::vector<unsigned int> getNegativeCycle(Graph);

    private:
        static void traverse(unsigned int, bool*, Graph);
        static unsigned int minDist(int *, bool *, unsigned int);
        static string isContainsCycleUndirected(Graph);    
        static vector<unsigned int> isCyclicUtil_UD(unsigned int, bool[], unsigned int, Graph, unsigned int[]);  
        static bool isCyclicUtil_D(unsigned int, bool[], bool *, Graph);   
        static string isContainsCycledirected(Graph g);
        static bool bipartiteUtil(Graph, unsigned int, int[]);
    };
}