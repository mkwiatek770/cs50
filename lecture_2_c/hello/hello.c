#include <stdio.h>

int main(void){

    char name[20];
    printf("What's your name? ");
    fgets(name, 20, stdin);
    printf("Hello, %s!", name);
    return 0;
}