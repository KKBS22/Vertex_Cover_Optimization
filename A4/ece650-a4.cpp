#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <string>
#include <list>
#include <stddef.h>
// defined std::unique_ptr
#include <memory>
// defines Var and Lit
#include "minisat/core/SolverTypes.h"
// defines Solver
#include "minisat/core/Solver.h"

struct Edge
{
    int sourceVertex;
    int destinationVertex;
    //float distance;
};

struct LitNew
{
    Minisat::Lit litC1;
    int i;
    int k;

};

std::vector<Edge> parseEdges(std::string lineData, int num);
int parseVertex(std::string lineData);
std::map<int,int> sameLine(std::vector<int> pointValues);

int compare(const void *a, const void * b);
int findMaxValue(std::map<int,int> freqOfPoints);
void ClauseOne(std::vector<std::vector<Minisat::Lit>> &listOfLits,int numOfVertex, int vertexCoverLen, std::unique_ptr<Minisat::Solver> &solverVC);
void ClauseTwo(std::vector<std::vector<Minisat::Lit>> &listOfLits,int numOfVertex, int vertexCoverLen,std::unique_ptr<Minisat::Solver> &solverVC);
void ClauseThree(std::vector<std::vector<Minisat::Lit>> &listOfLits,int numOfVertex, int vertexCoverLen,std::unique_ptr<Minisat::Solver> &solverVC);
void ClauseFour(std::vector<Edge> &graphData,std::vector<std::vector<Minisat::Lit>> &listOfLits,int numOfVertex, int vertexCoverLen, std::unique_ptr<Minisat::Solver> &solverVC);
void InitLits(std::vector<std::vector<Minisat::Lit>> &listOfLits,int vertexNum, int vertexCoverLen,std::unique_ptr<Minisat::Solver> &solverTT);
int AnalyzeMaxValue(int vertexNum, int freqMax,std::map<int,int> freqVal);

int main(int argc, char **argv) 
{
    
    std::vector<int> satSolve;
    std::vector<Edge> EdgeData;
    std::vector<int> pointData;
    int vertexNum;
    std::regex rVertex(R"([vV]\s*?[0-9]+)");
    std::regex rEdgeList(R"([eE]\s*?\{\s*(<\s*?[0-9]+\s?,\s*?[0-9]+\s*?>\s*?,\s*?)+(<\s*?[0-9]+\s*?,\s*?[0-9]+\s*?>)+\s*\})");
    std::regex rEdgeOne(R"([eE]\s*?\{\s*(<\s*?[0-9]+\s?,\s*?[0-9]+\s*?>\s*?)\})");
    std::regex rEdgeListNone(R"([eE]\s*?\{\})");
    while (!std::cin.eof())
    {
        // std::vector<std::vector<Minisat::Lit>> listOfLits;
        std::unique_ptr<Minisat::Solver> ptr = std::unique_ptr<Minisat::Solver>(new Minisat::Solver());
        std::smatch rVertexStatus,rEdgeStatus;
        std::smatch rVNone,rENone, rEOne;
        int maxVal =0;

        std::string line;
        std::getline(std::cin, line);

        auto s1 = std::regex_match(line,rVertexStatus,rVertex);
        auto s2 = std::regex_match(line,rEdgeStatus,rEdgeList);
        auto s5 = std::regex_match(line,rENone,rEdgeListNone);
        auto s6 = std::regex_match(line,rEOne,rEdgeOne);
        std::map<int,int> freqVal;


        if (s1)
        {     
           vertexNum =  parseVertex(line);  
           vertexNum += 1;  
           
        }
        if (s2 || s6)
        {
            EdgeData = parseEdges(line,vertexNum);
            for (auto &elem : EdgeData)
            {
               pointData.push_back(elem.destinationVertex);
               //pointData.push_back(elem.sourceVertex);
            }
            for (auto &elem : EdgeData)
            {
               //pointData.push_back(elem.destinationVertex);
               pointData.push_back(elem.sourceVertex);
            }
            
        }
        if (s5)
        {
            std::cout<<std::endl;
        }
        if (!EdgeData.empty())
        {
            bool res = true;
            std::vector<std::vector<Minisat::Lit>> listOfLitsFinal(vertexNum);
            freqVal = sameLine(pointData);
            int maxVFreq = 0;
            maxVFreq = findMaxValue(freqVal);
            maxVal = AnalyzeMaxValue(vertexNum, maxVFreq,freqVal);

            while (res == true)
            {
                std::vector<std::vector<Minisat::Lit>> listOfLits(vertexNum);
                
                InitLits(listOfLits,vertexNum,maxVal,ptr);
                ClauseOne(listOfLits,vertexNum,maxVal,ptr);
                ClauseTwo(listOfLits,vertexNum,maxVal,ptr);
                ClauseThree(listOfLits,vertexNum,maxVal,ptr);
                ClauseFour(EdgeData,listOfLits,vertexNum,maxVal,ptr);
                res = ptr->solve();
                ptr.reset(new Minisat::Solver());
                if (res == true)
                {
                    
                    maxVal -= 1;
                    listOfLits.clear();
                }
            }
            
             
            if (!res)
            {
                maxVal += 1;
                std::vector<std::vector<Minisat::Lit>> listOfLits(vertexNum);
                
                InitLits(listOfLits,vertexNum,maxVal,ptr);
                ClauseOne(listOfLits,vertexNum,maxVal,ptr);
                ClauseTwo(listOfLits,vertexNum,maxVal,ptr);
                ClauseThree(listOfLits,vertexNum,maxVal,ptr);
                ClauseFour(EdgeData,listOfLits,vertexNum,maxVal,ptr);
                res = ptr->solve();
                if (res)
                {
                    for (int i = 0; i < vertexNum; i++)
                    {
                        for (int j = 0; j < maxVal; j++)
                        {
                            if (Minisat::toInt(ptr->modelValue(listOfLits[i][j])) == 0)
                            {
                                satSolve.push_back(i);
                            }
                        }                
                    }
                    qsort(&satSolve[0],satSolve.size(),sizeof(int),compare);
                    for (auto &elem : satSolve)
                    {
                        std::cout<<elem<<" ";
                    }
                    std::cout<<std::endl;
                    listOfLits.clear();
                }
                else
                {
                    std::cerr<<"Error : Unable to find the vertex cover for the Graph"<<std::endl;
                } 
            }
            

            //Clering important DS
            pointData.clear();
            satSolve.clear(); 
            EdgeData.clear();
            
            freqVal.clear();
            //std::cout<<"Satisfiabiity :"<<res;
        } 
    }
 return 0;
}

