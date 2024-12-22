def padovan(a):
    if(a==0 or a==1 or a==2): return 1
    else: return padovan(a-2)+padovan(a-3)

n = int(input())
print('%.2f'%padovan(n))