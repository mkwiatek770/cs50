#include <cs50.h>
#include <math.h>
#include <stdio.h>


bool checksum(long int number, int length){
    // Luhn’s algorithm
    int sum_multipl_by_2 = 0;
    int sum_products_digits = 0;
    int sum_not_multipl_by_2 = 0;
    int nth_digit;

    for (int i = length - 1; i >= 0; i--){
        nth_digit = number / pow(10, i);
        // ops
        
        number -= nth_digit * pow(10, i);
        printf("%i, %li, %i\n", nth_digit, number, i);
    }

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
    if (number >= pow(10, 15) && checksum(number, 16)){
        first_digit = number / pow(10, 15);
    }
    else if (number >= pow(10, 12)){
        first_digit = number / pow(10, 12);
    }
    else {
        return false;
    }
    return (first_digit == 4);
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
