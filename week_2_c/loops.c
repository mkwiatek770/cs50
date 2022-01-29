#include <stdio.h>

// prototypes
void meow(void);
void bark(void);
void fsoc(void);


int main(void){
    
    int i = 0;
    while (i++ < 3)
    {
        meow();
    }
    
    for(int i = 0; i < 3; ++i){
        bark();
    }

    do{
        fsoc();
    } while(1);

}

void meow(void){
    printf("meow\n");
}

void bark(void){
    printf("woof\n");
}

void fsoc(void){
    printf("fsociety\n");
}