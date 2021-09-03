class Vertex:
    adjacencyList = {}
    doesIntersect = None
    streetNames = None
    orginalStreet = None
    endPoint = None
    point = ()
    name = None
    pointPos = None

    def __init__(self):
        self.adjacencyList = {}
        self.doesIntersect = None
        self.orginalStreet = None
        self.streetNames = []
        self.endPoint = None
        self.point = ()
        self.name = None
        self.pointPos= None


    def createVertex(self,vNum,street,endPointState,crossPointState,streetName):
        self.adjacencyList = {}
        self.doesIntersect = crossPointState
        self.endPoint = endPointState
        self.point = street
        self.orginalStreet = False
        self.name = vNum
        if len(streetName) >1:
            for a in range(len(streetName)):
                self.streetNames.append(streetName[a])
        else:
            self.streetNames.append(streetName[0])


    def createVertexOrg(self,vNum,street,endPointState,crossPointState,orgStreet,streetName):
        self.adjacencyList = {}
        self.doesIntersect = crossPointState
        self.endPoint = endPointState
        self.point = street
        self.orginalStreet = orgStreet
        self.name = vNum
        if len(streetName) >1:
            for a in range(len(streetName)):
                self.streetNames.append(streetName[a])
        else:
            self.streetNames.append(streetName[0])


    def addToDict(self,vertexData):
        res = [v.point  for v in self.adjacencyList.values()]
        addSuccess = False
        if vertexData.point not in res:
            self.adjacencyList.update({vertexData.name : vertexData})
            addSuccess = True
        return addSuccess

    #Not used
    def addVertex(self,vNum,street):
        self.doesIntersect = True
        self.endPoint = False
        self.name = vNum
        self.point = street
        res = [v.point  for v in self.adjacencyList.values()]
        addSuccess = False
        if self.point not in res:
            self.adjacencyList.update({self.name : self})
            addSuccess = True
        return addSuccess

    #Not used
    def addVertexEndPoints(self,vNum,street):
        self.doesIntersect = False
        self.endPoint = True
        self.name = vNum
        self.point = street
        res = [v.point  for v in self.adjacencyList.values()]
        addSuccess = False
        if self.point not in res:
            self.adjacencyList.update({self.name : self})
            addSuccess = True
        return addSuccess


    def displayVertex(self):
        if len(self.adjacencyList) ==0:
            print('V = { \n')
            print('} \n')
        else:
            print('V = { \n')
            for keys, value in self.adjacencyList.items():
                vXFormat = round(value.point[0],2)
                vYFormat = round(value.point[1],2)
                formatPoint = (vXFormat,vYFormat)
                print ('{0} : {1} \n'.format(keys,formatPoint))
            print('} \n')




    
        
