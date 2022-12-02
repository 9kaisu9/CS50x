#include <cs50.h>
#include <stdio.h>
#include <math.h>

int digit_from_back(long number, int m);
int how_many_digits(long number);

int main(void)
{
    long number = get_long("Number :");
    int check = 0;
    int digits = how_many_digits(number);
    for (int m = 0; m < digits; m++)
    {
        if (m % 2 == 1)
        {
            int multiplied_by_2 = 2 * digit_from_back(number, m);
            int sub_digits = how_many_digits(multiplied_by_2);
            if (sub_digits > 1)
            {
                for (int n = 0; n < sub_digits; n++)
                {
                    check += digit_from_back(multiplied_by_2, n);
                }
            }
            else
            {
                check += multiplied_by_2;
            }
        }
        else
        {
            check += digit_from_back(number, m);
        }

    }
    if (check % 10 == 0)
    {
        switch (digits)
        {
            case 13:
                if (4 == digit_from_back(number, 12))
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            case 15:
                if (3 == digit_from_back(number, 14) && (4 == digit_from_back(number, 13) || 7 == digit_from_back(number, 13)))
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            case 16:
                if (4 == digit_from_back(number, 15))
                {
                    printf("VISA\n");
                }
                else if (5 == digit_from_back(number, 15) && 0 < digit_from_back(number, 14) && digit_from_back(number, 14) < 6)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            default:
                printf("INVALID\n");
                break;
        }
    }
    else
    {
        printf("INVALID\n");
    }

}


int digit_from_back(long number, int m)
{
    for (int i = 0; i < m; i++)
    {
        number = number / 10;
    }
    return number % 10;
}

int how_many_digits(long number)
{
    int digits = 1;
    while (true)
    {
        number = number / 10;
        if (number == 0)
        {
            break;
        }
        else
        {
            digits++;
        }
    }
    return digits;
}