// Compile with c++ ece650-a2cpp -std=c++11 -o ece650-a2
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <string>
#include "GraphList/GraphList.h"

void extractIntegerWords(std::string lineData);
std::vector<Edge> parseEdges(std::string lineData, int num);
std::vector<int> parseSourceDestination(std::string lineData);
int parseVertex(std::string lineData);


int main(int argc, char** argv) {
    // Test code. Replaced with your code
    std::vector<Edge> EdgeData;
    std::vector<int> shorPathData;
    int vertexNum;
    int count=0;

    std::regex rVertex(R"([vV]\s*?[0-9]+)");
    std::regex rVertex1(R"([vV]\s*?[1]+)");
    std::regex rPath(R"([sS]\s*?[0-9]+\s*?[0-9]+)");
    std::regex rEdgeList(R"([eE]\s*?\{\s*(<\s*?[0-9]+\s?,\s*?[0-9]+\s*?>\s*?,\s*?)+(<\s*?[0-9]+\s*?,\s*?[0-9]+\s*?>)+\s*\})");
    std::regex rEdgeOne(R"([eE]\s*?\{\s*(<\s*?[0-9]+\s?,\s*?[0-9]+\s*?>\s*?)\})");
    std::regex rEdgeListNone(R"([eE]\s*?\{\})");

    std::smatch rPathStatus,rVertexStatus,rEdgeStatus;
    std::smatch rVNone,rENone, rEOne;
    while (!std::cin.eof())
    {

        // read a line of input until EOL and store in a string
        std::string line;
        std::getline(std::cin, line);
        
        auto s1 = std::regex_match(line,rVertexStatus,rVertex);
        auto s2 = std::regex_match(line,rEdgeStatus,rEdgeList);
        auto s3 = std::regex_match(line,rPathStatus,rPath);
        auto s4 = std::regex_match(line,rVNone,rVertex1);
        auto s5 = std::regex_match(line,rENone,rEdgeListNone);
        auto s6 = std::regex_match(line,rEOne,rEdgeOne);

        // if (s4 || s5)
        // {
        //     std::cerr<<"Error : No Graph for shortest path"<<std::endl;
        // }
        
        if (s1)
        {
           /*std::cout<<"Vertex Added"<<std::endl;*/
           if (count >0)
           {
               vertexNum =parseVertex(line); 
               EdgeData.clear();
           }
           
           
           vertexNum =  parseVertex(line);         
           std::cout<<line<<std::endl;
           
        }
        //std::cout<<"A"<<std::endl;

        if (s2 || s6)
        {
            //std::cout<<"Edges added"<<std::endl;
            std::cout<<line<<std::endl;

            EdgeData = parseEdges(line,vertexNum);
        }

        if (s5)
        {
            std::cout<<line<<std::endl;
            //std::cerr<<"Error : No Graph to search for for shortest path"<<std::endl;

        }
        
        //std::cout<<"B"<<std::endl;
        //if (s2 == false)
        //{
            //std::cout<<line<<std::endl;
            //int lengthOfString = line.size();
            //std::cout<<lengthOfString;
            //std::cout<<"Unable to add edges"<<std::endl;
        //}
        
        if (s3)
        {
            //std::cout<<line<<std::endl;
            shorPathData = parseSourceDestination(line);
            GraphList *test = new GraphList(vertexNum);
            if (EdgeData.size() != 0)
            {
                test->GenerateGraphList(EdgeData);
                auto z = test->BFSearchList(shorPathData[0]);
                auto result = test->findDisconnectedVectors();
                auto shortPath = test->DisplayShortestPath(shorPathData[0],shorPathData[1],z);
                if (shortPath.size() > 0)
                {
                    int size = shortPath.size();
                    for(int i = size; i >= 1; i--)
                    {
                        int k = i;
                        --k;
                        if (k ==0)
                        {
                            std::cout<<shortPath[k];
                        }
                        else
                        {
                            std::cout<<shortPath[k]<<"-";
                        }  
                    }
                    count +=1;
                }
                else
                {
                    std::cerr<<"Error : Path does not exist";
                }
            }
            else
            {
                std::cerr<<"Error : Path does not exist";
            }  
        }

    }
    return (0);
}

