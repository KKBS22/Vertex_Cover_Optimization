#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<unistd.h>
#include<getopt.h>
#include<time.h>
#include<cmath>
#include<map>

std::ifstream urandom("/dev/random");
int randomXY(int max,int min);
std::string randomName();
int randomUnNum(int max, int min);
void writer(std::string msg, FILE* ostream);
clock_t start,end;
double cpuTimeUsed;


struct point
{
   int pointX =0;
   int pointY =0;
   float pX;
   float pY;
};

struct path
{
  point a;
  point b;
};

class Street    
{
private:
    
public:
    std::vector<point> streetPoints;
    std::vector<path> streetPath;
    std::string streetName;
    int hasDuplicates;
    int sameLinePos;
    std::string addCmd;
    std::string rmCmd;
    point newPoint;
    path newPath;
    Street();
    //~Street();
};

Street::Street()
{
      this->streetPoints = {};
      this->streetPath = {};
      //this->streetName = "";
}

// Street::~Street()
// {

// }

void genStreetPath(Street &a);
int checkDuplicates(Street &a);
int checkOverlap(Street &a,Street &b);
int checkSelfIntersection(Street &a);
std::string generateStreetAddCmd(Street &a);
std::vector<point> randomPoints(int noOfLineSeg,int maxN);
point pointOfIntersection(path line1, path line2);
std::vector<Street> generateRandomStreetSets(int s, int n, int l, int c);
bool intersectStreets(path pOne, path pTwo);
float checkClockwise(point a, point b, point c);
float findLength(point a, point b);
bool betweenStreet(path pOne, path pTwo);
int sameLine(Street &a);

const char* program_name;
char* S;
char* N;
char* L;
char* C;

void print_usage(char *programName)
{
    std::cout<<"Usage : "<<std::endl;
    std::cout<<programName<<std::endl;
    std::cout<<"-h get some help "<<std::endl;
    std::cout<<"-s to enter number of streets "<<std::endl;
    std::cout<<"-n to enter number of line-segments in street"<<std::endl;
    std::cout<<"-l to enter wait period"<<std::endl;
    std::cout<<"-c to enter Co-oridnate data range"<<std::endl;
}

int main(int argc, char **argv)
{
    //std::vector<Street> totalStreets;
    std::vector<int> specs;
    int Si =10;
    int Ni =5;
    int Li =5;
    int Ci =20;
    int errorCode = 0;

    //int childStatus;
    int next_option;
    const char* const short_options = "hs:n:l:c:";

    const struct option long_options[] = {
        {"help", 0, NULL, 'h'},
        {"sVal", 1, NULL, 's'},
        {"nVal", 1, NULL, 'n'},
        {"lVal", 1, NULL, 'l'},
        {"cVal", 1, NULL, 'c'}
    };

    program_name = argv[0];
    while ((next_option = getopt_long(argc,argv,short_options,long_options,NULL))!=-1)
    {
        switch (next_option)
        {
        case 'h':
            print_usage(argv[0]);
            break;
        case 's':
            S = optarg;
            if (S != "")
            {
                Si = atoi(S);
                if (Si<2)
                {
                    errorCode = 1;
                    std::cerr<<"Error : Enter No of street values ge 2"<<std::endl;  
                    exit(1);                  
                }           
            }
            else
            {
                Si =10;
            }
            break;
        case 'n':
            N = optarg;
            if (N != "")
            {
                Ni = atoi(N);
                if (Ni < 2)
                {
                   errorCode =2;
                   std::cerr<<"Error : Enter No of line segment values ge 2"<<std::endl; 
                   exit(1);                  
                }
            }
            else
            {
                Ni =5;
            }           
            break;
        case 'l':
            L = optarg;
            if (L != "")
            {
                Li = atoi(L);
                if (Li < 5)
                {
                    errorCode =3;
                    std::cerr<<"Error : Enter delay values ge 5"<<std::endl; 
                    exit(1);                 
                }               
            }
            else
            {
                Li =5;
            }  
            break;
        case 'c':
            C = optarg;
            if (C != "")
            {
                Ci = atoi(C);
                if (Ci < 2)
                {
                    errorCode=4;
                    std::cerr<<"Error : Enter co-ordinate values ge 1"<<std::endl;
                    exit(1); 
                }               
            }
            else
            {
                Ci =20;
            }  
            break;
        default:
            Si = 10;
            Ni = 5;
            Li = 5;
            Ci = 20;
            break;
        }
    }

    int sleepTime = randomUnNum(Li,5);
    while (true)
    {
        if (errorCode > 0)
        {
            std::cerr<<"Error : Wrong street specification for random street generation "<<std::endl;
            break;
        }
        start = clock();
       
        auto finalStreets = generateRandomStreetSets(Si, Ni, Li,Ci);
        if (!finalStreets.empty())
        {
            
            for (unsigned i = 0; i < finalStreets.size(); i++)
            {
                std::cout<<finalStreets[i].addCmd<<std::endl;
            }
            std::cout<<"g"<<std::endl;
            usleep(sleepTime*1000000);
            for (unsigned i = 0; i < finalStreets.size(); i++)
            {
                 std::cout<<finalStreets[i].rmCmd<<std::endl;
            }
            finalStreets.clear();      
        }
        else
        {
            std::cerr<<"Error : No streets to generate graph"<<std::endl;
        }   
        end = clock();
        //std::cout<<"Time Used : "<<((double)(end-start))/CLOCKS_PER_SEC<<std::endl;     
    }
    urandom.close();
    return 0;
}


