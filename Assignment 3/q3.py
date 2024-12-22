import math

a = float(input())
b = float(input())
c = float(input())
d = b*b-4*a*c
x1 = x2 = y1 = y2 = 0.0

if(d>=0):
    x1 = -b/(2*a) + math.sqrt(d)/(2*a)
    x2 = -b/(2*a) - math.sqrt(d)/(2*a)
else:
    x1 = x2 = -b/(2*a)
    y1 = math.sqrt(-d)/(2*a)
    y2 = -math.sqrt(-d)/(2*a)
print('%.2f'%x1," ",'%.2f'%y1)
print('%.2f'%x2," ",'%.2f'%y2)       