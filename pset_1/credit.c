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
    int first_two_digits = number / pow(10, 14);
    if (first_two_digits >= 51 && first_two_digits <= 55){
        return true;
    }
    return false;
}

bool valid_visa(long int number){
    int first_digit;
    if (number >= pow(10, 15)){
        first_digit = number / pow(10, 15);
    }
    else if (number >= pow(10, 12)){
        first_digit = number / pow(10, 12);
    }
    else {
        return false;
    }
    if (first_digit == 4){
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
    else if (valid_visa(number)){
        printf("VISA\n");
    }
    else{
        printf("INVALID\n");
    }
}