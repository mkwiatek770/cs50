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
            image[h][w] = image_copy[h][width - w - 1];
        }
    }

    // free image_copy
    free(image_copy);

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // create copy of image
    RGBTRIPLE(*image_copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){
            image_copy[h][w] = image[h][w];
        }
    }

    // change image by refering to copy image
    for (int h = 1; h < height - 1; h++){
        for (int w = 1; w < width - 1; w++){
            BYTE blue_sum = 0;
            BYTE green_sum = 0;
            BYTE red_sum = 0;
            int pixels_counter = 0; 
            for (int i = -1; i <= 1; i++){
                for (int j = -1; j <= 1; j++){
                    blue_sum += image_copy[h - i][w - i].rgbtBlue;
                    green_sum += image_copy[h - i][w - i].rgbtGreen;
                    red_sum += image_copy[h - i][w - i].rgbtRed;
                    pixels_counter++;
                }
            }
            image[h][w].rgbtBlue = blue_sum / pixels_counter;
            image[h][w].rgbtGreen = blue_sum / pixels_counter;
            image[h][w].rgbtRed = blue_sum / pixels_counter;
        }
    }

    // free image_copy
    free(image_copy);

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
