#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    int blank_w;
    int hash_w;

    do
    {
        h = get_int("Size: ");
    } while (h < 1 && h > 8);

    for (int i = 1; i <= h; i++)
    {
        blank_w = h - i;
        hash_w = i;
        // 1st half
        for (int j = 0; j < blank_w; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < hash_w; j++)
        {
            printf("#");
        }
        // middle gap
        printf(" ");
        // 2nd half
        for (int j = 0; j < hash_w; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}