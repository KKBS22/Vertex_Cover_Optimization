#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <vector>
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <bits/stdc++.h>
#include <memory>
#include <fstream>
#include <string.h>
#include <pthread.h>
#include <time.h>

using namespace std;
using namespace Minisat;

vector<int> output_CNF;
vector<int> output_APPROX1;
vector<int> output_APPROX2;

int edge_empty_flag=0;

const std::string WHITESPACE = " \n\r\t\f\v";

int vertex;
std::vector< std::pair <int,int> > edge_database;

/*
#define handle_error(msg) \
               do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
*/


// REF: https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
// to remove white space from start
std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

// to remove white space from start
std::string rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

// to remove white space
std::string trim(const std::string& s)
{
    return rtrim(ltrim(s));
}


// to find no of vertex from input string line
int find_no_of_vertex(std::string str)
{
    int num = 0;
    int vertex=0; // to store no. of vertex
    int n = str.length();

    while(num < n) // run loop for entire string
    {
        if(isdigit(str.at(num)))
    	{
    		vertex = vertex*10 + (int(str[num])-48); // if digit, update no. of vertex
    	}
        num++;
    }
    return vertex;
}

// to check edge format from input string line
int find_edge_error(std::string str, int vertex)
{
    int i=0;    // loop variable
    int j=0;    // variable to store digit
    int k=0;    // loop variable
    //int n = str.length();

    while(str[i] != '}')
	{
        if(str[i] != '{')
        {
            k=1;
        }

        if(k==1)
        {
            if(isdigit(str.at(i)))
        	{
    	    	j = j*10 + (int(str[i])-48);
    	    }
            else
            {
                if(j>=vertex)
                {
                    return 0; // if any digit exceeds no. of vertex, return false
                }
                else if(str[i] != ',')
                {
                    j=0;
                }
                else if(str[i] != '>')
                {
                    j=0;
                }
                else if(str[i] != '<')
                {
                    j=0;
                }
            }
        }
        i++;
	}
    return 1; // if all digits within limit of vertex, return true
}

// to create edge database
void add_edge(std::string str, int vertex, std::vector< std::pair <int,int> >& vect)
{
    int i=0;    // loop variable
    int j=0;    // variable to store digit
    int k=0;    // loop variable
    //int n = str.length();
    int num1=0;
    int num2=0;
    int control=0;
    while(str[i] != '}')
	{
        if(str[i] != '{')
        {
            k=1;
        }

        if(k==1)
        {
          if(isdigit(str.at(i)))
        	{
    	    	j = j*10 + (int(str[i])-48);
    	    }
            else
            {
                if(str[i] == ',' && control==1)
                {
                    num1 = j;
                    j=0;
                }
				else if(str[i] == ',' && control==0)
                {
                    //num1 = j;
                    j=0;
                }
                else if(str[i] == '>')
                {
                    num2 = j;
                    j=0;
                    //std::cout << "num 1 is "<< num1<< " and num 2 is "<< num2<< std::endl;
		    vect.push_back(std::make_pair(num1,num2));
		    control = 0;
                }
                else if(str[i] == '<')
                {
                    j=0;
		    control=1;
                }
            }
        }
        i++;
	}
}

