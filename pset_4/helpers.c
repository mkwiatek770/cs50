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
    int blue_sum;
    int green_sum;
    int red_sum;
    int pixels_counter;
    int hi_up;
    int hi_down;
    int wi_right;
    int wi_left;
    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){
            blue_sum = 0;
            green_sum = 0;
            red_sum = 0;
            pixels_counter = 0;
            hi_up = h == height - 1 ? 0 : -1;
            hi_down = h == 0 ? 0 : 1;
            wi_right = w == width - 1 ? 0 : -1;
            wi_left = h == 0 ? 0 : 1;

            for (int hi = hi_up; hi <= hi_down; hi++){
                for (int wi = wi_right; wi <= wi_left; wi++){
                    blue_sum += image_copy[h - hi][w - hi].rgbtBlue;
                    green_sum += image_copy[h - hi][w - hi].rgbtGreen;
                    red_sum += image_copy[h - hi][w - hi].rgbtRed;
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
