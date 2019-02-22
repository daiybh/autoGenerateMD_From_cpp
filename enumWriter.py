import dataUnit
class EnumWorker:
    bStartEnum=False    
    enumCount=0
    curEnumName=""
    aWriter=None
    def __init__(self,aWer,dicEnum):
        self.aWriter = aWer
        self.DicEnum = dicEnum

    def doWithEnum(self,line):        
        if 'enum 'in line:            
            self.bStartEnum = True            
            x = line.find("enum") +5
            x2 = line.find(":")
            self.curEnumName = line[x:x2].strip()
            self.DicEnum[self.curEnumName]= line
            return True

        if self.bStartEnum ==False: 
            return False
        if 'class CmdType' in self.curEnumName:
            if line.find('{')<0 and line.find('}') <0:
                dataUnit.cmdType.append(line.strip()[:-1])
        
        self.DicEnum[self.curEnumName] += line
        
        if '};' in line:            
            self.bStartEnum =False         
            self.enumCount =self.enumCount+1   
            if  self.aWriter  !=None:
                self.aWriter.write("# "+str(self.enumCount)+". Enum\r\n"+ self.DicEnum[self.curEnumName])
        return True