void genStreetPath(Street &a)
{
    for (unsigned int i = 0; i < a.streetPoints.size(); i++)
    {
        if (i+1 < a.streetPoints.size() )
        {
            a.newPath.a = a.streetPoints[i];
            a.newPath.b = a.streetPoints[i+1];
            a.streetPath.push_back(a.newPath);
        }    
    }
}

int checkDuplicates(Street &a)
{
    int validStatus = 0;
    for (unsigned int i = 0; i < a.streetPoints.size(); i++)
    {
        for (unsigned int j = i+1 ; j <= (a.streetPoints.size()-1) ; j++)
        {
            if((a.streetPoints[i].pointX == a.streetPoints[j].pointX) && (a.streetPoints[i].pointY == a.streetPoints[j].pointY))
            {
                validStatus += 1;                          
            }
        }       
    }
    
    return validStatus;
}

int sameLine(Street &a)
{
    std::vector<int> xValues,yValues;
    std::map<int,int> frequencyX, frequencyY;
    int totalNum =0;
    int dX =0;
    int dY =0;
    for (unsigned int j = 1; j < a.streetPoints.size(); j++)
    {
        xValues.push_back(a.streetPoints[j].pointX);
        yValues.push_back(a.streetPoints[j].pointY);
       
    }
    for (auto &elem : xValues)
    {
        auto result = frequencyX.insert(std::pair<int,int>(elem,1));
        if (result.second == false)
        {
            result.first->second++;
        }
            
    }

    for (auto &elem : yValues)
    {
        auto result2 = frequencyY.insert(std::pair<int,int>(elem,1));
        if (result2.second == false)
        {
            result2.first->second++;
        }
            
    }

    for (auto &elem : frequencyX)
    {
        if (elem.second >= 3)
        {
            dX = elem.first;
        }          
    }

    for (auto &elem : frequencyY)
    {
        if (elem.second >= 3)
        {
            dY = elem.first;
        }         
    }
    for (unsigned int k = 0; k < a.streetPoints.size(); k++)
    {      
       if ((dX == a.streetPoints[k].pointX)||(dY == a.streetPoints[k].pointY))
       {
           totalNum += 1;
       }
       
    }

    xValues.clear();
    yValues.clear();
    frequencyX.clear();
    frequencyY.clear();
    return totalNum;
    
}

