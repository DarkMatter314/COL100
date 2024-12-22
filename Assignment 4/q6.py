import math
x = float(input())
n = int(input())

for i in range (1,n+1):
    term = (math.pow(-1,i))/(math.pow(x,2*i))
    print('%.2f'%term)