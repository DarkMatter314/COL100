n = int(input())
c=1

for i in range (0,n):
    for j in range (0,i+1):
        print(c,end=" ")
        c+=1
    print()