// 214984932 Oriyas.07@gmail.com

#pragma once

#include <string>
#include "Graph.hpp"

using std::string;

namespace ariel
{
    class Algorithms
    {
    public:
        static bool isConnected(Graph);
        static string shortestPath(Graph, int, int);
        static string isContainsCycle(Graph);
        static string isBipartite(Graph);
        static string negativeCycle(Graph);

    private:
        static void traverse(unsigned int, bool*, Graph);
        static unsigned int minDist(int *, bool *, unsigned int);
        static string isContainsCycleUndirected(Graph);
        static vector<unsigned int> isCyclicUtil_UD(unsigned int, bool[], unsigned int, Graph, unsigned int[]);
        static bool isCyclicUtil_D(unsigned int, bool[], bool *, Graph);
        static string isContainsCycledirected(Graph g);
        static bool isBipartiteUtil(Graph, unsigned int, int[]);
    };
}