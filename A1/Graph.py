import Streets
import Vertex

class Graph:
    graphList = {}
    graphListVV ={}
    graphListClean = {}


    def __init__(self,totalStreets, vertexObj):
        #Vertex -EndPoint Edge
        self.edgePV(totalStreets,vertexObj)
        #VertexIntersect - VertexIntersect
        self.edgeVV(totalStreets,vertexObj)
        #self.graphList.update(self.graphListVV)
        #self.mergeGraph(totalStreets,vertexObj)
        self.graphListClean = self.custom_merge(self.graphList,self.graphListVV)


        pass


    # def cleanGraph(self,vertexObj):
    #     cleanList =[]
    #     key =[]
    #     for k,v in self.graphListClean.items():
    #         if len(v)>2:
    #             aKey = v[0]
    #             avalue = v[1]
    #             subLista =[[ v[0],v[1]]]
    #             nextList = v[2:len(v)]
    #             for j in nextList:
    #                 subLista.append(j)
    #             for a in range(len(subLista)):
    #                 for b in range(len(subLista)-1):
    #                     if vertexObj.adjacencyList[subLista[a][0]].streetNames in vertexObj.adjacencyList[subLista[b][0].streetNames:
    #                         if subLista[a][1] > subLista[b][1]:




    #     pass


    def custom_merge(self,unit1, unit2):
        out = {**unit1, **unit2}
        for key, value in out.items():
            if key in unit1 and key in unit2:
               out[key] = [value , unit1[key]]
        return out


    def displayGraph(self):
        print('E = { \n')
        v = len(self.graphListClean)
        lenTest=0
        for keys, value in self.graphListClean.items():
            lenTest=lenTest+1
            if lenTest < v:
                if len(value)>=2:
                    if type(value[0]) is list:
                        1+1
                    else:
                        aKey = value[0]
                        avalue = value[1]
                        subLista =[[ value[0],value[1]]]
                        nextList = value[2:len(value)]
                        for j in nextList:
                            subLista.append(j)
                        for k in range(len(subLista)):
                            print('<{0},{1}>,'.format(keys,subLista[k][0]))
                if len(value)==2:
                    if type(value[0]) is list:
                        if len(value[0]) >=2:
                            aKey = value[0][0]
                            avalue = value[0][1]
                            subLista =[[ value[0][0],value[0][1]]]
                            nextList = value[0][2:len(value[0])]
                            for j in nextList:
                                subLista.append(j)
                            g = set(tuple(i) for i in subLista)
                    if type(value[0]) is list:
                        if len(value[1]) >=2:
                            aKey = value[1][0]
                            avalue = value[1][1]
                            subListb =[[ value[1][0],value[1][1]]]
                            nextListb = value[1][2:len(value[1])]
                            for j in nextListb:
                                subListb.append(j)
                            f = set(tuple(i) for i in subListb)
                        final = g.union(f)
                        lfinal = list(final)
                        for k in range(len(list(final))):
                            print('<{0},{1}>,'.format(keys,lfinal[k][0]))
            if lenTest ==v:
                if len(value)>=2:
                    if type(value[0]) is list:
                        1+1
                    else:
                        aKey = value[0]
                        avalue = value[1]
                        subLista =[[ value[0],value[1]]]
                        nextList = value[2:len(value)]
                        for j in nextList:
                            subLista.append(j)
                        lenSuba = 0
                        for k in range(len(subLista)):
                            lenSuba=lenSuba+1
                            if lenSuba < len(subLista):
                                print('<{0},{1}>,'.format(keys,subLista[k][0]))
                            if lenSuba == len(subLista):
                                print('<{0},{1}>'.format(keys,subLista[k][0]))
                if len(value)==2:
                    if type(value[0]) is list:
                        if len(value[0]) >=2:
                            aKey = value[0][0]
                            avalue = value[0][1]
                            subLista =[[ value[0][0],value[0][1]]]
                            nextList = value[0][2:len(value[0])]
                            for j in nextList:
                                subLista.append(j)
                            g = set(tuple(i) for i in subLista)
                    if type(value[0]) is list:
                        if len(value[1]) >=2:
                            aKey = value[1][0]
                            avalue = value[1][1]
                            subListb =[[ value[1][0],value[1][1]]]
                            nextListb = value[1][2:len(value[1])]
                            for j in nextListb:
                                subListb.append(j)
                            f = set(tuple(i) for i in subListb)
                        final = g.union(f)
                        lfinal = list(final)
                        lenFinalList = 0
                        for k in range(len(list(final))):
                            lenFinalList = lenFinalList+1
                            if lenFinalList < len(list(final)):
                                print('<{0},{1}>,'.format(keys,lfinal[k][0]))
                            if lenFinalList == len(list(final)):
                                print('<{0},{1}>'.format(keys,lfinal[k][0]))
        print('} \n')


    def edgePV(self,totalStreets, vertexObj):
        if len(vertexObj.adjacencyList) !=0:
            for key, value in vertexObj.adjacencyList.items():
                if value.endPoint == True:
                    for key2, value2 in vertexObj.adjacencyList.items():
                        if (value2.doesIntersect == True):
                            if value.name != value2.name:
                                for a in value.streetNames:
                                    if a in value2.streetNames:
                                        for ts in range(len(totalStreets)):
                                            if a == totalStreets[ts].streetName:
                                                self.checkConditionEdge(value,value2,vertexObj,totalStreets[ts])
        else:
            self.graphList ={}


    def edgeVV(self,totalStreets, vertexObj):
        ypStatus = False
        for key, value in vertexObj.adjacencyList.items():
            if value.doesIntersect == True:
                for key2, value2 in vertexObj.adjacencyList.items():
                    if (value2.doesIntersect == True):
                        if value.name != value2.name:
                            for vI in value.streetNames:
                                for vK in value2.streetNames:
                                    if vI == vK:
                                        for ts in range(len(totalStreets)):
                                            if vI == totalStreets[ts].streetName:
                                                pointOnStreet, statusStreet = self.findStreetWay(value.point,totalStreets[ts])
                                                if statusStreet == True:
                                                    if self.betweenStreet(pointOnStreet,value2.point):
                                                        ypStatus = False
                                                        dVV = self.findLength(list(value.point),list(value2.point))
                                                        newD,stat = self.checkSmallerPointVertex(value,value2,vertexObj,totalStreets[ts])
                                                        if stat == True:
                                                            dictV = newD
                                                        else:
                                                            dValue = [value2.name,dVV]
                                                            dictV = {value.name : [value2.name,dVV]}
                                                        
                                                        if len(self.graphListVV.items()) ==0:
                                                            self.graphListVV.update(dictV)
                                                        
                                                        else:
                                                            for keyi , valuei in dictV.items():
                                                                for keyj, valuej in self.graphListVV.items():
                                                                    if keyi == keyj:
                                                                        if len(self.graphListVV[keyj])>=2:
                                                                            aKey = valuej[0]
                                                                            avalue = valuej[1]
                                                                            subLista =[[ valuej[0],valuej[1]]]
                                                                            if len(self.graphListVV[keyj]) >2:
                                                                                nextList = valuej[2:len(self.graphListVV[keyj])]
                                                                                for j in nextList:
                                                                                    subLista.append(j)
                                                                        for a in range(len(subLista)):
                                                                            if dictV[keyi] not in subLista:
                                                                                if len(self.graphListVV[keyj])>=2:
                                                                                    self.graphListVV[keyj].append(dictV[keyi])
                                                                                else:
                                                                                    self.graphListVV[keyj] = dictV[keyi]
                                                            else:
                                                                for kup, vup in dictV.items():
                                                                    for kv,vv in self.graphListVV.items():
                                                                        if kv == vup[0]:
                                                                            if len(self.graphListVV[kv])>=2:
                                                                                tList = [[self.graphListVV[kv][0],self.graphListVV[kv][1]]]
                                                                                if len(self.graphListVV[kv]) >2:
                                                                                    nList = self.graphListVV[kv][2:len(self.graphListVV[kv])]
                                                                                    for j in nList:
                                                                                        tList.append(j)
                                                                                for a in range(len(tList)):
                                                                                    for b in range(len(tList[a])):
                                                                                        if kup == tList[a][b]:
                                                                                            ypStatus = True
                                                                    if ypStatus == False:
                                                                        if kup not in self.graphListVV.keys():
                                                                            self.graphListVV[kup] = vup
        pass


    def findNext(self,value, vertexObj,streetName, streetObj):
        if list(value.point) in streetObj.streetPath:
            iniPos = streetObj.streetPath.index(list(value.point))
            if (iniPos +1 > len(streetObj.streetPath)-1):
                return None
            else:
                nextPos = streetObj.streetPath[iniPos+1]
                for k, v in vertexObj.adjacencyList.items():
                    if (v.endPoint == True)&(v.point== tuple(nextPos)):
                        return vertexObj.adjacencyList[k]
                else:
                    return None


    def findPrevious(self,value, vertexObj, streetName, streetObj):
        if list(value.point) in streetObj.streetPath:
            iniPos = streetObj.streetPath.index(list(value.point))
            if (iniPos-1 <0) or (iniPos -1 > len(streetObj.streetPath)-1):
                return None
            else:
                nextPos = streetObj.streetPath[iniPos-1]
                for k, v in vertexObj.adjacencyList.items():
                    if (v.endPoint == True)&(v.point== tuple(nextPos)):
                        return vertexObj.adjacencyList[k]
                else:
                    return None

      
    def findLength(self,streetA, streetB):
        length = ( (streetB[0]-streetA[0])**2 + (streetB[1]-streetA[1])**2 ) ** 0.5
        return length


    def findcollinear(self,streetA, streetB, streetC): 
        area = streetA[0] * (streetB[1] - streetC[1]) + streetB[0] * (streetC[1] - streetA[1]) + streetC[0] * (streetA[1] - streetB[1]) 
        area2 = abs(round(area,1))

        if ((area == 0) or (area2 == 0.0)): 
            return True
        else: 
            return False


    def checkTraversability(self,value, pointX, value2, vertexObj, streetObj):
        dAV = self.findLength(list(value.point), list(value2.point))
        dBV = self.findLength(list(pointX.point), list(value2.point))
        if self.findcollinear(list(value.point),list(value2.point),list(pointX.point)):
            dVal, state = self.checkSmallerPoint(value,value2,vertexObj,streetObj)
            if state == True:
                return dVal
            else:
                return {value.name : [value2.name,dAV]}
        else:
            return None

    
    def checkSmallerPointVertex(self,value, value2, vertexObj, streetObj):
        dAV = self.findLength(list(value.point), list(value2.point))
        d = {}
        data = []
        status = False
        small = dAV
        vPos = value2.name
        for k,v in vertexObj.adjacencyList.items():
            if (v.point != vertexObj.adjacencyList[value.name].point) & (v.point != vertexObj.adjacencyList[value2.name].point):
                if (streetObj.streetName in v.streetNames):
                    if (v.doesIntersect == True):
                        val = self.betweenPoints(value.point,v.point,value2.point)
                        if val == True:
                            distTwo =  self.findLength(value.point,v.point)
                            dTest = [v.name,distTwo]
                            data.append(dTest)
        sizeData = len(data)
        if sizeData != 0:
            for a in range(len(data)):
                if data[a][1] < dAV:
                    dAV = data[a][1]
                    vPos = data[a][0]
                    status = True
                    d = {value.name : [vPos,dAV]}
        else:
            d = {}
        return d, status


    def checkSmallerPoint(self,value, value2, vertexObj, streetObj):
        dAV = self.findLength(list(value.point), list(value2.point))
        d = {}
        data = []
        status = False
        small = dAV
        vPos = value2.name
        for k,v in vertexObj.adjacencyList.items():
            if (v.point != vertexObj.adjacencyList[value.name].point) & (v.point != vertexObj.adjacencyList[value2.name].point):
                if (streetObj.streetName in v.streetNames):
                    val = self.findcollinear(value.point,v.point,value2.point)
                    if val == True:
                        distTwo =  self.findLength(value.point,v.point)
                        dTest = [v.name,distTwo]
                        data.append(dTest)
        sizeData = len(data)
        if sizeData != 0:
            for a in range(len(data)):
                if data[a][1] < dAV:
                    dAV = data[a][1]
                    vPos = data[a][0]
                    status = True
                    d = {value.name : [vPos,dAV]}
        else:
            d = {}
        return d, status


    def checkInterPoint(self,kvp,vertexObj,p,distance):
        val = False
        test = 0
        for k,v in vertexObj.adjacencyList.items():
            if (v.point != vertexObj.adjacencyList[kvp].point) & (v.point != vertexObj.adjacencyList[p].point):
                if v.streetNames in vertexObj.adjacencyList[kvp].streetNames:
                    val = self.findcollinear(vertexObj.adjacencyList[kvp].point,v.point,vertexObj.adjacencyList[p].point)
                    if val == True:
                        test +=1
                        distTwo =  self.findLength(vertexObj.adjacencyList[kvp].point,v.point)
                        if distTwo <= distance:
                            return {kvp : [v.name, distTwo]}, True, test
        else:
            return None, False, test

    
    def checkConditionEdge(self,value,value2,vertexObj,streetObj):
        pointX = self.findNext(value, vertexObj,value.streetNames[0],streetObj)
        pointY = self.findPrevious(value, vertexObj,value.streetNames[0],streetObj)
        subLista=[]
        subListb=[]
        xpStatus = False
        ypStatus = False
        if pointX != None:
            dictVal = self.checkTraversability(value,pointX,value2, vertexObj, streetObj)
            if dictVal != None:
                if len(self.graphList.items()) == 0:
                    self.graphList.update(dictVal)
                else:
                    for keyi , valuei in dictVal.items():
                        for keyj, valuej in self.graphList.items():
                            if keyi == keyj:
                                if len(self.graphList[keyj])>=2:
                                    aKey = valuej[0]
                                    avalue = valuej[1]
                                    subLista =[[ valuej[0],valuej[1]]]
                                    if len(self.graphList[keyj]) >2:
                                        nextList = valuej[2:len(self.graphList[keyj])]
                                        for j in nextList:
                                            subLista.append(j)
                                    for a in range(len(subLista)):
                                        if dictVal[keyi] not in subLista:
                                            d, state , colTest = self.checkInterPoint(keyi,vertexObj,valuei[0],subLista[a][1])
                                            if state == True:
                                                if len(self.graphList[keyj])>2:
                                                    self.graphList[keyj].append(d[keyi])
                                                else:
                                                    self.graphList[keyj] = d[keyi]
                                            elif colTest == 0:
                                                self.graphList[keyj].append(valuei)
                    else:
                        for kup, vup in dictVal.items():
                            for kv,vv in self.graphList.items():
                                if kv == vup[0]:
                                    if len(self.graphList[kv])>=2:
                                        tList = [[self.graphList[kv][0],self.graphList[kv][1]]]
                                        if len(self.graphList[kv]) >2:
                                            nList = self.graphList[kv][2:len(self.graphList[kv])]
                                            for j in nList:
                                                tList.append(j)
                                        for a in range(len(tList)):
                                            for b in range(len(tList[a])):
                                                if kup == tList[a][b]:
                                                    xpStatus = True
                            if xpStatus == False:
                                if kup not in self.graphList.keys():
                                    self.graphList[kup] = vup
        if pointY != None:
            dictVal = self.checkTraversability(value,pointY,value2, vertexObj, streetObj)
            if dictVal != None:
                if len(self.graphList.items()) == 0:
                    self.graphList.update(dictVal)
                else:
                    for keyi , valuei in dictVal.items():
                        for keyj, valuej in self.graphList.items():
                            if keyi == keyj:
                                if len(self.graphList[keyj])>=2:
                                    aKey = valuej[0]
                                    avalue = valuej[1]
                                    subListb =[[ valuej[0],valuej[1]]]
                                    if len(self.graphList[keyj])>2:
                                        nextList = valuej[2:len(self.graphList[keyj])]
                                        for j in nextList:
                                            subListb.append(j)
                                    for a in range(len(subListb)):
                                        if dictVal[keyi] not in subListb:
                                            d, state , collTest = self.checkInterPoint(keyi,vertexObj,valuei[0],subListb[a][1])
                                            if state == True:
                                                if len(self.graphList[keyj])>2:
                                                    self.graphList[keyj].append(d[keyi])
                                                else:
                                                    self.graphList[keyj] = d[keyi]
                                            elif collTest == 0:
                                                self.graphList[keyj].append(valuei)
                        else:
                            for kup, vup in dictVal.items():
                                for kv,vv in self.graphList.items():
                                    if kv == vup[0]:
                                        if len(self.graphList[kv])>=2:
                                            tList = [[self.graphList[kv][0],self.graphList[kv][1]]]
                                            if len(self.graphList[kv]) >2:
                                                nList = self.graphList[kv][2:len(self.graphList[kv])]
                                                for j in nList:
                                                    tList.append(j)
                                            for a in range(len(tList)):
                                                for b in range(len(tList[a])):
                                                    if kup == tList[a][b]:
                                                        ypStatus = True
                                if ypStatus == False:
                                    if kup not in self.graphList.keys():
                                        self.graphList[kup] = vup

        pass


    def findStreetWay(self,value,street):
        for aStreet in street.streetWays:
            status = self.betweenStreet(aStreet,list(value))
            if status == True:
                return aStreet, True           
        else:
            return None, False


    def betweenStreet(self,streetA,streetB):
        a = self.findLength(streetA[0],streetB)
        b = self.findLength(streetA[1],streetB)
        c = self.findLength(streetA[0],streetA[1])
        testResult = round(a+b,2)
        testOut = round(c,2)
        if testResult == testOut:
            return True
        else:
            return False

    
    def betweenPoints(self,pointA,pointB,pointC):
        a = self.findLength(pointA,pointB)
        b = self.findLength(pointB,pointC)
        c = self.findLength(pointA,pointC)
        testResult = round(a+b,2)
        testOut = round(c,2)
        if testResult == testOut:
            return True
        else:
            return False





