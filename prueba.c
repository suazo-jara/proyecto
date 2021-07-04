#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int main(){
    int cambio,b;
    srand(time(NULL));
    cambio=-7;
    b=((cambio)/abs(cambio))*(rand()%cambio+1);
    printf("%i",b);
}