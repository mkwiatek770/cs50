#include <stdio.h>
#include <cs50.h>

int main(void) {
    int u = 1;
    printf("hi");
    long int x = get_long("x: ");
    long int y = get_long("y: ");
    printf("%li", x + y);
}