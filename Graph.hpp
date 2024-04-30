// 214984932 Oriyas.07@gmail.com

#include <vector>

using std::vector;

namespace ariel
{
    class Graph
    {
    public:
        Graph(); // defult empty constructor
        void loadGraph(vector<vector<int>> g);
        void printGraph();
        int getSize();
        int getAt(int x, int y);
        bool isDirected();
        int getEdges();
    };
}