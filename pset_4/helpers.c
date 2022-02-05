#include "helpers.h"
#include "stdlib.h"
#include "math.h"



// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){
            BYTE average = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtRed = average;
        }
    }

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

// Blur image (box blur)
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
    int blue_sum, green_sum, red_sum, pixels_counter, hi_from, hi_to, wi_from, wi_to;
    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){
            blue_sum = 0, green_sum = 0, red_sum = 0, pixels_counter = 0;

            hi_from = h == 0 ? 0 : -1;
            hi_to = h == height - 1 ? 0 : 1;
            wi_from = w == 0 ? 0 : -1;
            wi_to = w == width - 1 ? 0 : 1;

            for (int hi = hi_from; hi <= hi_to; hi++){
                for (int wi = wi_from; wi <= wi_to; wi++){
                    blue_sum += image_copy[h + hi][w + wi].rgbtBlue;
                    green_sum += image_copy[h + hi][w + wi].rgbtGreen;
                    red_sum += image_copy[h + hi][w + wi].rgbtRed;
                    pixels_counter++;
                }
            }
            image[h][w].rgbtBlue = round(blue_sum / (float)pixels_counter);
            image[h][w].rgbtGreen = round(green_sum / (float)pixels_counter);
            image[h][w].rgbtRed = round(red_sum / (float)pixels_counter);
        }
    }

    // free image_copy
    free(image_copy);

    return;
}


int min(int num1, int num2){
    return (num1 > num2 ) ? num2 : num1;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    
    // create copy of image
    RGBTRIPLE(*image_copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){
            image_copy[h][w] = image[h][w];
        }
    }

    int GX_KERNEL[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int GY_KERNEL[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };


    // change image by refering to copy image
    int blue_sum_gx, blue_sum_gy, green_sum_gx, green_sum_gy, red_sum_gx, red_sum_gy;
    int hi_from, hi_to, wi_from, wi_to;

    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){
            blue_sum_gx =0, blue_sum_gy = 0, green_sum_gx = 0, green_sum_gy = 0, red_sum_gx = 0, red_sum_gy = 0;

            hi_from = h == 0 ? 0 : -1;
            hi_to = h == height - 1 ? 0 : 1;
            wi_from = w == 0 ? 0 : -1;
            wi_to = w == width - 1 ? 0 : 1;

            for (int hi = hi_from, kernel_h = hi_from + 1; hi <= hi_to; hi++, kernel_h++){
                for (int wi = wi_from, kernel_w = wi_from + 1; wi <= wi_to; wi++, kernel_w++){
                    blue_sum_gx += image_copy[h + hi][w + wi].rgbtBlue * GX_KERNEL[kernel_h][kernel_w];
                    green_sum_gx += image_copy[h + hi][w + wi].rgbtGreen * GX_KERNEL[kernel_h][kernel_w];
                    red_sum_gx += image_copy[h + hi][w + wi].rgbtRed * GX_KERNEL[kernel_h][kernel_w];
                    blue_sum_gy += image_copy[h + hi][w + wi].rgbtBlue * GY_KERNEL[kernel_h][kernel_w];
                    green_sum_gy += image_copy[h + hi][w + wi].rgbtGreen * GY_KERNEL[kernel_h][kernel_w];
                    red_sum_gy += image_copy[h + hi][w + wi].rgbtRed * GY_KERNEL[kernel_h][kernel_w];
                }
            }
            image[h][w].rgbtBlue = min(0xFF, round(sqrt(blue_sum_gx*blue_sum_gx + blue_sum_gy*blue_sum_gy)));
            image[h][w].rgbtGreen = min(0xFF, round(sqrt(green_sum_gx*green_sum_gx + green_sum_gy*green_sum_gy)));
            image[h][w].rgbtRed = min(0xFF, round(sqrt(red_sum_gx*red_sum_gx + red_sum_gy*red_sum_gy)));
        }
    }

    // free image_copy
    free(image_copy);

    return;
}
