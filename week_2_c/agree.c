#include <stdio.h>
#include <cs50.h>

int main(void){
    
    char c = get_char("dou you agree? ");

    if (c == 'y' || c == 'Y'){
        printf("agreed\n");
    }
    else if (c == 'n' || c == 'N'){
        printf("not agreed\n");
    }

}