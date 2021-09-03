#!/usr/bin/env python3
import sys
import Streets as st
import StreetUtil as su
import Graph as gp
import Vertex as vt
import re
from io import StringIO

# YOUR CODE GOES HERE
totalStreets = []
def main():
    # YOUR MAIN CODE GOES HERE
    try:
        global totalStreets
        generated =0 

       
    # sample code to read from stdin.
    # make sure to remove all spurious print statements as required
    # by the assignment
        while True:
            #print("Inside Python")
            line = sys.stdin.readline()
            cCommand = su.checkCommandType(line)
            
            #myStreet.streetName , myStreet.streetPath = su.parseInput(line)
            if cCommand == 'a':
                myStreet = st.Streets() 
                cmdData = su.checkInput(line)
                command = cmdData.group(1)
                sName = cmdData.group(3)
                sCData = cmdData.group(5)
                myStreet.streetName = su.validateData_Name(sName)
                path = []
                path = su.convertToStreet_Coordinate(sCData)
                myStreet.streetPath = path
                waysG = tuple()
                waysG =su.generateStreetWays(myStreet.streetPath)
                myStreet.streetWays = waysG
                if len(totalStreets) == 0:
                    totalStreets.append(myStreet)
                else:
                    pos,res = su.checkNames(myStreet.streetName, totalStreets)
                    if res != True:
                        totalStreets.append(myStreet)
                    else:
                        raise Exception('Street already present choose change command to update')
            
            if cCommand == 'r':
                rStreet = st.Streets() 
                cmdData = su.checkInput(line)
                command = cmdData.group(1)
                sName = cmdData.group(3)
                rStreet.streetName = su.validateData_Name(sName)
                if len(totalStreets) != 0:
                    pos,res = su.checkNames(rStreet.streetName, totalStreets)
                    if res == True:
                        totalStreets.pop(pos)
                    else:
                        print('Street {0} Not yet created  '.format(sName))
                else:
                    raise Exception('Street list is empty please add street data to remove')


            if cCommand == 'c':
                cStreet = st.Streets() 
                cmdData = su.checkInput(line)
                command = cmdData.group(1)
                sName = cmdData.group(3)
                sCData = cmdData.group(5)
                cStreet.streetName = su.validateData_Name(sName)
                path = []
                path = su.convertToStreet_Coordinate(sCData)
                cStreet.streetPath = path
                cStreet.streetWays = su.generateStreetWays(cStreet.streetPath)
                if len(totalStreets) != 0:
                    pos,res = su.checkNames(cStreet.streetName, totalStreets)
                    if res == True:
                        totalStreets[pos].streetPath = cStreet.streetPath
                        totalStreets[pos].streetWays = cStreet.streetWays
                    else:
                        raise Exception('Street does not exist to change the data')
                else:
                    raise Exception('Unable to change the street data')


            if cCommand == 'g':
                generated +=1
                noOfStreets = len(totalStreets)
                if noOfStreets <=1:
                    raise Exception('Generating graphs need more than one streets')

                #Generate Vertex Dictionary
                vertexDict = su.generateVertexDict(totalStreets,noOfStreets)
                newVertex = vt.Vertex()
                #newKeys = list(range(1,len(vertexDict.adjacencyList)+1,1))
                newKeys = list(range(0,len(vertexDict.adjacencyList),1))
                final_dict = dict(zip(newKeys,list(vertexDict.adjacencyList.values())))
                keyOri = list(vertexDict.adjacencyList.keys())
                ##maxVal = max(keyOri)
                valOri = list(vertexDict.adjacencyList.values())
                newVertex.adjacencyList = final_dict

                lenOfVertex = len(vertexDict.adjacencyList)
                #lenOfVertex +=1
                ##maxVal += 1
                vertexDisp = "V " + str(lenOfVertex)
                print(vertexDisp,file=sys.stdout, end="\n", flush=True)
                #sys.stdout.write(vertexDisp)

                keyNew = list(final_dict.keys())
                valNew = list(final_dict.values())
                modList = []
                
                for vO in vertexDict.adjacencyList.values():
                    for vM in final_dict.values():
                        if vO == vM:
                            p1 = valOri.index(vO)
                            p2 = valNew.index(vM)
                            posOri = keyOri[p1]
                            posNew = keyNew[p2]
                            modItem = [posOri,posNew]
                            modList.append(modItem)

                changeList = []

                for a in range(len(modList)):
                    if modList[a][0] !=  modList[a][1]:
                        changeList.append(modList[a])

                #vertexDict.adjacencyList = final_dict
                #vertexDict.displayVertex()
                #newVertex.displayVertex()
                #final_dict.displayVertex()

                #Generate graph with vertex dictionary information
                graphData = gp.Graph(totalStreets,vertexDict)
                # print(graphData.graphList[2])
                # print(type(graphData.graphList[2]))
                # print(len(graphData.graphList[2]))
                #graphData.displayGraph()
                old_stdout = sys.stdout
                sys.stdout = myStdOut = StringIO()
                graphData.displayGraph_a2(changeList)
                sys.stdout = old_stdout
                newGraph = myStdOut.getvalue()
                res_string = newGraph
                print(res_string, file=sys.stdout, end="\n", flush=True)
                
                graphData.graphListClean.clear()
                graphData.graphList.clear()
                graphData.graphListVV.clear()
                # for a in modList:
                #     if a[0] != a[1]:
                #         Ori = str(a[0])
                #         NewVal1 = str(a[1])
                #         res_string = re.sub('([0-9]*)@',NewVal1,res_string)
                
                #print("s 1 2", file=sys.stdout, end="\n", flush=True)
                #sys.stdout.write(res_string)
                #print(modGraph)             
            
            if not line:
                break

            if cCommand == ' ':
                break
        sys.exit(0)

    except Exception as e:
        print("Error : \n" + str(e), file=sys.stderr)



if __name__ == "__main__":
    main()
