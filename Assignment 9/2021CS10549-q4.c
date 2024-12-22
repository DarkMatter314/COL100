#include <stdio.h> // mandatory include

int birt(int XX, int YY, int ZZZZ, int AA, int BB, int CCCC){   // function you have to implement
    int c = 6; //counter for the day
    int days = 0; //number of days of birthday on Monday
    if((XX == 29) && (YY == 02)){
        c = 0;
        for(int i = ZZZZ+1; i < CCCC; i++){
            c = (c+1)%7;
            if(i%4 != 0){
                if(c==1) days++;
            }
            else{
                c = (c+1)%7;
                if(c == 2) days++;
            }
        }
        if(((CCCC%4) == 0) && (BB>2) && (c==1)) days++;
        if((((CCCC%4) != 0) && ((BB>3) || ((BB=3) && (AA>1)))) && c==0) days++;
    }
    else{
        for(int i = ZZZZ+1; i < CCCC; i++){
            c = (c+1)%7;
            if((i%4 == 0) && (YY>02)) c = (c+1)%7;
            if(c==1) days++;
            if((i%4 == 0) && (YY<=02)) c = (c+1)%7;
        }
        if((BB>YY) || ((BB==YY)&&(AA>XX))){
            if((c+1)%7 == 1) days++;
        }
    }
    return days;
}

int main()                       // mandatory main function
{
    int XX, YY, ZZZZ, AA, BB, CCCC;             // variable 
    scanf("%d", &XX);           // input of Date of birth
    scanf("%d", &YY);            // input of Month of birth
    scanf("%d", &ZZZZ);           // input of Year of birth
    scanf("%d", &AA);           // input of Date of death
    scanf("%d", &BB);            // input of Month of death
    scanf("%d", &CCCC);            // input of Year of death
    //printf("%d-%d-%d and %d-%d-%d \n",XX, YY, ZZZZ, AA, BB, CCCC);
    int result = birt(XX, YY, ZZZZ, AA, BB, CCCC);  // calling function
    printf("%d",result);               // printing result
    return 0;                   // return statment
}