#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

#define CAM


#ifdef CAM

int main(int argc, char* argv[])
{
    Mat current_frame, cvt_frame, mog2;
    Mat kernel;
    kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

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
        cvt_frame = current_frame.clone();
        //pMog2->apply(a, frame, 0);     //MOG2
        pMog2->operator()(current_frame, mog2, 0);
        morphologyEx(mog2, mog2, MORPH_OPEN, kernel);

        imshow("ther", mog2);
        findContours(mog2, contours,RETR_EXTERNAL, CHAIN_APPROX_NONE);
        drawContours(cvt_frame, contours, -1, Scalar(0, 0, 255), -1);

        for (int y = 0; y < current_frame.rows; y++)
        {
            for (int x = 0; x < current_frame.cols; x++)
            {
                if (cvt_frame.at<Vec3b>(y, x)[2] == 255)
                {
                    hist++;
                }
            }
        }
        
        
        imshow("test", cvt_frame);

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
#endif

#ifdef VIDEO
int main(int argc, char* argv[])
{
    Mat current_frame, cvt_frame, mog2;
    Mat kernel;
    kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

    int level;
    int hist = 0;

    vector<vector<Point> > contours;

    Ptr< BackgroundSubtractor> pMog2;
    //pMog2 = createBackgroundSubtractorMOG2();
   
    VideoCapture cap("river.mov");
   
    cap >> current_frame;
    int total_fix = current_frame.rows * current_frame.cols;


    while (1)
    {
        cap >> current_frame;
        cap >> current_frame;
        cap >> current_frame;
        cap >> current_frame;
        cap >> current_frame;
        cap >> current_frame;
        cap >> current_frame;
        cap >> current_frame;
        cap >> current_frame;
        cvt_frame = current_frame.clone();
        
        //pMog2->apply(current_frame, mog2, 0);
        morphologyEx(mog2, mog2, MORPH_ERODE, kernel);

        imshow("ther", mog2);
        findContours(mog2, contours,RETR_EXTERNAL, CHAIN_APPROX_NONE);
        drawContours(cvt_frame, contours, -1, Scalar(0, 0, 255), -1);

        for (int y = 0; y < current_frame.rows; y++)
        {
            for (int x = 0; x < current_frame.cols; x++)
            {
                if (cvt_frame.at<Vec3b>(y, x)[2] == 255)
                {
                    hist++;
                }
            }
        }
        
        imshow("test", cvt_frame);

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
#endif
