#include <stdio.h>
#include <cs50.h>
#include <string.h>


int main(void) {
    string name = get_string("String: ");
    int i = 0;
    // NUL character
    while (name[i] != '\0'){
        i++;
    }
    printf("%i\n", i);
    int l = strlen(name); // better way
}