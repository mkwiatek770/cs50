#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>


int main(void) {
    string name = get_string("String: ");
    printf("before: %s\n", name);
    printf("after:  ");
    // 1st version
    // for (int i = 0, l = strlen(name); i < l; i++){
    //     if (name[i] >= 'a' && name[i] <= 'z'){
    //         printf("%c", name[i] - 32);
    //     }
    //     else{
    //         printf("%c", name[i]);
    //     }
    // }
    // 2nd version
    // for (int i = 0, l = strlen(name); i < l; i++){
    //     if (islower(name[i])){
    //         printf("%c", toupper(name[i]));
    //     }
    //     else{
    //         printf("%c", name[i]);
    //     }
    // }
    // 3rd version
    for (int i = 0, l = strlen(name); i < l; i++){
        printf("%c", toupper(name[i]));
    }
    printf("\n");

}