def CheckMatrix(A: list) -> bool:
    check = True
    if(len(A) == 0): check = False
    elif(len(A[0]) == 0): check = False
    else:
        for i in range(0, len(A)):
            if(len(A[i]) != len(A[0])):
                check = False
                break
            elif(check):
                for j in range(0, len(A[i])):
                    if(isinstance(A[i][j], float) == False): 
                        check = False
                        break
    return check

def Transpose(A: list) -> list:
    if(CheckMatrix(A)):
        B = [[0 for m in range(len(A[0]))] for n in range(len(A))]
        for i in range(0,len(A[0])):
            for j in range(0,len(A[i])):
                B[j][i] = A[i][j]
        return(B)

def Addition(A: list, B: list) -> list:
    if(CheckMatrix(A) and CheckMatrix(B)):
        if((len(A) == len(B)) and (len(A[0]) == len(B[0]))):
            C = [[0 for m in range(len(A[0]))] for n in range(len(A))]
            for i in range(0, len(A)):
                for j in range(0,len(A[i])):
                    C[i][j] = A[i][j] + B[i][j]
            return C

def Multiplication(A: list, B: list) -> list:
    if(CheckMatrix(A) and CheckMatrix(B)):
        if(len(A[0]) == len(B)):
            C = [[0 for m in range(len(A))] for n in range(len(B[0]))]
            for i in range(0, len(A)):
                for j in range(0, len(B[0])):
                    for m in range(0, len(B)):
                        C[i][j] += A[i][m]*B[m][j]
            return C

def Symmetric(A: list) -> bool:
    check = True
    if(CheckMatrix(A) == False): check = False
    else:
        if(len(A) != len(A[0])): check = False
        else:
            for i in range(0,len(A)):
                for j in range(i,len(A)):
                    if(A[i][j] != A[j][i]): check = False
    return check 