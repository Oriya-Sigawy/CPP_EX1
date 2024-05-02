#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

////tests for Graph.cpp
TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Test printGraph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 4, 0, 2},
        {1, 4, 0, 3, 0},
        {0, 0, 3, 0, 1},
        {0, 2, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.printGraph() == "Graph with 5 vertices and 6 edges.");

    vector<vector<int>> graph2 = {
        {0, 1, 2, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {3, 0, 0, 0, 4},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(g.printGraph() == "Graph with 5 vertices and 6 edges.");
}

TEST_CASE("Test getNumOfVertices")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 4, 0, 2},
        {1, 4, 0, 3, 0},
        {0, 0, 3, 0, 1},
        {0, 2, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.getNumOfVertices() == 5);
}

TEST_CASE("Test getAt")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 4, 0, 2},
        {1, 4, 0, 3, 0},
        {0, 0, 3, 0, 1},
        {0, 2, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK_THROWS(g.getAt(-5, 1));
    CHECK_THROWS(g.getAt(5, 0));
    CHECK_THROWS(g.getAt(6, 7));
    CHECK(g.getAt(2, 0) == 1);
}

TEST_CASE("Test getEdges")
{
    ariel::Graph g;
    vector<vector<int>> graph1 = {
        {0, 0},
        {0, 0}};
    g.loadGraph(graph1);
    CHECK(g.getEdges() == 0);

    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph2);
    CHECK(g.getEdges() == 3);
}

/////////
TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");
}
TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "false");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "true");
}
TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}");
}
TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
}
