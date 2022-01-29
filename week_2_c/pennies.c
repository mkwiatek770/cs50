#include <cs50.h>
#include <math.h>
#include <stdio.h>


int main(void){
    float dollars = get_float("Dollars: ");
    int pennies = round(dollars * 100);
    printf("Pennies: %i\n", pennies);
}
