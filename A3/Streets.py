class Streets:
    streetName = None
    xPos = None
    yPos = None
    streetCoordinate = [xPos,yPos]
    streetPath = []
    streetLength = None
    streetWays = []
    streetIntersect = []

    def __init__(self):
        self.streetName = ""
        self.xPos = 0
        self.yPos = 0
        self.streetCoordinate = [self.xPos, self.yPos]

    def updateStreet(self, updatePath):
        self.streetPath = updatePath
        pass

    def removeStreet(self):
        pass

    #ToDo
    def lengthOfStreet(self):
        pass

    def noOfStreets(self):
        return (len(self.streetPath) -1)

    def updateVertex(self):
        pass


