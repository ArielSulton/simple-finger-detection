#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // Open the camera
    VideoCapture cap(0);

    if (!cap.isOpened()) {
        cout << "Error opening camera." << endl;
        return -1;
    }

    while (true) {
        Mat frame;
        cap >> frame;

        if (frame.empty()) {
            cout << "Error capturing frame." << endl;
            break;
        }

        // Convert the frame to grayscale
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // Apply Gaussian blur to reduce noise and improve contour detection
        GaussianBlur(gray, gray, Size(5, 5), 0);

        // Threshold the image to create a binary image
        threshold(gray, gray, 50, 255, THRESH_BINARY);

        // Find contours in the binary image
        vector<vector<Point>> contours;
        findContours(gray, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // Iterate over the contours to find the hand
        for (size_t i = 0; i < contours.size(); i++) {
            double area = contourArea(contours[i]);

            // Adjust this value based on your environment and lighting conditions
            if (area > 1000) {
                // Draw the contour around the hand
                drawContours(frame, contours, i, Scalar(0, 255, 0), 2);

                // Extract bounding box around the hand
                Rect boundingBox = boundingRect(contours[i]);

                // Draw the bounding box
                rectangle(frame, boundingBox.tl(), boundingBox.br(), Scalar(0, 0, 255), 2);

                // Display the detected hand gesture
                putText(frame, "Hand Detected", Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
            }
        }

        // Display the frame
        imshow("Hand Gesture Detection", frame);

        // Break the loop if the 'Esc' key is pressed
        if (waitKey(30) == 27) {
            break;
        }
    }

    // Release the camera
    cap.release();

    // Destroy all OpenCV windows
    destroyAllWindows();

    return 0;
}
