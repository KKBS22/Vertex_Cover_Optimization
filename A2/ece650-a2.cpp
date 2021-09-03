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
    // Print command line arguments that were used to start the program
    // std::cout << "Called with " << argc << " arguments\n";
    // for (int i = 0; i < argc; ++i)
    //     std::cout << "Arg " << i << " is " << argv[i] << "\n";

    // // separator character
    // const char comma = ',';

    // read from stdin until EOF
    while (!std::cin.eof()) {



        std::regex rVertex(R"([vV]\s*?[0-9]+)");
        std::regex rPath(R"([sS]\s*?[0-9]+\s*?[0-9]+)");
        std::regex rEdgeList(R"([eE]\s*?\{\s*(<\s*?[0-9]+\s?,\s*?[0-9]+\s*?>\s*?,\s*?)+(<\s*?[0-9]+\s*?,\s*?[0-9]+\s*?>)+\s*\})");

        std::smatch rPathStatus,rVertexStatus,rEdgeStatus;




        // read a line of input until EOL and store in a string
        std::string line;
        std::getline(std::cin, line);
        
        auto s1 = std::regex_match(line,rVertexStatus,rVertex);
        auto s2 = std::regex_match(line,rEdgeStatus,rEdgeList);
        auto s3 = std::regex_match(line,rPathStatus,rPath);

        if (s1)
        {
           vertexNum =  parseVertex(line);
           
        }

        if (s2)
        {
            EdgeData = parseEdges(line,vertexNum);
        }
        if (s3)
        {
            shorPathData = parseSourceDestination(line);
            GraphList *test = new GraphList(vertexNum);
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
            }
            else
            {
                std::cerr<<"Error : Path does not exist";
            }
            
            
            
            
    }
        // create an input stream based on the line
        // we will use the input stream to parse the line
        //std::istringstream input(line);

        // we expect each line to contain a list of numbers
        // this vector will store the numbers.
        // they are assumed to be unsigned (i.e., positive)
        //std::vector<unsigned> nums;


        // while there are characters in the input line
        // while (!input.eof()) {
        //     unsigned num;
        //     char command;

        //     //parse string
        //     input >> command;

        //     // parse an integer
        //     input >> num;
        //     if (input.fail()) {
        //         std::cerr << "Error parsing a number\n";
        //         break;
        //     }
        //     else
        //         nums.push_back(num);

        //     // if eof bail out
        //     if (input.eof())
        //         break;

        //     // read a character
        //     // Note that whitespace is ignored
        //     char separator;
        //     input >> separator;

        //     // if error parsing, or if the character is not a comma
        //     if (input.fail() || separator != comma) {
        //         std::cerr << "Error parsing separator\n";
        //         break;
        //     }
        // }

        // // done parsing a line, print the numbers
        // if (!nums.empty()) {
        //     std::cout << "\nYou have entered " << nums.size() << " numbers: ";
        //     size_t i = 0;
        //     for (unsigned x : nums) {
        //         std::cout << x;
        //         // print a comma if not the last number
        //         i++;
        //         if (i < nums.size()) std::cout << ",";
        //     }
        // }
        // std::cout << std::endl;
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
        std::regex rNew(R"(\s*?\<[0-9]+,[0-9]+\s*?\>)");
        std::smatch vPOints3;
        std::smatch vPOintsNew;
        std::smatch vPOintsTest;
        std::vector<Edge> edgeList;

        auto vt = std::regex_match(lineData,vPOintsTest,r3);

        if (vt)
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
