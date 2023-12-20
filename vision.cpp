#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    Mat current_frame, cvt_frame;
    Mat kernel;
    Mat mog2;
    Mat a, b, c;
    int level;
    int hist = 0;
    vector<vector<Point> > contours;

    //pMog2 = createBackgroundSubtractorMOG2();
    Ptr< BackgroundSubtractor> pMog2;
    pMog2 = new BackgroundSubtractorMOG2();
    //VideoCapture cap("river.mov");
    VideoCapture cap(2);


    cap >> current_frame;
    int total_fix = current_frame.rows * current_frame.cols;


    while (1)
    {
        cap >> current_frame;
        
        //pMog2->apply(a, frame, 0);     //MOG2
        pMog2->operator()(current_frame, mog2, 0);
        kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        morphologyEx(mog2, mog2, MORPH_ERODE, kernel);

        imshow("ther", mog2);
        findContours(frame, contours,RETR_EXTERNAL, CHAIN_APPROX_NONE);
        drawContours(cvt_frame, contours, -1, Scalar(0, 0, 255), -1);

        /*for (int i = 0; i < contours.size(); i++)
        {
            Rect rect = boundingRect(contours[i]);
            rectangle(a, rect, Scalar(0, 0, 255), -1);
        }*/


        for (int y = 0; y < a.rows; y++)
        {
            for (int x = 0; x < a.cols; x++)
            {
                if (a.at<Vec3b>(y, x)[2] == 255)
                {
                    hist++;
                }
            }
        }
        
        imshow("test", a);

        if (hist >= total_fix * 0.3 && hist < total_fix * 0.4)
        {
            cout << "notice" << endl;
            level = 2;
        }
        else if (hist >= total_fix * 0.4 && hist < total_fix * 0.5)
        {
            cout << "caution" << endl;
            level = 4;
        }
        else if (hist >= total_fix * 0.6 && hist < total_fix * 0.7)
        {
            cout << "warning" << endl;
            level = 6;
        }
        else if (hist >= total_fix * 0.7)
        {
            cout << "danger" << endl;
            level = 8;
        }

        hist = 0;
        waitKey(10);
    }
}
