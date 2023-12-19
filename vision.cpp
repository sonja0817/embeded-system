#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    VideoCapture cap("square.mov");
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
    
    while(1)
    {
        cap >> b;
        cvtColor(a, a_g, COLOR_BGR2GRAY);
        cvtColor(b, b_g, COLOR_BGR2GRAY);
        
        absdiff(a_g, b_g, diff1);
        threshold(diff1, diff1, thre, 255, THRESH_BINARY);
        
        getStructuringElement(MORPH_RECT, Size(3,3));
        morphologyEx(diff1, diff, MORPH_OPEN, k);
    
        pMog2->apply(b, frame);
        morphologyEx(frame, frame, MORPH_ERODE, k);
        cvtColor(frame , frame, COLOR_GRAY2BGR);
        bitwise_or(frame, b, diff);
        imshow("mog2", frame);
        imshow("diff", diff);
        
        a = b.clone();
        
    
        if(waitKey(50) >= 0)
            break;
        
    }
    return 0;
}
