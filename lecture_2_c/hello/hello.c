#include <stdio.h>
#include <string.h>


int main(void){

    char name[20];
    printf("What's your name? ");
    fgets(name, 20, stdin);
    // clear \n char from name
    name[strlen(name)-1] = '\0';
    printf("Hello, %s!\n", name);
    return 0;
}