int checkSelfIntersection(Street &a)
{
    int doesNotIntersect = 0;
    int streetPointPos=-1;
    point intersectPoints;
    intersectPoints.pointX =0;
    intersectPoints.pointY =0;
    for (unsigned int i = 0; i < a.streetPath.size(); i++)
    {
        for (unsigned int j = i+1; j <= a.streetPath.size()-1; j++)
        {
            if (intersectStreets(a.streetPath[i], a.streetPath[j]) || betweenStreet(a.streetPath[i],a.streetPath[j]))
            {
                intersectPoints = pointOfIntersection(a.streetPath[i],a.streetPath[j]);
                doesNotIntersect =0;
                for (unsigned k = 0; k < a.streetPoints.size(); k++)
                {
                    if ((intersectPoints.pX ==a.streetPoints[k].pointX) && (intersectPoints.pY == a.streetPoints[k].pointY))
                    {
                     doesNotIntersect +=1 ;
                    }
                }
                if (doesNotIntersect == 0)
                {
                    streetPointPos += 1;
                }
            }  
        }  
    }
    return streetPointPos;
}

//Check street Paths

bool intersectStreets(path pOne, path pTwo)
{
    return (checkClockwise(pOne.a,pTwo.a,pTwo.b) != checkClockwise(pOne.b,pTwo.a,pTwo.b)) &&(checkClockwise(pOne.a,pOne.b,pTwo.a)!=checkClockwise(pOne.a,pOne.b,pTwo.b));
}

float checkClockwise(point a, point b, point c)
{
    return ((c.pointY - a.pointY)*(b.pointX - a.pointX)) > ((b.pointY-a.pointY)*(c.pointX-a.pointX)); 
}

float findLength(point a, point b)
{
    float length;
    length = sqrt(((b.pointX - a.pointX)*(b.pointX - a.pointX))+((b.pointY - a.pointY)*(b.pointY - a.pointY)));
    return length;
}

bool betweenStreet(path pOne, path pTwo)
{
    if ((findLength(pOne.a,pTwo.a) + findLength(pOne.b,pTwo.a) == findLength(pOne.a,pOne.b)) ||
       (findLength(pOne.a,pTwo.b) + findLength(pOne.b,pTwo.b) == findLength(pOne.a,pOne.b)) ||
       (findLength(pTwo.a,pOne.a) + findLength(pTwo.b,pOne.a) == findLength(pTwo.a,pTwo.b)) ||
       (findLength(pTwo.a,pTwo.b) + findLength(pTwo.b,pOne.a) == findLength(pTwo.a,pTwo.b)))
    {
       return true;
    }
    else
    {
        return false;
    }
    
    
}

std::string randomName()
{

    if (urandom.fail())
    {
        std::cerr << "Error : Cannot open /dev/urandom \n";
        return NULL;
    }
    char ch = 'a';
    std::string name= "";
    for (int i = 0; i < 3; i++)
    {
        urandom.read(&ch, 1);
        int val =0;
        val = (65 + (((unsigned int)ch)%(90-65+1)));
        name = name + (char)val;
    }

    
    return name;
}

int randomXY(int max, int min)
{
    if (urandom.fail())
    {
        std::cerr << "Error : Cannot open /dev/urandom \n";
        return 1;
    }
    unsigned int ch = 1;
    //char ch = 'a';
    urandom.read((char*)&ch, 1);
    int val =0;
    val = (min + (((unsigned int)ch)%(max-min+1)));
    return val;
    

}

int randomUnNum(int max, int min)
{
    if (urandom.fail())
    {
        std::cerr << "Error : Cannot open /dev/urandom \n";
        return 1;
    }
    unsigned int ch =1;
    //char ch = 'a';
    urandom.read((char*)&ch, 1);
    int val =0;
    if (max == 10)
    {
        val = 5;
    }
    else
    {
        val = (min + (((unsigned int)ch)%(max-min+1)));
    }
    return val;
}

