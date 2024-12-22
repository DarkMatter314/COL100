#include <stdio.h> // mandatory include

float Combination(int n,int r){
    if(r == 1) return n;
    return ((n*Combination(n-1,r-1))/r);
}

int food(int x, int y, int m, int n){   // function you have to implement
    int total = Combination(x+y,x)*Combination(m+n-x-y,m-x);
    return total;                 // return statment
}

int main()                       // mandatory main function
{
    int x, y, m, n;             // variable denoting coordinate of restaurant and delivery location
    scanf("%d", &x);           // x coordinate of restaurant
    scanf("%d", &y);            // y coordinate of restaurant
    scanf("%d", &m);           // x coordinate of delivery location
    scanf("%d", &n);            // y coordinate of delivery location
    //printf("(%d,%d) and (%d,%d) \n",x,y,m,n);
    int result = food(x, y, m, n);  // calling function
    printf("%d",result);               // printing result
    return 0;                   // return statment
}
