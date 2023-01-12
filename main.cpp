#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
int main(int, char**)
{
    Mat frame1, frame1_g;
    Mat frame2, frame2_g;
    Mat difference, difference2;
    Mat difference_init, difference_init2, BlackScreen, sum1;
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

    Mat BlackScreen_temp(frame1.rows, frame1.cols, CV_8UC1, Scalar(0,0,0));
    Mat in[] = { BlackScreen_temp, BlackScreen_temp, BlackScreen_temp };
    merge(in, 3, BlackScreen);

  
    absdiff(frame1, BlackScreen, difference_init);
    //threshold(difference_init, difference_init2, 5, 255, cv::THRESH_TOZERO);
    Mat gray;
    cvtColor(difference_init, gray, COLOR_BGR2GRAY);

    //Prog pierwszej klatki z jakim porownuje sie do czarnego ekranu
    threshold(gray, difference_init2, 5, 255, cv::THRESH_TOZERO);




    cap.read(frame2);
    for (;;)
    {
        frame2 = frame1.clone();
        cap.read(frame1);
        waitKey(1);

        cvtColor(frame1, frame1_g, COLOR_BGR2GRAY);
        cvtColor(frame2, frame2_g, COLOR_BGR2GRAY);

        absdiff(frame1_g, frame2_g, difference);
        //Prog ponizej ktorego usuwa roznice znalezione pomiedzy kolejnymi klatkami
        threshold(difference, difference2, 5, 255, cv::THRESH_TOZERO);
        
        sum1 = difference_init2 + difference2;

        //imshow("Live", frame1_g);
        imshow("Live2", sum1);

        

        
        if (waitKey(1) >= 0)
            break;
    }
    return 0;
}