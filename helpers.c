#include "helpers.h"
#include <math.h>
#include <stdio.h>

//./filter -g images/courtyard.bmp outfile.bmp (TO CONVERT IMAGES TO THE SPECIFIED FILTER)
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int hgt = height - 1;
    int wdth = width - 1;
    int grayscale = 0;

    //Loop through each row of the image (to get the last row were doing "height - 1" since were counting from 0)
    for (int i = 0; i <= hgt ; i++)
    {
        //Loop through each pixel in the current row (to get the last row were doing do "row - 1" since were counting from 0)
        for (int j = 0; j <= wdth; j++)
        {
            //Calculate the average red, green, and blue colors of each pixel
            grayscale = (round(((float)image[i][j].rgbtRed + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtBlue) / (float)3.0));

            //Set the red, green, and blue colors to the average of the pixel(Round off the pixel if it is in decimal value)
            image[i][j].rgbtRed = grayscale;
            image[i][j].rgbtGreen = grayscale;
            image[i][j].rgbtBlue = grayscale;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int hgt = height - 1;
    int wdth = width - 1;

    //Loop through each row of the image (to get the last row were doing "height - 1" since were counting from 0)
    for (int i = 0; i <= hgt ; i++)
    {
        //Loop through each pixel in the current row (to get the last row were doing do "row - 1" since were counting from 0)
        for (int j = 0; j <= wdth; j++)
        {
            //Forumla for calculating the sepia amount
            float sepiaRed = ((float)0.393 * (float)image[i][j].rgbtRed) + ((float)0.769 * (float)image[i][j].rgbtGreen) + ((float)0.189 * (float)image[i][j].rgbtBlue);
            float sepiaGreen = ((float)0.349 * (float)image[i][j].rgbtRed) + ((float)0.686 * (float)image[i][j].rgbtGreen) + ((float)0.168 * (float)image[i][j].rgbtBlue);
            float sepiaBlue = ((float)0.272 * (float)image[i][j].rgbtRed) + ((float)0.534 * (float)image[i][j].rgbtGreen) + ((float)0.131 * (float)image[i][j].rgbtBlue);

            //Make sure the values do not exceed 255 (Set it to 255 if it should exceed the maximum value)
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            //Calcute the sepia amount of each pixel using the formula
            image[i][j].rgbtRed = (round(sepiaRed));
            image[i][j].rgbtGreen = (round(sepiaGreen));
            image[i][j].rgbtBlue = (round(sepiaBlue));
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int hgt = height - 1;
    int wdth = width - 1;
    RGBTRIPLE temporary;//Creates a variable used to hold a temporary data

    //Loop through each row of the image (to get the last row were doing "height - 1" since were counting from 0)
    for (int i = 0; i <= hgt ; i++)
    {
        //Loop through each pixel in the current row (to get the last row were doing do "row - 1" since were counting from 0)
        for (int j = 0; j <= (wdth/2); j++)
        {
            temporary = image[i][j];//Holds the data in the current array in a temporary variable to swap later to the data that is to be swapped
            image[i][j] = image[i][wdth - j];//Swaps the current data with the data on the opposite side
            image[i][wdth - j] = temporary;//Swaps the current data with the data STORED on the temporary variable
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int hgt = height - 1;
    int wdth = width - 1;
    float avgRed, avgGreen, avgBlue;
    float add1, add2, add3, add4, add5, add6, add7, add8, add9;
    float totalavg;
    RGBTRIPLE copy[height][width];

    //hgt = THE BOTTOMMOST EDGE
    //wdth = THE RIGHTMOST EDGE
    //hgt - 1 = AVOIDS THE BOTTOMMOST EDGE
    //wdth - 1 = AVOIDS THE RIGHTMOST EDGE
    //Calculate the average of EACH COLOR VALUE of the FOUR pixels on each corner by computing the AVERAGE of the adjacent FOUR PIXELS AROUND IT


    //COPIES THE WHOLE IMAGE FIRST TO AVOID UNNECESSARY ALTERATIONS TO THE ORIGINAL
    for (int i = 0; i <= hgt; i++)
    {
        for (int j = 0; j <= wdth; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //TOPLEFT CORNER (BLURRING image[0][0]) (GET THE AVERAGE of image[0][0], image[0][1], image[1][0], image[1][1])
    avgRed = ((float)image[0][0].rgbtRed + (float)image[0][1].rgbtRed + (float)image[1][0].rgbtRed + (float)image[1][1].rgbtRed) / 4.0;
    avgGreen = ((float)image[0][0].rgbtGreen + (float)image[0][1].rgbtGreen + (float)image[1][0].rgbtGreen + (float)image[1][1].rgbtGreen) / 4.0;
    avgBlue = ((float)image[0][0].rgbtBlue + (float)image[0][1].rgbtBlue + (float)image[1][0].rgbtBlue + (float)image[1][1].rgbtBlue) / 4.0;

    image[0][0].rgbtRed = (round(avgRed));
    image[0][0].rgbtGreen = (round(avgGreen));
    image[0][0].rgbtBlue = (round(avgBlue));

    //TOPRIGHT CORNER (BLURRING image[0][wdth]) (average of image[0][wdth], image[0][wdth - 1], image[1][wdth], image[1][wdth - 1])
    avgRed = ((float)image[0][wdth].rgbtRed + (float)image[0][wdth - 1].rgbtRed + (float)image[1][wdth].rgbtRed + (float)image[1][wdth - 1].rgbtRed) / 4.0;
    avgGreen = ((float)image[0][wdth].rgbtGreen + (float)image[0][wdth - 1].rgbtGreen + (float)image[1][wdth].rgbtGreen + (float)image[1][wdth - 1].rgbtGreen) / 4.0;
    avgBlue = ((float)image[0][wdth].rgbtBlue + (float)image[0][wdth - 1].rgbtBlue + (float)image[1][wdth].rgbtBlue + (float)image[1][wdth - 1].rgbtBlue) / 4.0;

    image[0][wdth].rgbtRed = (round(avgRed));
    image[0][wdth].rgbtGreen = (round(avgGreen));
    image[0][wdth].rgbtBlue = (round(avgBlue));

    //BOTTOMLEFT CORNER (BLURRING image[hgt][0]) (average of image[hgt][0], image[hgt][1], image[hgt - 1][0], image[hgt - 1][1])
    avgRed = ((float)image[hgt][0].rgbtRed + (float)image[hgt][1].rgbtRed + (float) image[hgt - 1][0].rgbtRed + (float)image[hgt - 1][1].rgbtRed) / 4.0;
    avgGreen = ((float)image[hgt][0].rgbtGreen + (float)image[hgt][1].rgbtGreen + (float) image[hgt - 1][0].rgbtGreen + (float)image[hgt - 1][1].rgbtGreen) / 4.0;
    avgBlue = ((float)image[hgt][0].rgbtBlue + (float)image[hgt][1].rgbtBlue + (float) image[hgt - 1][0].rgbtBlue + (float)image[hgt - 1][1].rgbtBlue) / 4.0;

    image[hgt][0].rgbtRed = (round(avgRed));
    image[hgt][0].rgbtGreen = (round(avgGreen));
    image[hgt][0].rgbtBlue = (round(avgBlue));

    //BOTTOMRIGHT CORNER (BLURRING image[hgt][wdth]) (average of image[hgt][wdth], image[hgt][wdth - 1], image[hgt - 1][wdth], image[hgt - 1][wdth - 1])
    avgRed = ((float)image[hgt][wdth].rgbtRed + (float)image[hgt][wdth - 1].rgbtRed + (float)image[hgt - 1][wdth].rgbtRed + (float)image[hgt - 1][wdth - 1].rgbtRed) / 4.0;
    avgGreen = ((float)image[hgt][wdth].rgbtGreen + (float)image[hgt][wdth - 1].rgbtGreen + (float)image[hgt - 1][wdth].rgbtGreen + (float)image[hgt - 1][wdth - 1].rgbtGreen) / 4.0;
    avgBlue = ((float)image[hgt][wdth].rgbtBlue + (float)image[hgt][wdth - 1].rgbtBlue + (float)image[hgt - 1][wdth].rgbtBlue + (float)image[hgt - 1][wdth - 1].rgbtBlue) / 4.0;

    image[hgt][wdth].rgbtRed = (round(avgRed));
    image[hgt][wdth].rgbtGreen = (round(avgGreen));
    image[hgt][wdth].rgbtBlue = (round(avgBlue));

    //Calculate the average of COLOR VALUE of the EDGE pixels by computing the AVERAGE of the adjacent SIX PIXELS AROUND IT
    for (int i = 1; i <= (hgt - 1); i++)//Loops through the LEFTMOST EDGE
    {
        //RED RGBT
        add1 =  copy[i - 1][0].rgbtRed;
        add2 =  copy[i][0].rgbtRed;
        add3 =  copy[i + 1][0].rgbtRed;
        add4 =  copy[i - 1][1].rgbtRed;
        add5 =  copy[i][1].rgbtRed;
        add6 =  copy[i + 1][1].rgbtRed;
        avgRed = (add1 + add2 + add3 + add4 + add5 + add6) / 6.0;

        //GREEN RGBT
        add1 =  copy[i - 1][0].rgbtGreen;
        add2 =  copy[i][0].rgbtGreen;
        add3 =  copy[i + 1][0].rgbtGreen;
        add4 =  copy[i - 1][1].rgbtGreen;
        add5 =  copy[i][1].rgbtGreen;
        add6 =  copy[i + 1][1].rgbtGreen;
        avgGreen = (add1 + add2 + add3 + add4 + add5 + add6) / 6.0;

        //BLUE RGBT
        add1 =  copy[i - 1][0].rgbtBlue;
        add2 =  copy[i][0].rgbtBlue;
        add3 =  copy[i + 1][0].rgbtBlue;
        add4 =  copy[i - 1][1].rgbtBlue;
        add5 =  copy[i][1].rgbtBlue;
        add6 =  copy[i + 1][1].rgbtBlue;
        avgBlue = (add1 + add2 + add3 + add4 + add5 + add6) / 6.0;

        image[i][0].rgbtRed   = (round(avgRed));
        image[i][0].rgbtGreen = (round(avgGreen));
        image[i][0].rgbtBlue  = (round(avgBlue));
    }

    for (int i = 1; i <= (hgt - 1); i++)//Loops through the RIGHTMOST EDGE
    {
        int j = wdth;//Keeps the loop consistently at the rightmost edge (width - 1)

            //RED RGBT
            add1 =  copy[i - 1][wdth].rgbtRed;
            add2 =  copy[i][wdth].rgbtRed;
            add3 =  copy[i + 1][wdth].rgbtRed;
            add4 =  copy[i - 1][wdth - 1].rgbtRed;
            add5 =  copy[i][wdth - 1].rgbtRed;
            add6 =  copy[i + 1][wdth - 1].rgbtRed;
            avgRed = (add1 + add2 + add3 + add4 + add5 + add6) / 6.0;

            //GREEN RGBT
            add1 =  copy[i - 1][wdth].rgbtGreen;
            add2 =  copy[i][wdth].rgbtGreen;
            add3 =  copy[i + 1][wdth].rgbtGreen;
            add4 =  copy[i - 1][wdth - 1].rgbtGreen;
            add5 =  copy[i][wdth - 1].rgbtGreen;
            add6 =  copy[i + 1][wdth - 1].rgbtGreen;
            avgGreen = (add1 + add2 + add3 + add4 + add5 + add6) / 6.0;

            //BLUE RGBT
            add1 =  copy[i - 1][wdth].rgbtBlue;
            add2 =  copy[i][wdth].rgbtBlue;
            add3 =  copy[i + 1][wdth].rgbtBlue;
            add4 =  copy[i - 1][wdth - 1].rgbtBlue;
            add5 =  copy[i][wdth - 1].rgbtBlue;
            add6 =  copy[i + 1][wdth - 1].rgbtBlue;
            avgBlue = (add1 + add2 + add3 + add4 + add5 + add6) / 6.0;

            image[i][wdth].rgbtRed = (round(avgRed));
            image[i][wdth].rgbtGreen = (round(avgGreen));
            image[i][wdth].rgbtBlue = (round(avgBlue));
    }

    for (int i = 0; i <= 1; i++)
    {
        for (int j = 1; j <= (wdth - 1); j++)//Loops through the TOPMOST EDGE
        {
            //RED RGBT
            add1 = copy[i][j - 1].rgbtRed;
            add2 = copy[i][j].rgbtRed;
            add3 = copy[i][j + 1].rgbtRed;
            add4 = copy[i + 1][j - 1].rgbtRed;
            add5 = copy[i + 1][j].rgbtRed;
            add6 = copy[i + 1][j + 1].rgbtRed;
            avgRed = (add1 + add2 + add3 + add4 + add5 + add6) / 6.0;

            //GREEN RGBT
            add1 = copy[i][j - 1].rgbtGreen;
            add2 = copy[i][j].rgbtGreen;
            add3 = copy[i][j + 1].rgbtGreen;
            add4 = copy[i + 1][j - 1].rgbtGreen;
            add5 = copy[i + 1][j].rgbtGreen;
            add6 = copy[i + 1][j + 1].rgbtGreen;
            avgGreen = (add1 + add2 + add3 + add4 + add5 + add6) / 6.0;

            //BLUE RGBT
            add1 = copy[i][j - 1].rgbtBlue;
            add2 = copy[i][j].rgbtBlue;
            add3 = copy[i][j + 1].rgbtBlue;
            add4 = copy[i + 1][j - 1].rgbtBlue;
            add5 = copy[i + 1][j].rgbtBlue;
            add6 = copy[i + 1][j + 1].rgbtBlue;
            avgBlue = (add1 + add2 + add3 + add4 + add5 + add6) / 6.0;

            image[i][j].rgbtRed = (round(avgRed));
            image[i][j].rgbtGreen = (round(avgGreen));
            image[i][j].rgbtBlue = (round(avgBlue));
        }
    }

    int n = hgt;//Keeps loop consistent at the bottommost edge (height - 1)
        for (int j = 1; j <= (wdth - 1); j++)//Loops through the BOTTOMMOST EDGE
        {
            //RED RGBT
            add1 = copy[n][j - 1].rgbtRed;
            add2 = copy[n][j].rgbtRed;
            add3 = copy[n][j + 1].rgbtRed;
            add4 = copy[n - 1][j - 1].rgbtRed;
            add5 = copy[n - 1][j].rgbtRed;
            add6 = copy[n - 1][j + 1].rgbtRed;
            avgRed = (add1 + add2 + add3 + add4 + add5 + add6) / 6.0;

            //GREEN RGBT
            add1 = copy[n][j - 1].rgbtGreen;
            add2 = copy[n][j].rgbtGreen;
            add3 = copy[n][j + 1].rgbtGreen;
            add4 = copy[n - 1][j - 1].rgbtGreen;
            add5 = copy[n - 1][j].rgbtGreen;
            add6 = copy[n - 1][j + 1].rgbtGreen;
            avgGreen = (add1 + add2 + add3 + add4 + add5 + add6) / 6.0;

            //BLUE RGBT
            add1 = copy[n][j - 1].rgbtBlue;
            add2 = copy[n][j].rgbtBlue;
            add3 = copy[n][j + 1].rgbtBlue;
            add4 = copy[n - 1][j - 1].rgbtBlue;
            add5 = copy[n - 1][j].rgbtBlue;
            add6 = copy[n - 1][j + 1].rgbtBlue;
            avgBlue = (add1 + add2 + add3 + add4 + add5 + add6) / 6.0;

            image[n][j].rgbtRed = (round(avgRed));
            image[n][j].rgbtGreen = (round(avgGreen));
            image[n][j].rgbtBlue = (round(avgBlue));
        }

    //Loop through each row of the image (to get the last row were doing "height - 1" since were counting from 0)
    for (int i = 1; i <= (hgt - 1); i++)
    {
        //Loop through each pixel in the current row (to get the last row were doing do "row - 1" since were counting from 0)
        for (int j = 1; j <= (wdth - 1); j++)
        {
            //Calculate the average of EACH COLOR VALUE of the MIDDLE pixels by computing the AVERAGE of the ADJACENT NINE PIXELS AROUND IT

            //RED RGBT
            add1 = copy[i - 1][j - 1].rgbtRed;
            add2 = copy[i - 1][j].rgbtRed;
            add3 = copy[i - 1][j + 1].rgbtRed;
            add4 = copy[i][j - 1].rgbtRed;
            add5 = copy[i][j].rgbtRed;
            add6 = copy[i][j + 1].rgbtRed;
            add7 = copy[i + 1][j - 1].rgbtRed;
            add8 = copy[i + 1][j].rgbtRed;
            add9 = copy[i + 1][j + 1].rgbtRed;
            avgRed = (add1 + add2 + add3 + add4 + add5 + add6 + add7 + add8 + add9) / 9.0;

            //GREEN RGBT
            add1 = copy[i - 1][j - 1].rgbtGreen;
            add2 = copy[i - 1][j].rgbtGreen;
            add3 = copy[i - 1][j + 1].rgbtGreen;
            add4 = copy[i][j - 1].rgbtGreen;
            add5 = copy[i][j].rgbtGreen;
            add6 = copy[i][j + 1].rgbtGreen;
            add7 = copy[i + 1][j - 1].rgbtGreen;
            add8 = copy[i + 1][j].rgbtGreen;
            add9 = copy[i + 1][j + 1].rgbtGreen;
            avgGreen = (add1 + add2 + add3 + add4 + add5 + add6 + add7 + add8 + add9) / 9.0;


            //BLUE RGBT
            add1 = copy[i - 1][j - 1].rgbtBlue;
            add2 = copy[i - 1][j].rgbtBlue;
            add3 = copy[i - 1][j + 1].rgbtBlue;
            add4 = copy[i][j - 1].rgbtBlue;
            add5 = copy[i][j].rgbtBlue;
            add6 = copy[i][j + 1].rgbtBlue;
            add7 = copy[i + 1][j - 1].rgbtBlue;
            add8 = copy[i + 1][j].rgbtBlue;
            add9 = copy[i + 1][j + 1].rgbtBlue;
            avgBlue = (add1 + add2 + add3 + add4 + add5 + add6 + add7 + add8 + add9) / 9.0;

            image[i][j].rgbtRed = (round(avgRed));
            image[i][j].rgbtGreen = (round(avgGreen));
            image[i][j].rgbtBlue = (round(avgBlue));
        }
    }
    return;
}
