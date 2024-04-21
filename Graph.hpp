//214984932 Oriyas.07@gmail.com

#include <vector>

using std::vector;

namespace ariel
{
    class Graph
    {
    public:
        Graph(vector<vector<int>> g);       //constructor
        ~Graph();                           //destructor
        void loadGraph(vector<vector<int>> g);
        void printGraph();
        int getSize();
    };
}