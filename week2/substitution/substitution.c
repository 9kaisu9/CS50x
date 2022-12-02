#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int valid_key(string text);


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (valid_key(argv[1]))
    {
        return 1;
    }
    string key = argv[1];
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string plaintext = get_string("plaintext: ");
    char ciphertext[strlen(plaintext)];
    strcpy(ciphertext, plaintext);
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if(isalpha(plaintext[i]))
        {
            int index = (int)(strchr(alphabet, tolower(plaintext[i])) - alphabet);
            if (islower(plaintext[i]))
            {
                ciphertext[i] = tolower(key[index]);
            }
            else
            {
                ciphertext[i] = toupper(key[index]);
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}


int valid_key(string text)
{
    int length = strlen(text);

    if (length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(text[i]))
        {
            printf("key not containing only alphabetical values\n");
            return 1;
        }
        for (int j = 0; j < i; j++)
        {

            if (tolower(text[i]) == tolower(text[j]))
            {
                printf("characters not unique\n");
                return 1;
            }
        }
    }
    return 0;
}

