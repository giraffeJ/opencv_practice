#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

int frame_num;

using namespace std;
using namespace cv;

int _abs(int a, int b) {
	if (a > b) return a - b;
	else return b - a;
}

void extractImages(VideoCapture cap, int frame_skip, string dir_name, int hp) {
	Mat img, prev_img;
	int frame;
	cap.set(CAP_PROP_POS_FRAMES, 0);
	for (frame = 0; frame < frame_num; frame++) {
		cap.read(img);
		if (frame == 0) {
			prev_img = img.clone();
			continue;
		}
		if (frame % frame_skip == 0) {
			int sum = 0;
			for (int i = 0; i < img.rows; i++) {
				for (int j = 0; j < img.cols; j++) {
					sum += _abs(img.at<Vec3b>(i, j)[0], prev_img.at<Vec3b>(i, j)[0]);
					sum += _abs(img.at<Vec3b>(i, j)[1], prev_img.at<Vec3b>(i, j)[1]);
					sum += _abs(img.at<Vec3b>(i, j)[2], prev_img.at<Vec3b>(i, j)[2]);
				}
			}
			if (sum >= hp) {
				cout << dir_name + "/" + to_string(frame) + ".png" << endl;
				imwrite(dir_name + "/" + to_string(frame) + ".png", prev_img);
			}
			prev_img = img.clone();
		}
	}
}



void main() {

	string path = "Resources/test_video.mp4";
	VideoCapture cap(path);
	frame_num = cap.get(CAP_PROP_FRAME_COUNT);

	//extractImages(cap, 10, "frame_skip_10", 5000000);
	//extractImages(cap, 20, "frame_skip_20", 5000000);
	extractImages(cap, 30, "frame_skip_30", 5000000);

	cap.release();
	destroyAllWindows();

}