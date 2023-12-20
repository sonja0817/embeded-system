#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>


#ifdef _DEBUG        
#pragma comment(lib, "opencv_core247d.lib")
#pragma comment(lib, "opencv_imgproc247d.lib")   //MAT processing
#pragma comment(lib, "opencv_objdetect247d.lib") //HOGDescriptor
//#pragma comment(lib, "opencv_gpu247d.lib")
//#pragma comment(lib, "opencv_features2d247d.lib")
#pragma comment(lib, "opencv_highgui247d.lib")
#pragma comment(lib, "opencv_ml247d.lib")
//#pragma comment(lib, "opencv_stitching247d.lib");
//#pragma comment(lib, "opencv_nonfree247d.lib");
#pragma comment(lib, "opencv_video247d.lib")
#else
#pragma comment(lib, "opencv_core247.lib")
#pragma comment(lib, "opencv_imgproc247.lib")
#pragma comment(lib, "opencv_objdetect247.lib")
//#pragma comment(lib, "opencv_gpu247.lib")
//#pragma comment(lib, "opencv_features2d247.lib")
#pragma comment(lib, "opencv_highgui247.lib")
#pragma comment(lib, "opencv_ml247.lib")
//#pragma comment(lib, "opencv_stitching247.lib");
//#pragma comment(lib, "opencv_nonfree247.lib");
#pragma comment(lib, "opencv_video247d.lib")
#endif 




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
    //pMog2 = createBackgroundSubtractorMOG2();
    pMOG2 = new BackgroundSubtractorMOG2();

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

        //pMog2->apply(b, frame);
        pMOG2->operator()(b, frame);
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

    while (1)
    {
        cap >> a;

        //pMog2->apply(a, frame);     //MOG2
        pMog2->operator()(a, frame);
        kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        morphologyEx(frame, frame, MORPH_ERODE, kernel);
        

        cvtColor(a, b, COLOR_BGR2GRAY);         //threshold
        threshold(b, c, 150, 255, THRESH_BINARY);
        

        bitwise_and(c, frame, c);

   
        imshow("ther", c);
        findContours(c, contours,RETR_EXTERNAL, CHAIN_APPROX_NONE);
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
        }
        else if (hist >= total_fix * 0.4 && hist < total_fix * 0.5)
        {
            cout << "caution" << endl;
        }
        else if (hist >= total_fix * 0.6 && hist < total_fix * 0.7)
        {
            cout << "warning" << endl;
        }
        else if (hist >= total_fix * 0.7 && hist < total_fix * 0.8)
        {
            cout << "danger" << endl;
        }

        hist = 0;
        waitKey(30);
    }
}

#endif