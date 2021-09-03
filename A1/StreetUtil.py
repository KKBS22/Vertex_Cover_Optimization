import re
import sys
import Streets
import Vertex as vt
import datetime

# data = 'a "Weberstreet" (1,2)(2,3)(3,4)'
# print(data)

#Tododata
def validateData_Name(nText):
    matchedValue = re.search('(\"[a-zA-Z0-9\D]*\s?[a-zA-Z0-9\D]*?\")',nText)
    name = matchedValue.group(1)
    return name

#ToDo
def validateData_Coordinate(cText):
    cValues = re.findall('(\d+)',cText)
    res = [int(i) for i in cValues]
    return res


def convertToStreet_Coordinate(cText):
    cValues = re.findall('(\([-+]?\d+\,[-+]?\d+\))+?',cText)
    noOfCordinates = len(cValues)
    street = []
    for i in range(noOfCordinates):
        values = [int(i) for i in re.findall('([-+]?\d+)',cValues[i])]
        xPos = values[0]
        yPOs = values[1]
        streetCordinate = [xPos,yPOs]
        street.append(streetCordinate)
    if len(street) < 1:
        raise Exception('Enter street co-ordinate correctly')
    return street

#ToDo
def checkNames(sName,tStreets):
    for i in range(len(tStreets)):
        if sName.lower() == tStreets[i].streetName.lower():
            return i , True
    else:
        return 0 , False

#Not used
def parseInput(commandData):
    r = re.search('([acrg])+(\s)+(\"[a-zA-Z0-9]*\")+(\s)+((\([0-9]*\,[0-9]*\)+(\s)?)*)',commandData)
    streetNames = None
    cordinateData = None

    if r != None:
        streetNames = r.group(3)
        cordinateData = r.group(5)

        if r.group(1) == 'a':
            streetNames = validateData_Name(streetNames)
            cordinateData = validateData_Coordinate(cordinateData)

        if r.group(1) == 'c':
            print(r.group(1))

        if r.group(1) == 'r':
            print(r.group(1))

        if r.group(1) == 'g':
            print(r.group(1))
    else:
        raise Exception('Input not in a valid format \n Enter \n a : For adding new street  Ex: a "Weber streer" (1,2) (2,3) (3,4) \n c : Change/update existing street Ex: c "Weber streer" (1,2) (2,3) \n r : Remove existing street  Ex: Ex: r "Weber streer" \n g : To generate graph')


    return streetNames, cordinateData


def checkInput(commandData):
    r = re.search('([acrg])+(\s)+(\"[a-zA-Z0-9\D]*\s?[a-zA-Z0-9\D]*?\")+(\s)+((\([-+]?[0-9]*\,[-+]?[0-9]*\)+(\s)?)*)',commandData)
    if r!= None:
        return r
    else:
        raise Exception('Input not in a valid format \n Enter \n a : For adding new street  Ex: a "Weber streer" (1,2) (2,3) (3,4) \n c : Change/update existing street Ex: c "Weber streer" (1,2) (2,3) \n r : Remove existing street  Ex: Ex: r "Weber streer" \n g : To generate graph')


def checkInputRemove(commandData):
    r = re.search('([acrg])+(\s)+(\"[a-zA-Z0-9]*\")+(\s)?',commandData)
    if r != None:
        return r
    raise Exception('Input not in a valid format \n Enter \n a : For adding new street  Ex: a "Weber streer" (1,2) (2,3) (3,4) \n c : Change/update existing street Ex: c "Weber streer" (1,2) (2,3) \n r : Remove existing street  Ex: Ex: r "Weber streer" \n g : To generate graph')


