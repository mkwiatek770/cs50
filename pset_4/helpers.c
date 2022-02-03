#include "helpers.h"
#include "stdlib.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // create copy of image
    RGBTRIPLE(*image_copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){
            image_copy[h][w] = image[h][w];
        }
    }

    // change image by refering to copy image
    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){
            BYTE average = (image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3;
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtRed = average;
        }
    }

    // free image_copy
    free(image_copy);

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
