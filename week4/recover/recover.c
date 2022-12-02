#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define BLOCK_SIZE 512

typedef uint8_t BYTE;
BYTE buffer[BLOCK_SIZE];


int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    int jpg_counter = 0;
    FILE *img = NULL;
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Could not open file");
        return 2;
    }
    char filename[8];
    bool img_open = false;

    while (fread(buffer, 1, BLOCK_SIZE, fp) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            img_open = true;
            if (jpg_counter == 0)
            {
                sprintf(filename, "%03i.jpg", jpg_counter);
                jpg_counter++;

                img = fopen(filename, "w");
                fwrite(buffer, 1, BLOCK_SIZE, img);
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", jpg_counter);
                jpg_counter++;

                img = fopen(filename, "w");
                fwrite(buffer, 1, BLOCK_SIZE, img);
            }
        }
        else
        {
            if (img_open)
            {
                fwrite(buffer, 1, BLOCK_SIZE, img);
            }
        }
    }
    fclose(img);
    fclose(fp);
    printf("%i images found\n", jpg_counter);
    return 0;
}