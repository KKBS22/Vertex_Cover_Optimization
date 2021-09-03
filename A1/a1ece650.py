#!/usr/bin/env python3
import sys
import Streets as st
import StreetUtil as su
import Graph as gp
import Vertex as vt

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
            line = sys.stdin.readline()
            cCommand = su.checkCommandType(line)
            
            #myStreet.streetName , myStreet.streetPath = su.parseInput(line)
            if cCommand == 'a':
                if generated > 0:
                    graphData.graphList.clear()
                    vertexDict.adjacencyList.clear()
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
                if generated > 0:
                    graphData.graphList.clear()
                    vertexDict.adjacencyList.clear()
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
                if generated > 0:
                    graphData.graphList.clear()
                    vertexDict.adjacencyList.clear()
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
                vertexDict.displayVertex()

                #Generate graph with vertex dictionary information
                graphData = gp.Graph(totalStreets,vertexDict)
                # print(graphData.graphList[2])
                # print(type(graphData.graphList[2]))
                # print(len(graphData.graphList[2]))
                graphData.displayGraph()

            if not line:
                break

            if cCommand == ' ':
                break

            

   
            #print("read a line:", line)

        #print(totalStreets[0])

        #print("Finished reading input")
        # return exit code 0 on successful termination
        sys.exit(0)

    except Exception as e:
        print("Error : \n" + str(e), file=sys.stderr)



if __name__ == "__main__":
    main()
