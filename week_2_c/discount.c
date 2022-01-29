#include <cs50.h>
#include <stdio.h>

float discount(float initial_price, int percent);

int main(void){
    printf("%.2f\n", discount(100, 30));
}



float discount(float initial_price, int percent){
    return initial_price * (100 - percent) / 100;
}