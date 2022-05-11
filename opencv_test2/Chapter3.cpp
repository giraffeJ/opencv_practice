#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

////////////////////// Resize and Crop ////////////////////////////

void main() {

	string path = "Resources/cat.png";
	Mat img = imread(path);
	Mat imgResize, imgCrop;

	//cout << img.size() << endl; // 521*531
	resize(img, imgResize, Size(), 0.5, 0.5); // or Size(640, 480)

	Rect roi(270, 40, 220, 220); //roi = region on interest
	imgCrop = img(roi); //crop image


	imshow("Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image Crop", imgCrop);

	waitKey(0);

}