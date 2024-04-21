#include <vector>

using std::vector;

namespace ariel
{
    class Graph
    {
        public:
        Graph(vector<vector<int>> g);
        void loadGraph(vector<vector<int>> g);
         void printGraph();
        
    }
}