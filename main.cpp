//#include <opencv2/opencv.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/objdetect.hpp>
//#include <opencv2/core.hpp>
//#include <opencv2/features2d/features2d.hpp>
//#include <opencv2/video/background_segm.hpp>
//#include <iostream>
//
//
//using namespace cv;
//using namespace std;


// Shape(countours) & Colour Detection

/*
void getContours(Mat imgDil, Mat img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;
		string objectType;

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);

			int objCor = (int)conPoly[i].size();

			if (objCor == 3) { objectType = "Tri"; }
			else if (objCor == 4)
			{
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				cout << aspRatio << endl;
				if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "Square"; }
				else { objectType = "Rect"; }
			}
			else if (objCor > 4) { objectType = "Circle"; }

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
		}
	}
}

int main() {

	VideoCapture cap(0);
	Mat img, imgHSV, imgGray, imgBlur, imgCanny, imgDil, imgErode, mask;

	int hmin = 0, smin = 0, vmin = 0;
	int hmax = 179, smax = 255, vmax = 255;

	namedWindow("Trackbars", (1280, 720));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);

	while (true) {
		cap.read(img);

		cvtColor(img, imgGray, COLOR_BGR2GRAY);
		GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);
		Canny(imgBlur, imgCanny, 25, 75);

		Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(imgCanny, imgDil, kernel);
		erode(imgDil, imgErode, kernel);

		getContours(imgDil, img);

		cvtColor(img, imgHSV, COLOR_BGR2HSV);

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);

		imshow("Image", img);
		imshow("Image HSV", imgHSV);
		imshow("Image Mask", mask);
		waitKey(1);
	}

}
*/


//  Webcam

/*
int main() {

	VideoCapture cap(0);
	Mat img, imgGray, imgBlur, imgCanny, imgDil, imgErode;
	CascadeClassifier faceCascade;

	while (true) {
		cap.read(img);

		// Face Detection

		faceCascade.load("Resources/haarcascade_frontalface_default.xml");

		if (faceCascade.empty()) {
			cout << "XML file not loaded" << endl;
		}

		vector<Rect> faces;
		faceCascade.detectMultiScale(img, faces, 1.1, 10);

		for (int i = 0; i < faces.size(); i++) {
			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
		}

		imshow("Image", img);

		waitKey(1);

	}

}
*/


// Basic Functions

/*
int main() {

	VideoCapture cap(0);
	Mat img, imgGray, imgBlur, imgCanny, imgDil, imgErode;
	CascadeClassifier faceCascade;

	while (true) {
		cap.read(img);

		// Basic Functions

		cvtColor(img, imgGray, COLOR_BGR2GRAY);
		GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);
		Canny(imgBlur, imgCanny, 25, 75);

		Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(imgCanny, imgDil, kernel);
		erode(imgDil, imgErode, kernel);

		imshow("Image", img);
		imshow("Image Gray", imgGray);
		imshow("Image Blur", imgBlur);
		imshow("Image Canny", imgCanny);
		imshow("Image Dilation", imgDil);
		imshow("Image Erode", imgErode);

		waitKey(1);

	}

}
*/


//  Image

/*
int main() {

	string path = "Resources/test.png";
	Mat img = imread(path);
	imshow("Image", img);
	waitKey(0);

}
*/


//  Video

/*
void main() {

string path = "Resources/test_video.mp4";
VideoCapture cap(path);
Mat img;

while (true) {
	cap.read(img);
	imshow("Image", img);
	waitKey(20);
	}

}
*/


// Hand Detection

/*
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
*/



