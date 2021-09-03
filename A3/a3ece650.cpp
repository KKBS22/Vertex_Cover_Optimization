#include<iostream>
#include<getopt.h>
#include<string>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<vector>

int main (int argc, char **argv)
 {
    
    std::vector<pid_t> kids;
    int RtoA1[2], A1toA2[2];

    pipe(RtoA1);
    pipe(A1toA2);

    pid_t child_pid;
    child_pid = fork();
  

    if (child_pid == 0)
    {
        close(RtoA1[0]);
        dup2(RtoA1[1],STDOUT_FILENO);
        close(RtoA1[1]);

        int rgen  = execv("./rgen",argv); 
        return rgen;

        
    }

    kids.push_back(child_pid);
    child_pid = fork();
    if (child_pid == 0)
    {
        close(RtoA1[1]);
        close(A1toA2[0]);
        
        dup2(RtoA1[0],STDIN_FILENO);
        close(RtoA1[0]);

        
        dup2(A1toA2[1],STDOUT_FILENO);
        close(A1toA2[1]);

        execv("a1ece650.py",argv);
        
    }
    
    kids.push_back(child_pid);
    child_pid = fork();
    if (child_pid == 0)
    {
        close(A1toA2[1]);
        dup2(A1toA2[0],STDIN_FILENO);
        close(A1toA2[0]);
        
        int a2re = execv("./a2ece650",argv);    
        return a2re;
    }

    // kids.push_back(child_pid);
    // child_pid = fork();
    // if(child_pid == 0)
    kids.push_back(child_pid);
    child_pid = 0;


    close(A1toA2[0]);
    dup2(A1toA2[1],STDOUT_FILENO);
    close(A1toA2[1]);

    std::string msg;

    while(!std::cin.eof()) {
            std::getline(std::cin, msg);
            std::cout.flush()<< msg<<std::endl;
    }       
    

        
    for (pid_t t : kids)
    {
        int status;
        kill(t, SIGTERM);
        waitpid(t, &status, 0);
    }
    return 0;

}

