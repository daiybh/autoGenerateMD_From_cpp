class StructWorker:
    bStart=False    
    Count=0
    curName=""
    aWriter=None
    def __init__(self,aWer,dicStruct):
        self.aWriter = aWer
        self.dicStruct = dicStruct
    startCount=0
    def doWithStruct(self,line):        
        if 'struct 'in line:
            if self.bStart:                
                self.dicStruct[self.curName]+= line
                return
            
            self.bStart = True            
            x = line.find("struct") +6
            x2 = line.find(":")
            self.curName = line[x:x2].strip()            
            self.dicStruct[self.curName]= line
            return True

        if self.bStart ==False: 
            return False
        
        self.dicStruct[self.curName] += line
        if '{' in line:            
            self.startCount=self.startCount+1
            
        if '}' in line and ';' in line:
            self.startCount=self.startCount-1
            if self.startCount>0:
                return True
            self.bStart =False         
            self.Count =self.Count+1 
            if  self.aWriter  !=None:
                self.aWriter.write("# "+str(self.Count)+". Struct "+ self.curName+  "\r\n"+ self.dicStruct[self.curName])
        return True
