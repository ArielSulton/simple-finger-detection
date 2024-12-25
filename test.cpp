#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/video/background_segm.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void getContours(Mat imgDilate, Mat img, Scalar lower, Scalar upper) {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(imgDilate, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());

    for (int i = 0; i < contours.size(); i++) {
        int area = contourArea(contours[i]);
        //cout << area << endl;

        string objectType;

        if (area > 1000) {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            boundRect[i] = boundingRect(conPoly[i]);
            //cout << conPoly[i].size() << endl;

            int objCorner = (int)conPoly[i].size();

            if (objCorner <= 8) {
                objectType = "1 or 2 fingers";
            }

            else if (objCorner <= 10) {
                objectType = "3 fingers";
            }

            else if (objCorner <= 14) {
                objectType = "4 fingers";
            }

            else if (objCorner <= 20) {
                objectType = "5 fingers";
            }

            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);
            putText(img, objectType, {boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_PLAIN, 1, Scalar(0, 70, 255), 2);
        }
    }
}

int main() {
    VideoCapture cap(0);
    Mat img, imgHSV, imgGray, imgBlur, imgCanny, imgDilate, imgErode, mask;

    int hmin = 0, smin = 0, vmin = 0;
    int hmax = 179, smax = 255, vmax = 255;

    namedWindow("Trackbars", (640, 200));
    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);

    while (true) {
        cap.read(img);

        cvtColor(img, imgHSV, COLOR_BGR2HSV);

        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);

        //cvtColor(mask, imgGray, COLOR_BGR2GRAY);
        //GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);
        //Canny(mask, imgCanny, 25, 75);

        erode(mask, imgErode, getStructuringElement(MORPH_RECT, Size(3, 3)));
        dilate(imgErode, imgDilate, getStructuringElement(MORPH_RECT, Size(3, 3)));

        getContours(imgDilate, img, lower, upper);

        imshow("Image", img);
        imshow("Image HSV", imgHSV);
        imshow("Image Dilate", imgDilate);
        //imshow("Mask", mask);

        waitKey(1);
    }

}