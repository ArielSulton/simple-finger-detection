/*
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgHSV, mask;
int hmin = 0, smin = 110, vmin = 153;
int hmax = 19, smax = 240, vmax = 255;
int erosi = 0, dilasi = 0;

int main() {
    VideoCapture cap(0);
    Mat img;
    namedWindow("TrackBars", (640, 200));
    createTrackbar("Hue min", "TrackBars", &hmin, 179);
    createTrackbar("Smin", "TrackBars", &smin, 179);
    createTrackbar("Vmin", "TrackBars", &vmin, 255);
    createTrackbar("Hmax", "TrackBars", &hmax, 255);
    createTrackbar("Smax", "TrackBars", &smax, 255);
    createTrackbar("Vmax", "TrackBars", &vmax, 255);
    createTrackbar("Erosi", "TrackBars", &erosi, 10);
    createTrackbar("Dilasi", "TrackBars", &dilasi, 10);
    Mat imgBlur, imgcanny, imgdia, imgrode;

    while (true) {
        Mat Karnel = getStructuringElement(MORPH_RECT, Size(5, 5));
        cap.read(img);
        cvtColor(img, imgHSV, COLOR_BGR2HSV);
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);

        //GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
        //Canny(imgBlur, imgcanny, 25, 75);
        erode(mask, imgrode, getStructuringElement(MORPH_ELLIPSE, Size(2 * erosi + 1, 2 * erosi + 1), Point(erosi, erosi)));
        dilate(imgrode, imgdia, getStructuringElement(MORPH_ELLIPSE, Size(2 * dilasi + 1, 2 * dilasi + 1), Point(dilasi, dilasi)));


        vector<vector<Point>> contours;
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        int largestContourIndex = -1;
        double largestContourArea = 0.0;

        for (int i = 0; i < contours.size(); i++) {
            double area = contourArea(contours[i]);
            if (area > largestContourArea) {
                largestContourArea = area;
                largestContourIndex = i;
            }
            //Rect boundingBox = boundingRect(contours[i]);
            //rectangle(img, boundingBox.tl(), boundingBox.br(), Scalar(0, 255, 0), 2);
        }


        if (largestContourIndex != -1) {
            Rect boundingBox = boundingRect(contours[largestContourIndex]);
            rectangle(img, boundingBox.tl(), boundingBox.br(), Scalar(0, 255, 0), 2);
        }



        imshow("Image ori", img);
        imshow("img hsv", imgHSV);
        imshow("img scalar", imgdia);
        waitKey(1);
    }
}
*/