int parseVertex(std::string lineData)
{
    std::regex r4(R"([0-9]+)");
    std::regex re(R"([vV]\s*?[0-9]+)");
    std::smatch vPOints;
    std::smatch vPOints3;
    std::string at;
    auto vt = std::regex_match(lineData,vPOints,re);
    if (vt)
    {
        auto tr = std::regex_search(lineData,vPOints3,r4);
        at = vPOints3[0];
    }
    else
    {
        std::cerr<<"Error: Parsing Vertex Data";
        //std::cout<<"Error: Parsing Vertex Data";
    }  
    return std::stoi(at);
}

std::vector<Edge> parseEdges(std::string lineData, int num)
{
        std::regex r4(R"([0-9]+)");
        std::regex r3(R"([eE]\s*?\{\s*(<\s*?[0-9]+\s?,\s*?[0-9]+\s*?>\s*?,\s*?)+(<\s*?[0-9]+\s*?,\s*?[0-9]+\s*?>)+\s*\})");
        std::regex r2(R"(\{\s*(<\s*?[0-9]+\s?,\s*?[0-9]+\s*?>\s*?,\s*?)+(<\s*?[0-9]+\s*?,\s*?[0-9]+\s*?>)+\s*\})");
        std::regex r5(R"([eE]\s*?\{\s*(<\s*?[0-9]+\s?,\s*?[0-9]+\s*?>\s*?)\})");
        std::regex rNew(R"(\s*?\<[0-9]+,[0-9]+\s*?\>)");
        std::smatch vPOints3;
        std::smatch vPOintsNew;
        std::smatch vPOintsTest, vPointTest2;
        std::vector<Edge> edgeList;

        auto vt = std::regex_match(lineData,vPOintsTest,r3);
        auto eOT = std::regex_match(lineData,vPointTest2,r5);

        if (vt || eOT )
        {
            while (std::regex_search(lineData,vPOints3,rNew))
            {
                //std::cout << vPOints3[0] << std::endl;
                std::string at = vPOints3[0];

                int i=1;
                Edge a;
                while (std::regex_search(at,vPOintsNew,r4))
                {
                    if (i%2 != 0)
                    {
                        //std::cout<< vPOintsNew[0] << std::endl;
                        std::string temp = vPOintsNew[0];
                        int tempin = std::stoi(temp);
                        a.sourceVertex = tempin;
                    }
                    if (i%2 == 0)
                    {
                        //std::cout<< vPOintsNew[0] << std::endl;
                        std::string temp = vPOintsNew[0];
                        int tempin = std::stoi(temp);
                        a.destinationVertex = tempin;
                    }
                    i++;
                    at = vPOintsNew.suffix();
                }
                if (a.sourceVertex == a.destinationVertex)
                {
                    std::cerr<<"Error: A Self loop edge identified inavlid edge information";
                    //std::cout<<"Error: A Self loop edge identified inavlid edge information";
                }
                if ((a.destinationVertex>=num)||(a.sourceVertex >= num))
                {
                    std::cerr<<"Error: Invalid vertex information";
                    //std::cout<<"Error: Invalid vertex information";
                }
                
                else
                {
                    edgeList.push_back(a);
                }
                lineData = vPOints3.suffix();
            }
        }
        else
        {
            std::cerr<<"Error : Parsing data for edges";
            //std::cout<<"Error : Parsing data for edges";
        }
        
        return edgeList;
}

std::vector<int> parseSourceDestination(std::string lineData)
{
    std::regex r4(R"([0-9]+)");
    std::regex re(R"([sS]\s*?[0-9]+\s*?[0-9]+)");
    
    std::smatch vPOints;
    std::smatch vPOints3;
    auto vt = std::regex_match(lineData,vPOints,re);
    std::vector<int> pathList;
    if(vt)
    {
        while (std::regex_search(lineData,vPOints3,r4))
        {
            std::string at = vPOints3[0];
            pathList.push_back(std::stoi(at));
            lineData = vPOints3.suffix();
        }
    }
    else
    {
        std::cerr<<"Error : Parsing data for Source and Destination";
        //std::cout<<"Error : Parsing data for Source and Destination";
    } 
    return pathList;
}
