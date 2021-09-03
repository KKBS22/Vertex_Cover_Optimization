#include "GraphList.h"
#include <iostream>
#include <vector>
#include <queue>


GraphList::GraphList(int nVertices)
{
   int vertex_count = nVertices;
   this->adjList.resize(vertex_count+3);
 
 //this->adjList = new std::vector<int>[nVertices];
 for(int i = 0; i<nVertices+1; i++)
 {
     Vertex a;
     a.color = 0;
     a.index = i;
     a.distance = 0;
     a.previousIndex = 0;
     this->vertexList.push_back(a);
 }


}

// GraphList::~GraphList()
// {

// }


void GraphList::GenerateGraphList(std::vector<Edge> myEdge)
{
    for(auto a : myEdge)
    {
        int source = a.sourceVertex;
        int destination = a.destinationVertex;
        // Implement Graph using Adjacency List
        this->adjList[source].push_back(destination);
        this->adjList[destination].push_back(source);
    }
}

std::list<Vertex> GraphList::BFSearchList(int source)
{
    this->vertexList[source].color = 2;
    this->vertexList[source].distance = 0;
    this->vertexList[source].previousIndex = -1;
    std::queue<Vertex> traverseQ;
    std::list<Vertex> outputQ;
    traverseQ.push(vertexList[source]);
    while (!traverseQ.empty())
    {
        auto u = traverseQ.front();
        outputQ.push_back(u);
        traverseQ.pop();
        
        for(auto &v : adjList[u.index])
        {
            if (vertexList[v].color == 0)
            {                
                vertexList[v].color = 2;
                vertexList[v].distance = u.distance +1;
                vertexList[v].previousIndex = u.index;
                traverseQ.push(vertexList[v]);

            }
        }
        u.color = 1;
        //std::cout<<vertexList[u.index].index<<"at level" <<vertexList[u.index].distance <<'\n';
    } 
    return outputQ;
}


std::vector<int> GraphList::findDisconnectedVectors()
{

    for(auto &a : this->vertexList)
    {
        if (a.color == 0)
        {
            this->disconnectedList.push_back(a.index);
        }
        
    }
    return this->disconnectedList;
}

std::vector<int> GraphList::DisplayShortestPath(int source, int destination, std::list<Vertex> outQ)
{
    bool sourcePresent = false;
    bool destPresent = false;
    std::vector<int> path;
    for (auto a : outQ)
    {
        if (a.index == source)
        {
            sourcePresent = true;
        }
        if (a.index == destination)
        {
            destPresent = true;
        }
        
    }

    if ((sourcePresent == true) && (destPresent == true))
    {
        while (this->vertexList[destination].previousIndex != -1)
        {
            path.push_back(vertexList[destination].index);
            destination = vertexList[destination].previousIndex;
        }
        path.push_back(vertexList[destination].index);
       
    }
    else
    {
        return path = {};
    }
    
    return path;

}

void GraphList::setVertices(int numOfVertices )
{
    this->noOfVertices = numOfVertices;
}

void GraphList::addEdges(Edge a)
{
    this->myEdgeVector.push_back(a);
}
