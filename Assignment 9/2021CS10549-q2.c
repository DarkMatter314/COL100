#include <stdio.h> // mandatory include

float time_angle(int XX, int YY){   // function you have to implement
    float hourangle, minuteangle;
    if(XX >= 12) XX -= 12;
    minuteangle = YY*6;
    hourangle = XX*30 + (float)YY/2;
    float angle = minuteangle - hourangle;
    if(angle<0) angle = -angle;
    if(angle>180) angle = 360 - angle;
    return angle;                  // return statment
}

int main()                       // mandatory main function
{
    int XX, YY;                 // variable denoting hours and minutes
    scanf("%d", &XX);           // hour input
    scanf("%d", &YY);           // minute input
    // printf("%d:%d",XX,YY);
    int result = time_angle(XX, YY);  // calling function
    printf("%d",result);               // printing result
    return 0;                   // return statment
}