#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
#define TEST

#ifdef REAL
int main(int argc, char* argv[])
{
    VideoCapture cap("square.mp4");
    Mat a, b, c;
    Mat a_g, b_g, c_g;
    Mat diff, diff1, diff2;
    Mat k;
    int thre = 5;

    Mat frame;
    Mat Mog2;
    Ptr<BackgroundSubtractor> pMog2;
    pMog2 = createBackgroundSubtractorMOG2();


    cap >> a;

    while (1)
    {
        cap >> b;
        cvtColor(a, a_g, COLOR_BGR2GRAY);
        cvtColor(b, b_g, COLOR_BGR2GRAY);

        absdiff(a_g, b_g, diff1);
        threshold(diff1, diff1, thre, 255, THRESH_BINARY);

        getStructuringElement(MORPH_RECT, Size(3, 3));
        morphologyEx(diff1, diff, MORPH_OPEN, k);

        pMog2->apply(b, frame);
        morphologyEx(frame, frame, MORPH_ERODE, k);
        cvtColor(frame, frame, COLOR_GRAY2BGR);
        bitwise_or(frame, b, diff);
        imshow("mog2", frame);
        imshow("diff", diff);

        a = b.clone();


        if (waitKey(50) >= 0)
            break;

    }
    return 0;
} 
#endif

#ifdef TEST
int main(int argc, char* argv[])
{

    Mat frame;
    Mat k;
    Mat Mog2;
    Ptr<BackgroundSubtractor> pMog2;
    pMog2 = createBackgroundSubtractorMOG2();
   

    VideoCapture cap("square.mp4");
    Mat a, b, c;
    vector<vector<Point>> contours;


    
    Point2f center;
    float radius = 0;
  
 

    while (1)
    {
        cap >> a;
        //pMog2->apply(a, frame);
        //k = getStructuringElement(MORPH_RECT, Size(3, 3));
        //morphologyEx(frame, frame, MORPH_ERODE, k);

        cvtColor(a, b, COLOR_BGR2GRAY);
        threshold(b, c, 200, 255, THRESH_BINARY);
        //bitwise_and(frame, c, frame);
        imshow("ther", c);
        findContours(c, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
        drawContours(a, contours, -1, Scalar(0, 0, 255), -1);


        imshow("test", a);
        waitKey(30);
    }
}

#endif