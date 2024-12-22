def sortings(inpt : str) -> str: # it takes string as input and return string
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

    # return your's string result
    # your's code end here 
    

if __name__=="__main__": # calling main (run automtically)
    inpt = input()       # taking input from user (string type)
    out = sortings(inpt) # calling function sortings in which you have to write code
    print (out)          # printing the output of your's function