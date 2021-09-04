# Vertex_Cover_Optimization
Vertex Cover is a problem on finding a set of vertices that includes at least one endpoint of every edge of the graph, it is a classical optimization problem and is used in this project to find the minimum number of locations where a CCTV camera can be placed for complete surveillance of traffic incidents.

# Technology
* Languages : Python, C++
* Tools : CMake, Minisat
* Keywords : Multithreading, Linux Process, Multiprocessing


# Assignments

All assignments are part of ECE 650 course at Waterloo

## Assignment 1 [A1]

### Input
The input comprises lines each of which specifies a command. There are 4 kinds of commands that can be entered:
* add a street - command - a
* change a street - command - c
* remove a street - command - r
* generate a graph - command - g 

Here is an example of how your program should work. Visualizing this example using the Cartesian
coordinate system may help you understand what’s going on 

```Python
a "Weber Street" (2,-1) (2,2) (5,5) (5,6) (3,8)
a "King Street S" (4,2) (4,8)
a "Davenport Road" (1,4) (5,8)
g
```

### Output

V : Is the set of co-ordinates
E : Is the set of edges that from an undirected graph

```Python
V={
  1: (2,2) 
  2: (4,2) 
  3: (4,4) 
  4: (5,5) 
  5: (1,4) 
  6: (4,7) 
  7: (5,6) 
  8: (5,8) 
  9: (3,8) 
  10: (4,8)
} 

E={
  <1,3>,
  <2,3>,
  <3,4>,
  <3,6>,
  <7,6>,
  <6,5>,
  <9,6>,
  <6,8>,
  <6,10>
}
```

## Assignment 2 [A2]

For this assignment, you need to write a program that takes input till it sees an EOF.
* One of the kinds of input contributes towards the specification of an undirected graph.
* Another kind of input asks you to print out a shortest-path from one vertex to another in the
current graph.

### Input
```Python
$ ./a2ece650
V 15
E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}
```

### Output
```Python
s 2 10
2-8-10
```

## Assignment 3 [A3]

For this assignment, you are to:
* Modify the output format of your Python script from Assignment 1 to match the input format
of your C++ program from Assignment 2.
* Modify your C++ program from Assignment 2 to output the input graph on standard output.
* Write a program in C++ to generate random input for your Python script.
* Write a driver program in C++ that uses Inter-Process Communication (IPC) to link the
output of the random input generator to the input of the Python script, and the output of the
Python script to the input of the C++ program from Assignment 2.

### Input
```Python
$ cd build
$ cmake ../
$ make install
$ cd ./run/bin
$ ./a3ece650 -s 5 -n 4 -l 5
```

### Output
```Python
V 8
E {<0,2>,<0,3>,<0,4>,<1,3>,<4,7>,<5,2>,<5,6>}
s 2 4
2-0-4
```

## Assignment 4 [A4]

For this assignment, you are to augment your code from Assignment 2 to solve the minimal Vertex Cover problem for the input graph. 
Your approach is based on a polynomial time reduction to CNF- SAT, and use of a SAT solver. The following are the steps you should take for this assignment.

### SAT Solver

A SAT solver is a tool that takes as input a CNF formula and outputs either a satisfying Boolean assignment to the variables used in the CNF formula if the formula is consistent or UNSAT if it is not.

We will be using MiniSat SAT solver available at https://github.com/agurfinkel/minisat
MiniSat provides a CMake build system. You can compile it using the usual sequence:

```Python
cd PROJECT && mkdir build && cd build && cmake ../ && make
```

### Incorporate SAT
Create a polynomial reduction of the decision version of VERTEX COVER to CNF-SAT. We have discussed the reduction in class. 
It is also available under the name a4 encoding.pdf on LEARN. You are allowed to use your own reduction provided it is sound and polynomial-time. 
Implement the reduction and use minisat as a library to solve the minimum VERTEX COVER problem for the graphs that are input to your program (as in Assignment 2).

As soon as you get an input graph via the ’V’ and ’E’ specification you should compute a minimum-sized Vertex Cover, and immediately output it. 
The output should just be a sequence of vertices in increasing order separated by one space each. You can use qsort(3) or std::sort for sorting.

Assuming that your executable is called a4-ece650, the following is a sample run of your program:

#### Input 
```Python
$ ./a4-ece650
V 5
E {<0,4>,<4,1>,<0,3>,<3,4>,<3,2>,<1,3>} 
```
#### Output
```Python
3 4
```
The lines starting with V and E are the inputs to your program, and the last line is the output.
Note that the minimum-sized vertex cover is not necessarily unique. You need to output just one of them.

## Final Project
You should augment your code from Assignment 4 in the following ways.
* Make it multithreaded. You should have at least 4 threads: one for I/O, and one each for the different approaches to solve the minimum vertex cover problem.
* Implement the following two additional ways to solve MIN-VERTEX-COVER, in addition to the REDUCTION-TO-CNF-SAT approach you had in Assignment 4. (We will call your approach from Assignment 4, CNF-SAT-VC.)
(1). Pick a vertex of highest degree (most incident edges). Add it to your vertex cover and throw away all edges incident on that vertex. Repeat till no edges remain. We will call this algorithm APPROX-VC-1.
(2). Pick an edge ⟨u,v⟩, and add both u and v to your vertex cover. Throw away all edges attached to u and v. Repeat till no edges remain. We will call this algorithm APPROX- VC-2.

### Input
As input, use the output of /home/agurfink/ece650/graphGen/graphGen on ecelinux. That program generates graphs with the same number of edges for a particular number of vertices, but not necessarily the same edges.

### Output
Given a graph as input, your program should output the vertex cover computed by each approach in sorted order. That is, give the following input:
```Python
V 5
E {<2,1>,<2,0>,<2,3>,<1,4>,<4,3>}
```

The output from your program should be:
```Python
CNF-SAT-VC: 2,4
APPROX-VC-1: 2,4
APPROX-VC-2: 0,2,3,4
```