def checkCommandType(commandData):
    lstCmd = commandData.strip().split()
    if commandData.isspace():
        a = ' '
        return a
    if len(lstCmd) ==0:
        return lstCmd
    else:
        cmd = lstCmd[0]
    r = re.search('([acrg])',cmd)
    if len(cmd) > 1:
        raise Exception('Input not in a valid format \n Enter \n a : For adding new street  Ex: a "Weber streer" (1,2) (2,3) (3,4) \n c : Change/update existing street Ex: c "Weber streer" (1,2) (2,3) \n r : Remove existing street  Ex: Ex: r "Weber streer" \n g : To generate graph')
    elif r == None:
        raise Exception('Input commands not in a valid format \n Enter \n a : For adding new street  Ex: a "Weber streer" (1,2) (2,3) (3,4) \n c : Change/update existing street Ex: c "Weber streer" (1,2) (2,3) \n r : Remove existing street  Ex: Ex: r "Weber streer" \n g : To generate graph')
    else:
        return cmd


def generateVertexDict(tStreets,nStreets):
    intersect = None
    vNumber = 0
    vertexFinalVal = vt.Vertex()
    for i in range(nStreets-1):
        for j in range(nStreets-1):
            if j+i+1 <= nStreets -1:
                streetA = tStreets[i].streetWays
                streetB = tStreets[j+i+1].streetWays
                for k in range(len(streetA)):
                    for l in range(len(streetB)):
                        if (intersectStreets(streetA[k],streetB[l])) or (betweenStreet(streetA[k], streetB[l])):
                            xPos, yPos, status = intersectAtLines(streetA[k], streetB[l])
                            if status == True:
                                for m in streetA[k]:
                                    vNumber +=1
                                    vertexVal = vt.Vertex()
                                    vertexVal.streetNames.clear()
                                    vertexVal.pointPos = tStreets[i].streetPath.index(list(m))
                                    if m == (xPos,yPos):
                                        vertexVal.createVertexOrg(vNumber,m,True,True,True,[tStreets[i].streetName])
                                    else:
                                        vertexVal.createVertexOrg(vNumber,m,True,False,False,[tStreets[i].streetName])
                                    addPointStatus = vertexFinalVal.addToDict(vertexVal)
                                    if addPointStatus == False:
                                        pass
                                for n in streetB[l]:
                                    vNumber +=1
                                    vertexVal = vt.Vertex()
                                    vertexVal.streetNames.clear()
                                    vertexVal.pointPos = tStreets[j+i+1].streetPath.index(list(n))
                                    if n == (xPos,yPos):
                                        vertexVal.createVertexOrg(vNumber,n,True,True,True,[tStreets[j+i+1].streetName])
                                    else:
                                        vertexVal.createVertexOrg(vNumber,n,True,False,False,[tStreets[j+i+1].streetName])
                                    addPointStatus = vertexFinalVal.addToDict(vertexVal)
                                    if addPointStatus == False:
                                        pass
                                vNumber += 1
                                vertexVal = vt.Vertex()
                                vertexVal.streetNames.clear()
                                if ((xPos,yPos) in streetA[k]) or ((xPos,yPos) in streetA[l]):
                                    vertexVal.createVertexOrg(vNumber,(xPos,yPos),True,True,True,[tStreets[i].streetName,tStreets[j+i+1].streetName])
                                else:
                                    vertexVal.createVertexOrg(vNumber,(xPos,yPos),False,True,False,[tStreets[i].streetName,tStreets[j+i+1].streetName])
                                addPointStatus = vertexFinalVal.addToDict(vertexVal)
                                if addPointStatus == False:
                                    for key, value in vertexFinalVal.adjacencyList.items():
                                        if vertexVal.point == value.point:
                                            for m in vertexVal.streetNames:
                                                if m not in vertexFinalVal.adjacencyList[key].streetNames:
                                                    vertexFinalVal.adjacencyList[key].streetNames.append(m)
                                                    vertexFinalVal.adjacencyList[key].doesIntersect = True
                                            if (vertexVal.point in streetA[k]) or (vertexVal.point in streetA[l]):
                                                vertexFinalVal.adjacencyList[key].orginalStreet = True
                                    pass
                                pass
                            else:
                                pass
                        else:
                            pass          
            else:
                break
    return vertexFinalVal


