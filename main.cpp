#include <stdio.h>
// #include <opencv2/opencv.hpp> // Opencv Library also added if needed. Opencv gives us function like 'resize' where we can specify Bilinear Interpolation
// #include <opencv2/imgcodecs.hpp>
// #include <opencv2/imgproc.hpp>
#include <iostream> // Input output stream
#include "Image.h"

// using namespace cv; // Standard opencv library
using namespace std;
int main(int argc, char** argv) 
{
    Image test("D:/Work/ITWS/1614685.jpg");
    test.write("new.png");
    Image gray_avg = test;

    gray_avg.grayscale_avg();
    gray_avg.write("gray_avg.png"); //Writing Grayscale image


// // Read Image using opencv
//     Mat image;
//     Mat imgGray;
//     image = imread("D:/Work/ITWS/1614685.jpg"); ///image import
//     if ( !image.data )
//     {
//         printf("No image data \n");
//         return -1;
//     }
//     cvtColor(image, imgGray, COLOR_BGR2GRAY);

//     cout<< imgGray.cols*1.3<<endl;
//     cout<< imgGray.rows*1.3;


//     namedWindow("Display Image", WINDOW_AUTOSIZE );
//     imshow("Display Image", imgGray);
//     waitKey(0);

    return 0;
}