#include <cs50.h>
#include <math.h>
#include <stdio.h>



bool checksum(long int number, int length){
    // Luhn’s algorithm
    int sum_products = 0;
    int sum_remaining = 0;
    int nth_digit;

    for (int i = length - 1; i >= 0; i--){
        nth_digit = number / pow(10, i);
        // check if even
        if (i % 2 == 1){
            if (nth_digit >= 5){
                sum_products += 1 + (nth_digit * 2 - 10);
            }
            else{
                sum_products += nth_digit * 2;
            }
        }
        else{
            sum_remaining += nth_digit;
        }
        number -= nth_digit * pow(10, i);
    }
    return (sum_remaining + sum_products) % 10 == 0;
}

bool valid_mastercard(long int number){
    int first_two_digits = number / pow(10, 14);
    return (first_two_digits >= 51 && first_two_digits <= 55);
}

bool valid_american_express(long int number){
    int first_two_digits = number / pow(10, 13);
    return (first_two_digits == 34 || first_two_digits == 37);
}


bool valid_visa(long int number){
    int first_digit;
    int length;
    if (number >= pow(10, 15)){
        length = 16;
        first_digit = number / pow(10, length - 1);
    }
    else if (number >= pow(10, 12)){
        length = 13;
        first_digit = number / pow(10, length - 1);
    }
    else {
        return false;
    }
    return first_digit == 4 && checksum(number, length);
}



int main(void)
{
    long int number = get_long("Number: ");
    if (valid_mastercard(number)){
        printf("MASTERCARD\n");
    }
    else if (valid_american_express(number)){
        printf("AMEX\n");
    }
    else if (valid_visa(number)){
        printf("VISA\n");
    }
    else{
        printf("INVALID\n");
    }
}
