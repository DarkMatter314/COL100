from typing import List

def sort(inpt : str) -> str: # it takes string as input and return string
    A = list(inpt)
    B = [0 for m in range (0,10)]
    C = []
    for i in range(0,len(A)):
        for j in range(0,10):
            if(A[i] == chr(j+48)): B[j] += 1
    for j in range(0,10):
        if(B[j] % 2 != 0):
            for i in range(0,B[j]): C.append(chr(j+48))
    for i in range(0, len(A)):
        check = True
        for j in range(0,10):
            if(A[i] == chr(j+48) and (B[j]%2) != 0): check = False
        if(check): C.append(A[i])
    z="".join(C)
    inpt=z
    return inpt

def sortings(lst : List[str]) -> List[str]: # it takes list of strings as input and return list of strings
    # write your code in this function only
    # your's code start here 
    sortlst = []
    for i in range(0, len(lst)): sortlst.append(sort(lst[i]))
    
    nonelst = []
    numlst = ["" for m in range(len(sortlst))]
    for i in range(0,len(sortlst)):
        if(sortlst[i] == ""): nonelst.append(sortlst[i])
        for j in range(0,len(sortlst[i])):
            if(ord(sortlst[i][j]) > 58 or ord(sortlst[i][j]) < 47): 
                if(numlst[i] == ""): nonelst.append(sortlst[i])
                break
            else:
                for k in range(0,10): 
                    if(sortlst[i][j] == chr(k+48)): numlst[i] += str(chr(k+48))
    
    sortednumlstdup = sorted(numlst)
    sortednumlst = []
    for i in range(0,len(sortednumlstdup)):
        if(sortednumlstdup[i] == ""): continue
        if(sortednumlstdup[i] not in sortednumlst): sortednumlst.append(sortednumlstdup[i])

    indexlst = []
    for i in range(0,len(sortednumlst)):
        for j in range(0,len(numlst)):
            if(numlst[j] == sortednumlst[i]): indexlst.append(j)

    while("" in indexlst):
        indexlst.remove("")
    
    for i in range(0,len(indexlst)):
        lst[i] = (sortlst[indexlst[i]])
    for i in range(len(indexlst), len(lst)): 
        lst[i] = nonelst[i-len(indexlst)]

    return lst 
    
    # return your's result (list of string) 
    # your's code end here 
    

if __name__=="__main__": # calling main (run automtically)
    lst = []             # list that stores the input strings
    num = int(input())   # taking input from user of number of strings of list
    for i in range(num): # take input of all strings of list
        inpt = input()
        lst.append(inpt) # append each string into the list
    lst = sortings(lst)  # calling function in which you have to write the code
    print (lst)          # printing the output (list of strings) of your's function