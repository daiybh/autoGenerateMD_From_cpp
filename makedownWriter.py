class makeDownWriter:
    
    filePath=".\\result.md"
    
    def open(self):
        self.fwriter = open(self.filePath,"w")
        self.write("# Title\r\n")

    def write(self,strContent):
        self.fwriter.write(strContent)
        self.fwriter.flush()
    cmdTypeCount=1
    def writeCmdType(self,typeName):
        self.write("# "+str(self.cmdTypeCount)+". "+typeName+"\r\n")  
        self.cmdTypeCount=self.cmdTypeCount +1
    
    def writeItem(self,strContent):
        if isinstance(strContent,list):
            for x in strContent:
                self.writeItem(x)
        else:
            self.write(strContent+"\r\n")  

          #  Exception has occurred: TypeError
#can only concatenate list (not "str") to list
    


    
        



if __name__ == "__main__":
    x = makeDownWriter()
    x.open()
    x.write("## lllllllll")
    x.write("## lllllllll")
    

