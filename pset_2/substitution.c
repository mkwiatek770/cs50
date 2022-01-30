#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>


const int ASCII_A = 65, ASCII_a = 97;
// prototypes
bool key_is_valid(string key);
string encode(string text, string key);


int main(int argc, string *argv){

    if (argc != 2){
        printf("One argument(key) required!\n");
        return 1;
    }
    string key = argv[1];
    if (!key_is_valid(key)){
        return 1;
    }
    string plaintext = get_string("plaintext:  ");
    string cipher = encode(plaintext, key);
    printf("ciphertext: %s\n", cipher);

    return 0;
}

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


string encode(string text, string key){
    // substitution cipher
    string encoded_text = text;
    char c;
    char new_c;
    int position;
    for (int i = 0, len = strlen(text); i < len; i++){
        c = text[i];
        if (isalpha(c)){
            if (isupper(c)){
                position = c - ASCII_A;
                new_c = toupper(key[position]);
            }
            else{
                position = c - ASCII_a;
                new_c = tolower(key[position]);
            }
            // perform substitution
            encoded_text[i] = new_c;
        }
    }
    return encoded_text;
}