def checkClockwise(A,B,C):
	return (C[1]-A[1])*(B[0]-A[0]) > (B[1]-A[1])*(C[0]-A[0])

#Not Used
def Intersect(pointA,pointB,pointC,pointD):
	return checkClockwise(pointA,pointC,pointD) != checkClockwise(pointB,pointC,pointD) and checkClockwise(pointA,pointB,pointC) != checkClockwise(pointA,pointB,pointD)


def intersectStreets(streetA, streetB):
    return checkClockwise(streetA[0],streetB[0],streetB[1]) != checkClockwise(streetA[1],streetB[0],streetB[1]) and checkClockwise(streetA[0],streetA[1],streetB[0]) != checkClockwise(streetA[0],streetA[1],streetB[1])

#Not Used
def findIntersection(streetA, streetB):
    lnA = len(streetA)
    lnB = len(streetB)

    pass


def intersectAtLines(streetLineA,streetLineB):
    doesIntersect = False
    xCheck = (streetLineA[0][0] - streetLineA[1][0], streetLineB[0][0] - streetLineB[1][0])
    yCheck = (streetLineA[0][1] - streetLineA[1][1], streetLineB[0][1] - streetLineB[1][1])

    value = checkIntersection(xCheck,yCheck)
    if value == 0:
        doesIntersect = False
        x = None
        y = None

    else:
        doesIntersect = True
        d = (checkIntersection(*streetLineA), checkIntersection(*streetLineB))
        x = checkIntersection(d, xCheck) / value
        #xFormat = round(x,2)
        y = checkIntersection(d, yCheck) / value
        #yFormat = round(y,2)

    return x, y, doesIntersect


def checkIntersection(xValue,yValue):
    return xValue[0] * yValue[1] - xValue[1] * yValue[0]
 

def generateStreetWays(street):
    ways = []
    sLength = len(street)
    if sLength-2 >0:
        for i in range(sLength-1):
            if i+1<= sLength-1:
                val1 = (tuple(street[i]),tuple(street[i+1]))
                ways.append(val1)
    else:
        val1 = (tuple(street[0]),tuple(street[1]))
        ways.append(val1)
    return  ways


def streetCollinear(streetA, streetB):
    col = collinearPoints(streetA[0],streetB[0],streetA[1]) or collinearPoints(streetA[0],streetB[1],streetA[1]) or collinearPoints(streetB[0],streetA[0],streetB[1]) or collinearPoints(streetB[0],streetA[1],streetB[1])   
    
    return col 


def collinearPoints(streetA, streetB, streetC):
    area = streetA[0] * (streetB[1] - streetC[1]) + streetB[0] * (streetC[1] - streetA[1]) + streetC[0] * (streetA[1] - streetB[1]) 
    if (area == 0): 
        return True
    else: 
        return False



def findLength(pointA, pointB):
    length = ( (pointB[0]-pointA[0])**2 + (pointB[1]-pointA[1])**2 ) ** 0.5
    return length


def betweenStreet(streetA,streetB):
    if ((findLength(streetA[0],streetB[0]) + findLength(streetA[1],streetB[0]) == findLength(streetA[0],streetA[1])) or 
       (findLength(streetA[0],streetB[1]) + findLength(streetA[1],streetB[1]) == findLength(streetA[0],streetA[1])) or
       (findLength(streetB[0],streetA[0]) + findLength(streetB[1],streetA[0]) == findLength(streetB[0],streetB[1])) or
       (findLength(streetB[0],streetB[1]) + findLength(streetB[1],streetA[0]) == findLength(streetB[0],streetB[1]))):
        return True
    else:
        return False

# def main():
#     try:
#         parseInput(data)

#     except Exception as e:
#             print("Error : \n" + str(e), file=sys.stderr)



# if __name__ == "__main__":
#     main()
    