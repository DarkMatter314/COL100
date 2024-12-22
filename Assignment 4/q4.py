n = int(input())
ch = 65

for i in range (0,n):
    print(" "*i,end="",sep="")
    for j in range (i,n):
        print(chr(ch),end="")
    ch+=1
    print()