def pattern(a):
    if(a==1): return 111
    else: return(str(a) + str(pattern(a-1)) + str(a) + str(pattern(a-1)) + str(a))

n = int(input())
print(pattern(n))