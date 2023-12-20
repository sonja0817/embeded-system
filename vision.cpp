#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

#define TEST

using namespace cv;
using namespace std;

#ifdef REAL
int main(int argc, char* argv[])
{
    Mat frame;
    Mat kernel;
    Mat Mog2;
    Ptr<BackgroundSubtractor> pMog2;

    //pMog2 = createBackgroundSubtractorMOG2();
    pMog2 = new BackgroundSubtractorMOG2();

    //VideoCapture cap("square.mp4");
    VideoCapture cap(2);
 
    Mat a, b, c;
    vector<vector<Point> > contours;

    cap >> a;

    int hist = 0;
    int total_fix = a.rows * a.cols;
    int level;

    while (1)
    {
        cap >> a;

        //pMog2->apply(a, frame);     //MOG2
        pMog2->operator()(a, frame);
        kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        morphologyEx(frame, frame, MORPH_ERODE, kernel);
        

        //cvtColor(a, b, COLOR_BGR2GRAY);         //threshold
        //threshold(b, c, 200, 255, THRESH_BINARY);
        

        //bitwise_and(c, frame, c);

   
        imshow("ther", frame);
        findContours(frame, contours,RETR_EXTERNAL, CHAIN_APPROX_NONE);
        //drawContours(a, contours, -1, Scalar(0, 0, 255), 1);

        for (int i = 0; i < contours.size(); i++)
        {
            Rect rect = boundingRect(contours[i]);
            rectangle(a, rect, Scalar(0, 0, 255), -1);
        }


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
        waitKey(30);
    }
}
#endif

#ifdef TEST
int main(int argc, char * argv[])
{
    Mat frame;
    Mat kernel;
    Mat a, b, c, pre;
    Mat a_g, b_g, c_g;
    Mat diff, diff1, diff2;
    int hist = 0;
    int total_fix = a.rows * a.cols;
    int level;
    
    //VideoCapture cap("square.mp4");
    VideoCapture cap(2);

    vector<vector<Point> > contours;

    cap >> a;
    cap >> b;
    
    
    while (1)
    {
        cap >> c;
        cvtColor(a, a_g, COLOR_BGR2GRAY);
        cvtColor(b, b_g, COLOR_BGR2GRAY);
        cvtColor(c, c_g, COLOR_BGR2GRAY);
        
        absdiff(a_g, b_g, diff1);
        threshold(diff1, diff1, 50, 255, THRESH_BINARY);
        absdiff(b_g, c_g, diff2);
        threshold(diff2, diff2, 50, 255, THRESH_BINARY);

        bitwise_and(diff1, diff2, diff);

        //drawContours(a, contours, -1, Scalar(0, 0, 255), 1);


        kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        morphologyEx(diff1, diff, MORPH_OPEN, kernel);


        imshow("ther", diff);

        findContours(diff, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
        for (int i = 0; i < contours.size(); i++)
        {
            Rect rect = boundingRect(contours[i]);
            rectangle(a, rect, Scalar(0, 0, 255), -1);
        }


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
        a = b.clone();
        b = c.clone();
        waitKey(30);
    }
}
#endif 
