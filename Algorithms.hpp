// 214984932 Oriyas.07@gmail.com

#include <string>

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
    };
}