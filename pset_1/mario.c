#include <cs50.h>
#include <stdio.h>


int main(void){
    int h;
    do{
        h = get_int("Size: ");
    } while (h < 1 && h > 8);

    // rows
    for (int i=0; i<h; i++){
        for (int j=0; j<h; j++){
            printf("#");
        }
        printf(" ");
        for (int j=0; j<h; j++){
            printf("#");
        }
        printf("\n");
    }
}