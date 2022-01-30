#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>


bool key_is_valid(string key){
    // make sure key lenght is 26 chars long and contains only alphabetical letters
    if (strlen(key) != 26){
        printf("Key must contain 26 aphabetic characters!\n");
        return false;
    }
    for (int i = 0; i < 26; i++){
        if (!isalpha(key[i])){
            printf("Chraracter on position %i is not alphabetical!\n", i + 1);
            return false;
        }
    }
    return true;
}

int main(int argc, string *argv){

    if (argc != 2){
        printf("One argument(key) required!\n");
        return 1;
    }
    string key = argv[1];
    if (!key_is_valid(key)){
        return 1;
    }
    // convert string to lowercase
    // get plaintext
    string plaintext = get_string("plaintext:  ");
    // encode plaintext using key
    // print ciphertext
    printf("ciphertext: %s\n", plaintext);
    return 0;
}