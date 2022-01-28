#include <cs50.h>
#include <math.h>
#include <stdio.h>

// const long int MIN_VALID_VISA = pow(10, 13);
// const long int MAX_VALID_VISA = pow(10, 16);
// const long int MAX_VALID_MASTERCARD = pow(10, 16);
// const long int MAX_VALID_MASTERCARD = pow(10, 16);
// const long int MAX_VALID_AEXPRESS = 34 * pow(10, 15);
// const long int MAX_VALID_AEXPRESS = 37 * pow(10, 15);

bool valid_mastercard(long int number){
    int remainder = number / pow(10, 14);
    if (remainder >= 51 && remainder <= 55){
        return true;
    }
    return false;
}


int main(void)
{
    long int number = get_long("Number: ");
    if (valid_mastercard(number)){
        printf("MASTERCARD\n");
    }
    else{
        printf("INVALID\n");
    }

}