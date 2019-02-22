import re 
dEnum={    
     'Name': 'Content' ,
}

dStruct={
     'Name': 'Content' ,    
}
#print(dStruct)


cmdType=[]

def getEnum(Key,depth=0):    
    ret =[]
    Key = Key.replace('*','')   
    for s in dEnum:
        m  =re.search(Key,s,re.IGNORECASE) 
        if m:          
            xret = formatLine(dEnum[s],depth)
            if len(xret)>0:
                ret.append(xret)
            ret.append(dEnum[s])
    return ret


def getStruct(Key,depth=0):    
    depth+=1    
    ret =[]
    Key = Key.replace('*','')    
    for s in dStruct:
        if depth>1:
            m = (s == Key)
        else:
            m =re.search(Key,s,re.IGNORECASE) 
        if m:            
            xret = formatLine(dStruct[s],depth)
            if len(xret)>0:
                ret.append(xret)
            ret.append(dStruct[s])
    return ret

def formatLine(line,depth=0):
    
    depth+=1
    if depth >3:
        print(depth,">>",line)
        return []

    ret = line.replace('\t','').split('\n')
    bStart=0
    total=[]
    for xItem in ret:
        if '{' in xItem:
            bStart+=1
            continue
        elif '}' in xItem:
            bStart-=1
            if bStart<0:
                break
            else:
                continue

        if bStart:            
            xRet = xItem.strip().split(' ')
            if len(xRet) <2:
                continue
            #print(xRet)
            xStruct=getStruct(xRet[0],depth)
            if len(xStruct)>0:
                total.append(xStruct)
            else:
                xEnum=getEnum(xRet[0])
                if len(xEnum)>0:
                    total.append(xEnum)
        

    #print(ret)

    return total    

if __name__=="__main__":
    retx=[]
    print(isinstance(retx,list))
    
    testString='\tstruct GetThumbnailParam\n\t{\n\t\tThumbnailType type;\n\t\tuint64_t field;\n\t\tuint32_t tagSize;\n\t\tchar tag[MAX_ID_LEN];\n\t};\n'
    dStruct['GetThumbnailParam'] = testString
    testString ='\tstruct sGangExParam\n\t{\nGetThumbnailParam  xxxParam;\n\t\tstruct PlayerGangParam\n\t\t{\n\t\t\tCnlID  playerID;\n\t\t\tchar group;\n\t\t};\n\n\t\tint32_t count;\n\t\tPlayerGangParam* pParamArray;\n\t};\n'

    fs = open("./xxx.md",'w')
    xx = formatLine(testString)
    fs.write(xx)
    fs.close()
    
