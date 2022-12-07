#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
int main(int, char**)
{
    Mat frame1;
    Mat frame2;
    Mat difference;
    Mat thresh;
    vector<vector<Point> > cnts;

    VideoCapture cap;

    int deviceID = 0;
    int apiID = cv::CAP_ANY;
    cap.set(3, 512);
    cap.set(4, 288);
    cap.open(deviceID, apiID);

    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    cap.read(frame1);
    cap.read(frame2);
    for (;;)
    {
        absdiff(frame1, frame2, difference);

        

        frame2 = frame1;
        cap.read(frame1);

        imshow("Live", difference);
        
        if (waitKey(1) >= 0)
            break;
    }
    return 0;
}