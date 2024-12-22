line=[]

def Call(a):
    for i in range(0, len(a)):
        if("Check" in a[i]): Check()
        elif("GetLine" in a[i]): GetLine()
        elif("Issue" in a[i]): Issue()
        else:
            x,y = a[i].split()
            y = int(y)
            Join(y)

def Issue():
    if(len(line) == 0): print("Invalid")
    else: line.pop(0)

def Join(AadharID: int):
    line.append(AadharID)

def Check():
    if(len(line) == 0): print("Invalid")
    else: print(line[0])

def GetLine():
    if(len(line) == 0): print("Invalid")
    else:
        for i in range(0,len(line)): 
            print(line[i], end=" ")
        print()

n = int(input())
command = [""]*n
for i in range(0,n):
    command[i] = input()

Call(command)