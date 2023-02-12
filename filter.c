#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++) // for each row in image
    {
        for (int col = 0; col < width; col++) // for each column in image , ' to iterate pixel by pixel '
        {
            // here we calculate the average as its algorathinm finding gray filter
            int average = round((image[row][col].rgbtBlue + image[row][col].rgbtGreen + image[row][col].rgbtRed) / 3.0);

            // set all RGBs to average
            image[row][col].rgbtRed = average;
            image[row][col].rgbtGreen = average;
            image[row][col].rgbtBlue = average;

        }
    }
    //printf("%i\n",image[22][44].rgbtBlue);
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // we calculate numerb of swaps , to be width / 2 , works with odd and even
    int swaps = width / 2;
    for (int row = 0; row < height; row++) // for each row
    {
        for (int swap = 0; swap < swaps; swap++) // for each swap
        {
            // create temp variable to store value in it
            // knwoing that , starts from swap = 0 , swap with last ' width-(i+1) ' index

            RGBTRIPLE temp = image[row][swap]; // store left pixel to tem
            image[row][swap] = image[row][width - (swap + 1)]; // move right pixel to left one
            image[row][width - (swap + 1)] = temp; // put temp to the right pixel

        }
    }

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // copying image pixel by pixel nested loop  @@

    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // copy pixel by pixel
            copy[row][col].rgbtRed = image[row][col].rgbtRed;
            copy[row][col].rgbtGreen = image[row][col].rgbtGreen;
            copy[row][col].rgbtBlue = image[row][col].rgbtBlue;
        }
    }




    // adjust image in copied version

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // sum if the nighboor pixel in pound ' will be checked with 8 ifs
            float sum_red = 0.0;
            float sum_green = 0.0;
            float sum_blue = 0.0;

            // number of blocks
            float blocks = 1; // the original medium

            // (1) left upper pixel
            if (((row - 1) >= 0) && ((col - 1) >= 0))
            {

                sum_red = sum_red + image[row - 1][col - 1].rgbtRed;
                sum_green = sum_green + image[row - 1][col - 1].rgbtGreen;
                sum_blue = sum_blue + image[row - 1][col - 1].rgbtBlue;
                blocks++;

            }

            // (2) upper pixel
            if ((row - 1) >= 0)
            {

                sum_red = sum_red + image[row - 1][col].rgbtRed;
                sum_green = sum_green + image[row - 1][col].rgbtGreen;
                sum_blue = sum_blue + image[row - 1][col].rgbtBlue;
                blocks++;
            }

            // (3) right upper pixel
            if (((row - 1) >= 0) && ((col + 1) < width))
            {

                sum_red = sum_red + image[row - 1][col + 1].rgbtRed;
                sum_green = sum_green + image[row - 1][col + 1].rgbtGreen;
                sum_blue = sum_blue + image[row - 1][col + 1].rgbtBlue;
                blocks++;

            }

            // (4) left pixel
            if (((col - 1) >= 0))
            {

                sum_red = sum_red + image[row][col - 1].rgbtRed;
                sum_green = sum_green + image[row][col - 1].rgbtGreen;
                sum_blue = sum_blue + image[row][col - 1].rgbtBlue;
                blocks++;

            }

            // (5) same pixel
            sum_red = sum_red + image[row][col].rgbtRed;
            sum_green = sum_green + image[row][col].rgbtGreen;
            sum_blue = sum_blue + image[row][col].rgbtBlue;

            // (6) right pixel
            if ((col + 1) < width)
            {

                sum_red = sum_red + image[row][col + 1].rgbtRed;
                sum_green = sum_green + image[row][col + 1].rgbtGreen;
                sum_blue = sum_blue + image[row][col + 1].rgbtBlue;
                blocks++;
            }

            // (7) left below pixel
            if (((row + 1) < height) && ((col - 1) >= 0))
            {

                sum_red = sum_red + image[row + 1][col - 1].rgbtRed;
                sum_green = sum_green + image[row + 1][col - 1].rgbtGreen;
                sum_blue = sum_blue + image[row + 1][col - 1].rgbtBlue;
                blocks++;

            }

            // (8) lower pixel
            if ((row + 1) < height)
            {

                sum_red = sum_red + image[row + 1][col].rgbtRed;
                sum_green = sum_green + image[row + 1][col].rgbtGreen;
                sum_blue = sum_blue + image[row + 1][col].rgbtBlue;
                blocks++;
            }

            // (9) right below pixel
            if (((row + 1) < height) && ((col + 1) < width))
            {

                sum_red = sum_red + image[row + 1][col + 1].rgbtRed;
                sum_green = sum_green + image[row + 1][col + 1].rgbtGreen;
                sum_blue = sum_blue + image[row + 1][col + 1].rgbtBlue;
                blocks++;
            }

            copy[row][col].rgbtRed = round(sum_red / blocks); // get average into copy pixel
            copy[row][col].rgbtGreen = round(sum_green / blocks); // get into copy pixel
            copy[row][col].rgbtBlue = round(sum_blue / blocks); // get into copy pixel

        }
    }


    // after finish creating new image into 'copy' 2darray pixels, put them in original image variable

    // copying from 'copy variable' to ' original image variable ' pixel by pixel

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col].rgbtRed = copy[row][col].rgbtRed;
            image[row][col].rgbtGreen = copy[row][col].rgbtGreen;
            image[row][col].rgbtBlue = copy[row][col].rgbtBlue;
        }
    }

}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // copying image pixel by pixel nested loop @@

    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // copy pixel by pixel
            copy[row][col].rgbtRed = image[row][col].rgbtRed;
            copy[row][col].rgbtGreen = image[row][col].rgbtGreen;
            copy[row][col].rgbtBlue = image[row][col].rgbtBlue;
        }
    }




    // adjust image in copied version

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            //Gxs
            int gx_red = 0;
            int gx_green = 0;
            int gx_blue = 0;

            //Gys
            int gy_red = 0;
            int gy_green = 0;
            int gy_blue = 0;





            // (1) left upper pixel
            if (((row - 1) >= 0) && ((col - 1) >= 0)) // if that pixel inside range
            {
                // sum first component of gx from first square , and so on .
                gx_red = gx_red + (-1 * image[row - 1][col - 1].rgbtRed);
                gx_green = gx_green + (-1 * image[row - 1][col - 1].rgbtGreen);
                gx_blue = gx_blue + (-1 * image[row - 1][col - 1].rgbtBlue);

                // sum first component of gy from first square , and so on .

                gy_red = gy_red + (-1 * image[row - 1][col - 1].rgbtRed);
                gy_green = gy_green + (-1 * image[row - 1][col - 1].rgbtGreen);
                gy_blue = gy_blue + (-1 * image[row - 1][col - 1].rgbtBlue);


            }





            // (2) upper pixel
            if ((row - 1) >= 0) // if that pixel inside range
            {
                // sum first component of gx from first square , and so on .
                gx_red = gx_red + (0 * image[row - 1][col].rgbtRed);
                gx_green = gx_green + (0 * image[row - 1][col].rgbtGreen);
                gx_blue = gx_blue + (0 * image[row - 1][col].rgbtBlue);

                // sum first component of gy from first square , and so on .

                gy_red = gy_red + (-2 * image[row - 1][col].rgbtRed);
                gy_green = gy_green + (-2 * image[row - 1][col].rgbtGreen);
                gy_blue = gy_blue + (-2 * image[row - 1][col].rgbtBlue);
            }







            // (3) right upper pixel
            if (((row - 1) >= 0) && ((col + 1) < width)) // if that pixel inside range
            {
                // sum first component of gx from first square , and so on .
                gx_red = gx_red + (1 * image[row - 1][col + 1].rgbtRed);
                gx_green = gx_green + (1 * image[row - 1][col + 1].rgbtGreen);
                gx_blue = gx_blue + (1 * image[row - 1][col + 1].rgbtBlue);

                // sum first component of gy from first square , and so on .

                gy_red = gy_red + (-1 * image[row - 1][col + 1].rgbtRed);
                gy_green = gy_green + (-1 * image[row - 1][col + 1].rgbtGreen);
                gy_blue = gy_blue + (-1 * image[row - 1][col + 1].rgbtBlue);

            }




            // (4) left pixel
            if (((col - 1) >= 0)) // if that pixel inside range
            {
                // sum first component of gx from first square , and so on .
                gx_red = gx_red + (-2 * image[row][col - 1].rgbtRed);
                gx_green = gx_green + (-2 * image[row][col - 1].rgbtGreen);
                gx_blue = gx_blue + (-2 * image[row][col - 1].rgbtBlue);

                // sum first component of gy from first square , and so on .

                gy_red = gy_red + (0 * image[row][col - 1].rgbtRed);
                gy_green = gy_green + (0 * image[row][col - 1].rgbtGreen);
                gy_blue = gy_blue + (0 * image[row][col - 1].rgbtBlue);

            }


            // (5) same pixel
            //sum_red = sum_red + image[row][col].rgbtRed;
            //sum_green = sum_green + image[row][col].rgbtGreen;
            //sum_blue = sum_blue + image[row][col].rgbtBlue;





            // (6) right pixel
            if ((col + 1) < width) // if that pixel inside range
            {

                // sum first component of gx from first square , and so on .
                gx_red = gx_red + (2 * image[row][col + 1].rgbtRed);
                gx_green = gx_green + (2 * image[row][col + 1].rgbtGreen);
                gx_blue = gx_blue + (2 * image[row][col + 1].rgbtBlue);

                // sum first component of gy from first square , and so on .

                gy_red = gy_red + (0 * image[row][col + 1].rgbtRed);
                gy_green = gy_green + (0 * image[row][col + 1].rgbtGreen);
                gy_blue = gy_blue + (0 * image[row][col + 1].rgbtBlue);



            }







            // (7) left below pixel
            if (((row + 1) < height) && ((col - 1) >= 0)) // if that pixel inside range
            {
                // sum first component of gx from first square , and so on .
                gx_red = gx_red + (-1 * image[row + 1][col - 1].rgbtRed);
                gx_green = gx_green + (-1 * image[row + 1][col - 1].rgbtGreen);
                gx_blue = gx_blue + (-1 * image[row + 1][col - 1].rgbtBlue);

                // sum first component of gy from first square , and so on .

                gy_red = gy_red + (1 * image[row + 1][col - 1].rgbtRed);
                gy_green = gy_green + (1 * image[row + 1][col - 1].rgbtGreen);
                gy_blue = gy_blue + (1 * image[row + 1][col - 1].rgbtBlue);

            }






            // (8) lower pixel
            if ((row + 1) < height) // if that pixel inside range
            {
                // sum first component of gx from first square , and so on .
                gx_red = gx_red + (0 * image[row + 1][col].rgbtRed);
                gx_green = gx_green + (0 * image[row + 1][col].rgbtGreen);
                gx_blue = gx_blue + (0 * image[row + 1][col].rgbtBlue);

                // sum first component of gy from first square , and so on .

                gy_red = gy_red + (2 * image[row + 1][col].rgbtRed);
                gy_green = gy_green + (2 * image[row + 1][col].rgbtGreen);
                gy_blue = gy_blue + (2 * image[row + 1][col].rgbtBlue);
            }






            // (9) right below pixel
            if (((row + 1) < height) && ((col + 1) < width)) // if that pixel inside range
            {
                // sum first component of gx from first square , and so on .
                gx_red = gx_red + (1 * image[row + 1][col + 1].rgbtRed);
                gx_green = gx_green + (1 * image[row + 1][col + 1].rgbtGreen);
                gx_blue = gx_blue + (1 * image[row + 1][col + 1].rgbtBlue);

                // sum first component of gy from first square , and so on .

                gy_red = gy_red + (1 * image[row + 1][col + 1].rgbtRed);
                gy_green = gy_green + (1 * image[row + 1][col + 1].rgbtGreen);
                gy_blue = gy_blue + (1 * image[row + 1][col + 1].rgbtBlue);

            }


            // calculate round of root gx^2 + gy^2 to set the answer into pixel color

            // check red
            int red = round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));
            if (red > 255)
            {
                red = 255;
            }
            copy[row][col].rgbtRed = red;

            // check green
            int green = round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
            if (green > 255)
            {
                green = 255;
            }
            copy[row][col].rgbtGreen = green;

            // check blue
            int blue = round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));
            if (blue > 255)
            {
                blue = 255;
            }
            copy[row][col].rgbtBlue = blue;



        }
    }


    // after finish creating new image into 'copy' 2darray pixels, put them in original image variable

    // copying from 'copy variable' to ' original image variable ' pixel by pixel

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col].rgbtRed = copy[row][col].rgbtRed;
            image[row][col].rgbtGreen = copy[row][col].rgbtGreen;
            image[row][col].rgbtBlue = copy[row][col].rgbtBlue;
        }
    }



}