//Initialize Literals
/*
1. Number of atomic proposition  = n x k
*/
void InitLits(std::vector<std::vector<Minisat::Lit>> &listOfLits,int vertexNum, int vertexCoverLen,std::unique_ptr<Minisat::Solver> &solverTT)
{
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexCoverLen; j++)
        {
            Minisat::Lit lt = Minisat::mkLit(solverTT->newVar());
            listOfLits[i].push_back(lt);
            
        }
        
    }
}

//Clause 1
/*
1. At least one vertex is the ith vertex in the vertex cover
2. No of clauses = k
*/
void ClauseOne(std::vector<std::vector<Minisat::Lit>> &listOfLits,int numOfVertex, int vertexCoverLen, std::unique_ptr<Minisat::Solver> &solverTT)
{
    for (int i = 0; i < vertexCoverLen; i++)
    {
        Minisat::vec<Minisat::Lit> litCOne;

        for (int j = 0; j < numOfVertex; j++)
        {
            litCOne.push(listOfLits[j][i]);
        } 
        solverTT->addClause(litCOne);
        litCOne.clear();
    } 
}

//Clause 2
/*
1. No vertex can appear twice in a vertex cover

*/
void ClauseTwo(std::vector<std::vector<Minisat::Lit>> &listOfLits,int numOfVertex, int vertexCoverLen, std::unique_ptr<Minisat::Solver> &solverTT)
{
    for (int i = 0; i < numOfVertex; i++)
    {
        for (int j = 0; j < vertexCoverLen; j++)
        {
            for (int k = j+1; k < vertexCoverLen; k++)
            {
                solverTT->addClause(~listOfLits[i][j],~listOfLits[i][k]);
            }
        }   
    }
  
}
    
//Clause 3
/*
1. Dual of 2
*/
void ClauseThree(std::vector<std::vector<Minisat::Lit>> &listOfLits,int numOfVertex, int vertexCoverLen, std::unique_ptr<Minisat::Solver> &solverTT)
{
    for (int i = 0; i < vertexCoverLen; i++)
    {
        for (int j = 0; j < numOfVertex-1; j++)
        {
            for (int k = j+1; k < numOfVertex; k++)
            {
                solverTT->addClause(~listOfLits[j][i],~listOfLits[k][i]);
            }
        }   
    }
  
}

//Clause 4
/*
1. Every edge is incident to at least one vertex in the vertex cover.
*/
void ClauseFour(std::vector<Edge> &graphData,std::vector<std::vector<Minisat::Lit>> &listOfLits,int numOfVertex, int vertexCoverLen, std::unique_ptr<Minisat::Solver> &solverTT)
{
    for (unsigned int i = 0; i < graphData.size(); i++)
    {
        Minisat::vec<Minisat::Lit> litCOne;
        for (int j = 0; j < vertexCoverLen; j++)
        {
            litCOne.push(listOfLits[graphData[i].sourceVertex][j]);
            litCOne.push(listOfLits[graphData[i].destinationVertex][j]);
        }
        solverTT->addClause(litCOne);
        litCOne.clear(); 
    }
}



int compare(const void *a, const void * b)
{
    return(*(int*)a - *(int *)b);
}

int AnalyzeMaxValue(int vertexNum, int freqMax,std::map<int,int> freqVal)
{
    int freNumber[freqMax] = {};
    for (unsigned int i = 1; i <= freqMax ; i++)
    {
        int count =0;
        for (auto &elem : freqVal)
        {
            if (elem.second == i)
            {
                ++count;
            }  
        }
        freNumber[i-1] = count;
    }
    return (freqMax + ((vertexNum - freqMax)/freqMax));
}

int findMaxValue(std::map<int,int> freqOfPoints)
{
    int a =1 ;
    for (auto &elem : freqOfPoints)
    {
        if (elem.second > a)
        {
            a = elem.second;
        } 
    }
    return a;
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
        std::regex_search(lineData,vPOints3,r4);
        at = vPOints3[0];
    }
    else
    {
        std::cerr<<"Error: Parsing Vertex Data";
        //std::cout<<"Error: Parsing Vertex Data";
    }  
    return std::stoi(at);
}

std::map<int,int> sameLine(std::vector<int> pointValues)
{
    std::vector<int> xValues;
    std::map<int,int> frequencyX;
    for (auto &elem : pointValues)
    {
        auto result = frequencyX.insert(std::pair<int,int>(elem,1));
        if (result.second == false)
        {
            result.first->second++;
        }     
    }
    return frequencyX; 
}

