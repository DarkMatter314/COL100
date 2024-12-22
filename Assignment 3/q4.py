check = input()

if(len(check) == 1): print("YES")
elif((len(check) == 2) or (len(check) == 3)):
    if(check[0] == check[len(check)-1]): print("YES")
    else: print("NO")
elif(len(check) == 4):
    if(check[0] == check[3]):
        if(check[1] == check[2]): print("YES")
        else: print("NO")
    else: print("NO")    