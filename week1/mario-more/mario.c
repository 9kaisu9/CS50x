#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (!(height > 0 && height < 9));

    for (int i = 1; i <= height; i++)
    {
        int spaces = height - i;
        for (int a = 1; a <= spaces; a++)
        {
            printf(" ");
        }
        for (int a = 1; a <= i; a++)
        {
            printf("#");
        }
        printf("  ");
        for (int a = 1; a <= i; a++)
        {
            printf("#");
        }
        printf("\n");
    }

}