std::string generateStreetAddCmd(Street &a)
{
    std::string addCmd = "a ";
    char start = '"';

    addCmd = addCmd + start + a.streetName + start + " ";
    for (unsigned int i = 0; i < a.streetPoints.size(); i++)
    {

        std::string streetCor = "(";
        std::string x= std::to_string(a.streetPoints[i].pointX);
        streetCor = streetCor + x + ",";
        std::string y= std::to_string(a.streetPoints[i].pointY);
        streetCor = streetCor + y + ")";
        addCmd = addCmd + streetCor;

    }
    return addCmd;
}

std::string generateStreetremoveCmd(Street &a)
{
    std::string rmCmd = "r ";
    char start = '"';

    rmCmd = rmCmd + start + a.streetName + start;
    return rmCmd;

}

std::vector<point> randomPoints(int noOfLineSeg,int maxN)
{
    point newPoint;
    std::vector<point> sPoints;
    for (int i = 0; i < noOfLineSeg+1; i++)
    {
        newPoint.pointX = randomXY(maxN,-maxN); 
        newPoint.pointY = randomXY(maxN,-maxN);
        sPoints.push_back(newPoint);
    }
    return sPoints;
}

std::vector<Street> generateRandomStreetSets(int s, int n, int l, int c)
{

    int noOfStreets=randomUnNum(s,2);
    int noOfLineSeg=randomUnNum(n,2);
    std::string newName = "";
    std::vector<Street> totalStreets = {};
    for (int j = 0; j < noOfStreets; j++)
    {
        Street *a = new Street();
        newName = randomName();
        for (int i = 0; i < noOfLineSeg+1; i++)
        {
            a->newPoint.pointX = randomXY(c,-c); 
            a->newPoint.pointY = randomXY(c,-c);
            a->streetPoints.push_back(a->newPoint);
        }
        a->streetName = newName;
        genStreetPath(*a);
        a->hasDuplicates = checkDuplicates(*a);
        a->sameLinePos = sameLine(*a);
        //Check for self intersection
        if (noOfLineSeg >1)
        {
            int sPos = checkSelfIntersection(*a);
            if ((sPos >=0) ||(a->hasDuplicates>0) || (a->sameLinePos>= 3))
            {
                int tries = 25;
                while (tries != 0)
                {
                    auto newSPoints = randomPoints(noOfLineSeg,c);
                    a->streetPoints.clear();
                    a->streetPoints = newSPoints;
                    a->hasDuplicates =checkDuplicates(*a);
                    a->sameLinePos = sameLine(*a);
                    a->streetPath.clear();
                    genStreetPath(*a);
                    if ((checkSelfIntersection(*a) >= 0) ||(a->hasDuplicates >0)||(a->sameLinePos>= 3) )
                    {
                        tries -= 1;
                        if(tries ==0 )
                        {    
                            std::cerr<<"Error : Unable to generate streets";
                            exit(1);
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                
            }
            
        }     
        a->addCmd = generateStreetAddCmd(*a);
        a->rmCmd = generateStreetremoveCmd(*a);
        totalStreets.push_back(*a);
    }  
    return totalStreets;

}

point pointOfIntersection(path line1, path line2)
{
    point intersection;
    int x1 = line1.a.pointX;
    int y1 = line1.a.pointY;
    int x2 = line1.b.pointX;
    int y2 = line1.b.pointY;
    int x3 = line2.a.pointX;
    int y3 = line2.a.pointY;
    int x4 = line2.b.pointX;
    int y4 = line2.b.pointY;

    float xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4));
    float xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
    intersection.pX = xnum / xden;

    float ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4);
    float yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
    intersection.pY = ynum / yden;

    return intersection;

}



