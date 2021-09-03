#ifndef GRAPH_LIST
#define GRAPH_LIST

#include<iostream>
#include<vector>
#include<list>
#include<queue>

struct Edge
{
    int sourceVertex;
    int destinationVertex;
    //float distance;
};

struct Vertex
{
    int index;
    int previousIndex;
    int color;
    int distance;
    /* data */
};


class GraphList
{
//Private properties
private:
    int noOfVertices;
    std::vector<Edge> myEdgeVector;
    std::vector<int> disconnectedList;
    std::vector<Vertex> vertexList;
    std::vector<int> shortestPath;

public:
    std::vector<std::list<int>> adjList;    


    //Initialize a Graph with Number of vertices = noOfvertices
    GraphList(int vertices);

    //Create Graph as a Adjacency List
    void GenerateGraphList(std::vector<Edge> edgeVector);

    //Add number of edges in the graph
    void addEdges(Edge a);

    //Function to find the shortest path between two vertices
    std::list<Vertex> BFSearchList(int source);

    //Display the shortest path between two points
    std::vector<int> DisplayShortestPath(int source,int destination, std::list<Vertex> outQ);

    //finding disconnected vectors
    std::vector<int> findDisconnectedVectors();

    // Property getters/setters
    void setVertices(int numOfVertices);

    int getVertices() { return noOfVertices; }
};

#endif