int empty_edge(std::string str, int vertex)
{
	int i=0;    // loop variable
    	int k=0;    // loop variable
	//int n = str.length();

	while(str[i] != '}')
        {
        if(str[i] != '{')
        {
            k=1;
        }

        if(k==1)
        {
            if(isdigit(str.at(i)))
            {
			k=2;
            }	
            else if(str[i] == ',')
            {
                 k=2;
            }
            else if(str[i] == '>')
            {
                 k=2;
            }
            else if(str[i] == '<')
            {
                    k=2;
            }
        }
        i++;
        }
	
	if(k==1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int find_highest_degree(int vertex, std::vector< std::pair <int,int>> vect_edges)
{
	int highest_degree=0;
	int highest_degree_count=0;
	int count=0;
	for(int i=0; i<vertex; i++)
	{
		count =0;
		for(const auto& data : vect_edges) 
		{
        		//std::cout << data.first << " " << data.second << std::endl;
			if(i==data.first)
			{
				count++;
			}
			else if(i==data.second)
			{
				count++;
			}

			if(count>highest_degree_count)
			{
				highest_degree=i;
				highest_degree_count=count;
			}	
    		}		
	
	}

	return highest_degree;
}


void APPROCX_VC_1(int vertex, std::vector< std::pair <int,int>> vect_edges) {
	std::vector< std::pair <int,int>> initial_vect_edges;	
	std::vector< std::pair <int,int>> temp_vect_edges;	
	//std::vector<int> Final_ans;	
	
	initial_vect_edges=vect_edges;
	int highest_degree;

	while(!initial_vect_edges.empty())
	{
		highest_degree = find_highest_degree(vertex, initial_vect_edges);
        	//std::cout << "Highest degree vertex is " <<highest_degree <<std::endl;
	
		// add vertex with highest degree to final ans
		output_APPROX1.push_back(highest_degree);

		// remove edges connected to highest degree vertex

		temp_vect_edges.clear();
		for(const auto& data : initial_vect_edges)
                {
        		//std::cout << data.first << " " << data.second << " and highest degree is "<< highest_degree <<std::endl;
                        if(highest_degree!=data.first && highest_degree!=data.second)
                        {
				temp_vect_edges.push_back(data);
                        }
                }
		initial_vect_edges.clear();
		initial_vect_edges=temp_vect_edges;
	}	
	
	sort(output_APPROX1.begin(), output_APPROX1.end());
	
	std::vector<int>::iterator iter;
    
    /*for (iter = Final_ans.begin() ; iter != Final_ans.end(); ++iter)
    {
         std::cout << *iter << " ";
    }
    std::cout << std::endl;*/
	
}


void Solve_minisat(int vertex, std::vector< std::pair <int,int>>& vect_edges)
{
	int upper_bound = vertex;
	int mid = vertex/2;
	int lower_bound = 1;
	int i=0; //loop variable
	int j=0; //loop variable
	int k=0;
	bool test;

	Minisat::Solver solver;
	//std::vector <int> Final_ans;

	while(lower_bound <= upper_bound)
	{
		Minisat::Solver solver;
		Minisat::Lit x[mid+1][vertex];

		// add all clauses
		for(i = 0; i<mid; i++)						
		{
			for(j = 0; j<vertex; j++)
			{
				x[i][j] = Minisat::mkLit(solver.newVar());
			}
		}

		for(k = 0 ; k < vertex; k++)		
		{
			for (i =0; i<mid;i++)
			{
				for(j = i+1;j<mid;j++)
				{
					solver.addClause(~x[i][k],~x[j][k]);
				}
			}
		}

		for(k = 0; k<mid; k++)
		{
			for(i = 0; i<vertex; i++)
			{
				for(j = i+1; j<vertex ; j++)
				{
					solver.addClause(~x[k][i], ~x[k][j]);
				}
			}
			Minisat::vec<Minisat::Lit>ps;
			i=0;
			while(i<vertex)
			{
				ps.push(x[k][i]);
				i++;
			}
			solver.addClause(ps);
		}

		for (std::pair <int, int>edge:vect_edges)
		{
			Minisat::vec<Minisat::Lit>ps;
			i=0;
			while(i<mid)
			{
				ps.push(x[i][edge.first]);
				ps.push(x[i][edge.second]);
				i++;
			}
			solver.addClause(ps);
		}

		// check solution
		test = solver.solve();
		
		if(test!=true)
		{
			lower_bound = mid+1;
		}
		else
		{
			output_CNF.clear();
                        for(i = 0; i<mid ; i++)
                        {
                                for(j = 0; j<vertex;j++)
                                {
                                        if(solver.modelValue(x[i][j]) == Minisat::l_True)
                                        {
                                                output_CNF.push_back(j);
                                        }
                                }
                        }
                        upper_bound = mid-1;
		}

		mid = (lower_bound + upper_bound)/2;
	}

	sort(output_CNF.begin(), output_CNF.end());
	
	if(edge_empty_flag==1)
		output_CNF.clear();
}


void APPROCX_VC_2(int vertex, std::vector< std::pair <int,int>> vect_edges) 
{
    std::vector< std::pair <int,int>> edge_data =  vect_edges;
    std::vector< std::pair <int,int>> vect_edge_data;
    while (!edge_data.empty())
    {
        
        std::pair <int,int> temp_pair = std::make_pair(edge_data[0].first, edge_data[0].second);
        vect_edge_data.push_back(temp_pair);
        edge_data.erase(edge_data.begin()+0);
        for (int i = edge_data.size()-1; i >= 0; i--)
        {
           if ((temp_pair.first == edge_data[i].first) || (temp_pair.first == edge_data[i].second) || (temp_pair.second == edge_data[i].first) || (temp_pair.second == edge_data[i].second))
            {
              edge_data.erase(edge_data.begin()+i);
            } 
        } 
    }
    if (vect_edge_data.size()>0)
    {
        for (auto &elem : vect_edge_data)
        {
            output_APPROX2.push_back(elem.first);
        }
        for (auto &elem : vect_edge_data)
        {
            output_APPROX2.push_back(elem.second);
        }
        sort(output_APPROX2.begin(), output_APPROX2.end());
        
    }
    
	//std::cout << "code for APPROCX_VC_2 need to be added here!!!"<<std::endl;

}


void* APPROX_VC_1_thread(void* arg) {

	clock_t start, finish;
	double duration;

	start = clock();
	APPROCX_VC_1(vertex, edge_database);
	//std::cout << "Yes thread 2 is also running!!!"<<std::endl;
	finish = clock();
	
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	//cout << "the duration APPROX_V1 time is: " << duration << endl;
	
    //std::cout << "Vertex is "<< vertex <<std::endl;
	
	//for(const auto& data : edge_database)
    //{
    //    	std::cout << data.first << " " << data.second << " are the edge pair" <<std::endl;
    //}
}


void* CNF_SAT_VC_thread(void* arg) {

	clock_t start, finish;
	double duration;

	start = clock();
	Solve_minisat(vertex, edge_database);
	//std::cout << "Yes thread 1 is also running!!!"<<std::endl;
	finish = clock();
	
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	//cout << "the duration CNF_SAT time is: " << duration << endl;
	
}

void* APPROX_VC_2_thread(void* arg) {

        clock_t start, finish;
        double duration;

        start = clock();
        APPROCX_VC_2(vertex, edge_database);
        //std::cout << "Yes thread 3 is also running!!!"<<std::endl;
        finish = clock();

        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        //cout << "the duration APPROX_V2 time is: " << duration << endl;

    //std::cout << "Vertex is "<< vertex <<std::endl;

        //for(const auto& data : edge_database)
    //{
    //          std::cout << data.first << " " << data.second << " are the edge pair" <<std::endl;
    //}
}

void print_final_output() {
	
	int i=0;
	cout << "CNF-SAT-VC: ";
	while(i < output_CNF.size())
	{	
		if (i < output_CNF.size()-1) {
                        cout << output_CNF[i] << ",";
                }
                else {
                        cout << output_CNF[i];
                }
		i++;
	}
	
	cout << "\n";

	i=0;
	cout << "APPROX-VC-1: ";
	
	while(i < output_APPROX1.size())
	{
		if (i < output_APPROX1.size()-1) {
                        cout << output_APPROX1[i] << ",";
                }
                else {
                        cout << output_APPROX1[i];
                }
		i++;	
	}

	cout << "\n";

	i=0;
        cout << "APPROX-VC-2: ";

        while(i < output_APPROX2.size())
        {
                if (i < output_APPROX2.size()-1) {
                        cout << output_APPROX2[i] << ",";
                }
                else {
                        cout << output_APPROX2[i];
                }
                i++;
        }

        cout << "\n";

}

// static void pclock(char *msg, clockid_t cid)
//        {
//            struct timespec ts;

//            printf("%s", msg);
//            if (clock_gettime(cid, &ts) == -1)
//                handle_error("clock_gettime");
//            printf("%4jd.%03ld\n", (intmax_t) ts.tv_sec, ts.tv_nsec / 1000000);
//        }



void compare_algo(int vertex, std::vector< std::pair <int,int>> vect_edges)
{
	int t0,t1,t2;
	pthread_t thread0, thread1, thread2;
    //clockid_t cid;

	t0 = pthread_create(&thread0, NULL, CNF_SAT_VC_thread, NULL);
    // s = pthread_getcpuclockid(thread0,&cid);
    // if (s !=0 )
    // {
    //     handle_error_en(s, "pthread_getcpuclockid");
    // }
    // pclock("CNF Time :", cid);
	if(t0) _exit(1);
	t1 = pthread_create(&thread1, NULL, APPROX_VC_1_thread, NULL);
    // s = pthread_getcpuclockid(thread1,&cid);
    // if (s !=0 )
    // {
    //    handle_error_en(s, "pthread_getcpuclockid");
    // }
    // pclock("APPROX 1 Time :", cid);

	if(t1) _exit(1);
	t2 = pthread_create(&thread2, NULL, APPROX_VC_2_thread, NULL);
    // s = pthread_getcpuclockid(thread2,&cid);
    // if (s !=0 )
    // {
    //     handle_error_en(s, "pthread_getcpuclockid");
    // }
    // pclock("APPROX 2 Time :", cid);
	if(t2) _exit(1);

	pthread_join(thread0, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	print_final_output();

	output_CNF.clear();
        output_APPROX1.clear();
        output_APPROX2.clear();

}

void* call_IO_thread(void* arg) {


    std::string line;          //for input
    std::string trimmed_line;  //input lines with removed extra spaces in stating and ending        
    int control=0;             //variable to transfer control between various function
    int check_edge;           //variable to store if edges are within limit

    //int vertex;
    //std::vector< std::pair <int,int> > edge_database;
    
    // read from stdin until EOF
    while (!std::cin.eof()) 
    {
        // read a line of input until EOL and store in a string
        std::getline(std::cin, line);
        trimmed_line = trim(line);  // remove extra white space from start & end of input 

        if((trimmed_line[0]=='v' || trimmed_line[0]=='V'))  
        {
            control=1;
            vertex = find_no_of_vertex(trimmed_line);  // store number of vertex
			edge_database.clear();
        }
        else if((trimmed_line[0]=='e' || trimmed_line[0]=='E'))
        {
            if(control!=1)
            {
                std::cout << "Error: Incorrect input order, please enter V first"<<std::endl;
            }
            else
            {
                check_edge=find_edge_error(trimmed_line, vertex);
                if(check_edge==1)
                {
                    //std::cout << "Cool!!! Ecerything looks fine"<<std::endl;
                    add_edge(trimmed_line, vertex, edge_database); // create a database
		    edge_empty_flag=empty_edge(trimmed_line, vertex);		    
		    //std::cout << "Yes thread is running!!!"<<std::endl;
					compare_algo(vertex, edge_database);
					//Solve_approx1(vertex, edge_database);          // solve using minisat
                }
                else
                {
                    std::cout << "Error: edge exceeds vertex list"<<std::endl;
                }
            control=0;
            }     
        }
    }
}


int main(int argc, char** argv) {

	int th1;
	pthread_t IO_thread;

	th1 = pthread_create(&IO_thread, NULL, call_IO_thread, NULL);
	if (th1) return 0;
	
	pthread_join(IO_thread, NULL);
	return 0;
}
