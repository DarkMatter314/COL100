def numwords(s = [], *args):
    c = 0
    minimum = 0
    for k in range(0, n):
        if(len(s[k]) == 0): minimum = 0
        else:
            for i in range(1, (len(s[k]))):
                if((s[k][i] == " " and (s[k][i-1] != ' ' and s[k][i-1] != ',' and s[k][i-1] != '.')) 
                or (s[k][i] == "," and (s[k][i-1] != ' ' and s[k][i-1] != ',' and s[k][i-1] != '.')) 
                or (s[k][i] == "." and (s[k][i-1] != ' ' and s[k][i-1] != ',' and s[k][i-1] != '.'))):
                    c = c+1
            if(s[k][len(s[k])-1] != " " and s[k][len(s[k])-1] != "," and s[k][len(s[k])-1] != "."): c=c+1
        if(k==0): minimum=c
        minimum = min(minimum,c)
        c=0
    return minimum

n = int(input())
sen = [""] *n
for j in range(0,n):
    sen[j] = input()
print('%.2f'%numwords(sen))