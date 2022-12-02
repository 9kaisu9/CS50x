#include "helpers.h"
#include <math.h>


// Swap two pixels
void swap_pixels(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2)
{
    RGBTRIPLE tmp = *pixel1;
    *pixel1 = *pixel2;
    *pixel2 = tmp;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = (int)(((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)) / 3 + 0.5);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);

            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int half = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < half; j++)
        {
            swap_pixels(&image[i][j], &image[i][width - 1 - j]);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE oldimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            oldimage[i][j] = image[i][j];
        }
    }

    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            image[i][j].rgbtRed = round((oldimage[i-1][j-1].rgbtRed + oldimage[i-1][j].rgbtRed + oldimage[i-1][j+1].rgbtRed + oldimage[i][j-1].rgbtRed + oldimage[i][j].rgbtRed + oldimage[i][j+1].rgbtRed + oldimage[i+1][j-1].rgbtRed + oldimage[i+1][j].rgbtRed + oldimage[i+1][j+1].rgbtRed) / 9.0);
            image[i][j].rgbtGreen = round((oldimage[i-1][j-1].rgbtGreen + oldimage[i-1][j].rgbtGreen + oldimage[i-1][j+1].rgbtGreen + oldimage[i][j-1].rgbtGreen + oldimage[i][j].rgbtGreen + oldimage[i][j+1].rgbtGreen + oldimage[i+1][j-1].rgbtGreen + oldimage[i+1][j].rgbtGreen + oldimage[i+1][j+1].rgbtGreen) / 9.0);
            image[i][j].rgbtBlue = round((oldimage[i-1][j-1].rgbtBlue + oldimage[i-1][j].rgbtBlue + oldimage[i-1][j+1].rgbtBlue + oldimage[i][j-1].rgbtBlue + oldimage[i][j].rgbtBlue + oldimage[i][j+1].rgbtBlue + oldimage[i+1][j-1].rgbtBlue + oldimage[i+1][j].rgbtBlue + oldimage[i+1][j+1].rgbtBlue) / 9.0);
        }
    }
    for (int j = 1; j < width - 1; j++)
    {
        image[0][j].rgbtRed = round((oldimage[0][j-1].rgbtRed + oldimage[0][j].rgbtRed + oldimage[0][j+1].rgbtRed + oldimage[1][j-1].rgbtRed + oldimage[1][j].rgbtRed + oldimage[1][j+1].rgbtRed) / 6.0);
        image[0][j].rgbtGreen = round((oldimage[0][j-1].rgbtGreen + oldimage[0][j].rgbtGreen + oldimage[0][j+1].rgbtGreen + oldimage[1][j-1].rgbtGreen + oldimage[1][j].rgbtGreen + oldimage[1][j+1].rgbtGreen) / 6.0);
        image[0][j].rgbtBlue = round((oldimage[0][j-1].rgbtBlue + oldimage[0][j].rgbtBlue + oldimage[0][j+1].rgbtBlue + oldimage[1][j-1].rgbtBlue + oldimage[1][j].rgbtBlue + oldimage[1][j+1].rgbtBlue) / 6.0);
        image[height-1][j].rgbtRed = round((oldimage[height-1][j-1].rgbtRed + oldimage[height-1][j].rgbtRed + oldimage[height-1][j+1].rgbtRed + oldimage[height-2][j-1].rgbtRed + oldimage[height-2][j].rgbtRed + oldimage[height-2][j+1].rgbtRed) / 6.0);
        image[height-1][j].rgbtGreen = round((oldimage[height-1][j-1].rgbtGreen + oldimage[height-1][j].rgbtGreen + oldimage[height-1][j+1].rgbtGreen + oldimage[height-2][j-1].rgbtGreen + oldimage[height-2][j].rgbtGreen + oldimage[height-2][j+1].rgbtGreen) / 6.0);
        image[height-1][j].rgbtBlue = round((oldimage[height-1][j-1].rgbtBlue + oldimage[height-1][j].rgbtBlue + oldimage[height-1][j+1].rgbtBlue + oldimage[height-2][j-1].rgbtBlue + oldimage[height-2][j].rgbtBlue + oldimage[height-2][j+1].rgbtBlue) / 6.0);
    }
    for (int i = 1; i < height - 1; i++)
    {
        image[i][0].rgbtRed = round((oldimage[i-1][0].rgbtRed + oldimage[i][0].rgbtRed + oldimage[i+1][0].rgbtRed + oldimage[i-1][1].rgbtRed + oldimage[i][1].rgbtRed + oldimage[i+1][1].rgbtRed) / 6.0);
        image[i][0].rgbtGreen = round((oldimage[i-1][0].rgbtGreen + oldimage[i][0].rgbtGreen + oldimage[i+1][0].rgbtGreen + oldimage[i-1][1].rgbtGreen + oldimage[i][1].rgbtGreen + oldimage[i+1][1].rgbtGreen) / 6.0);
        image[i][0].rgbtBlue = round((oldimage[i-1][0].rgbtBlue + oldimage[i][0].rgbtBlue + oldimage[i+1][0].rgbtBlue + oldimage[i-1][1].rgbtBlue + oldimage[i][1].rgbtBlue + oldimage[i+1][1].rgbtBlue) / 6.0);
        image[i][width-1].rgbtRed = round((oldimage[i-1][width-1].rgbtRed + oldimage[i][width-1].rgbtRed + oldimage[i+1][width-1].rgbtRed + oldimage[i-1][width-2].rgbtRed + oldimage[i][width-2].rgbtRed + oldimage[i+1][width-2].rgbtRed) / 6.0);
        image[i][width-1].rgbtGreen = round((oldimage[i-1][width-1].rgbtGreen + oldimage[i][width-1].rgbtGreen + oldimage[i+1][width-1].rgbtGreen + oldimage[i-1][width-2].rgbtGreen + oldimage[i][width-2].rgbtGreen + oldimage[i+1][width-2].rgbtGreen) / 6.0);
        image[i][width-1].rgbtBlue = round((oldimage[i-1][width-1].rgbtBlue + oldimage[i][width-1].rgbtBlue + oldimage[i+1][width-1].rgbtBlue + oldimage[i-1][width-2].rgbtBlue + oldimage[i][width-2].rgbtBlue + oldimage[i+1][width-2].rgbtBlue) / 6.0);
    }
    image[0][0].rgbtRed = round((oldimage[0][0].rgbtRed + oldimage[1][0].rgbtRed + oldimage[0][1].rgbtRed + oldimage[1][1].rgbtRed) / 4.0);
    image[0][0].rgbtGreen = round((oldimage[0][0].rgbtGreen + oldimage[1][0].rgbtGreen + oldimage[0][1].rgbtGreen + oldimage[1][1].rgbtGreen) / 4.0);
    image[0][0].rgbtBlue = round((oldimage[0][0].rgbtBlue + oldimage[1][0].rgbtBlue + oldimage[0][1].rgbtBlue + oldimage[1][1].rgbtBlue) / 4.0);

    image[height-1][0].rgbtRed = round((oldimage[height-1][0].rgbtRed + oldimage[height-2][0].rgbtRed + oldimage[height-1][1].rgbtRed + oldimage[height-2][1].rgbtRed) / 4.0);
    image[height-1][0].rgbtGreen = round((oldimage[height-1][0].rgbtGreen + oldimage[height-2][0].rgbtGreen + oldimage[height-1][1].rgbtGreen + oldimage[height-2][1].rgbtGreen) / 4.0);
    image[height-1][0].rgbtBlue = round((oldimage[height-1][0].rgbtBlue + oldimage[height-2][0].rgbtBlue + oldimage[height-1][1].rgbtBlue + oldimage[height-2][1].rgbtBlue) / 4.0);

    image[0][width-1].rgbtRed = round((oldimage[0][width-1].rgbtRed + oldimage[1][width-1].rgbtRed + oldimage[0][width-2].rgbtRed + oldimage[1][width-2].rgbtRed) / 4.0);
    image[0][width-1].rgbtGreen = round((oldimage[0][width-1].rgbtGreen + oldimage[1][width-1].rgbtGreen + oldimage[0][width-2].rgbtGreen + oldimage[1][width-2].rgbtGreen) / 4.0);
    image[0][width-1].rgbtBlue = round((oldimage[0][width-1].rgbtBlue + oldimage[1][width-1].rgbtBlue + oldimage[0][width-2].rgbtBlue + oldimage[1][width-2].rgbtBlue) / 4.0);

    image[height-1][width-1].rgbtRed = round((oldimage[height-1][width-1].rgbtRed + oldimage[height-2][width-1].rgbtRed + oldimage[height-1][width-2].rgbtRed + oldimage[height-2][width-2].rgbtRed) / 4.0);
    image[height-1][width-1].rgbtGreen = round((oldimage[height-1][width-1].rgbtGreen + oldimage[height-2][width-1].rgbtGreen + oldimage[height-1][width-2].rgbtGreen + oldimage[height-2][width-2].rgbtGreen) / 4.0);
    image[height-1][width-1].rgbtBlue = round((oldimage[height-1][width-1].rgbtBlue + oldimage[height-2][width-1].rgbtBlue + oldimage[height-1][width-2].rgbtBlue + oldimage[height-2][width-2].rgbtBlue) / 4.0);

    return;
}