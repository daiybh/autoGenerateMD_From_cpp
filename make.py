fpath=r'.\transportCmd.h'
import makedownWriter
from enumWriter import EnumWorker
from StructWriter import StructWorker
import dataUnit
class Maker:    
    def open(self,aWriter):
        with open(fpath,'r') as f:
            
            self.enumWorker = EnumWorker(aWriter,dataUnit.dEnum)
            self.structWorker = StructWorker(aWriter,dataUnit.dStruct)
            for line in f.readlines():
                self.doProcess(line)

    bstartProcess=False
    def doProcess(self,line):
        if self.bstartProcess==False:
            self.bstartProcess =  'namespace transportCmd' in line            
        
        if self.enumWorker.doWithEnum(line) ==False:
            self.structWorker.doWithStruct(line)


        


    
aWriter = makedownWriter.makeDownWriter()
aWriter.open()

aaa = Maker()
aaa.open(None)
cout=0


#aWriter.write(dataUnit.dEnum['class CmdType'])
dScmd=[]
def getSCmd():
    ret = dataUnit.dStruct['SCmd']
    
    bStart = False
    for line in ret.strip().split('\n'):
        
        if 'union' in line:
            bStart = True
            continue
        if bStart==False:
            continue
        if '}' in line:
            break
        ret = line.strip().split(' ')
        if len(ret) <2:
            continue        
        dScmd.append(ret[0])

dCmdType=[]
def getCmdType():
     ret = dataUnit.dEnum['class CmdType']

     bStart=False
     for line in ret.strip().split('\n'):
        if '{' in line:
             bStart = True
             continue
        if bStart==False:
            continue
        if '}' in line:
            break
        rett = line.strip().replace('\t','').split(',')
        if len(rett)<2:
            continue
        dCmdType.append(rett[0])

getCmdType()
#print(dCmdType)
 
getSCmd()  
#print(dScmd)  
i=0
for cmdType in dCmdType:
    print(cmdType,"--->",dScmd[i])
    i+=1    
def test(typ):
    aWriter.writeCmdType(typ)
    ret = dataUnit.getStruct(typ)

    for x in ret:
        aWriter.writeItem(x)

def w():
    for Xtype in dataUnit.cmdType:
        aWriter.writeCmdType(Xtype)

        ret = dataUnit.getStruct(Xtype) 
        aWriter.writeItem(str(ret))
#w()
#test('SCmd')   


