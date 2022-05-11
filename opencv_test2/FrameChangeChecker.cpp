#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
FILE *out1, *out2, *out3, *out4, *out5, *out6, *out7, *out8;

int frame_num;

using namespace std;
using namespace cv;

int _abs(int a, int b) {
	if (a > b) return a - b;
	else return b - a;
}

void salt(Mat& mat, int count) {
	for (int i = 0; i < count; i++) {
		int x = rand() % mat.cols;
		int y = rand() % mat.rows;

		mat.at<Vec3b>(y, x)[0] = 255;
		mat.at<Vec3b>(y, x)[1] = 255;
		mat.at<Vec3b>(y, x)[2] = 255;
	}
}

void checkFrameChange(VideoCapture cap, int frame_skip, FILE *f, bool grayScale) {
	Mat img, prev_img;
	int frame;
	cap.set(CAP_PROP_POS_FRAMES, 0);
	for (frame = 0; frame < frame_num; frame++) {
		cap.read(img);
		if(grayScale) cvtColor(img, img, COLOR_BGR2GRAY);
		if (frame == 0) {
			prev_img = img.clone();
			continue;
		}
		if (frame % frame_skip == 0) {
			int sum = 0;
			for (int i = 0; i < img.rows; i++) {
				for (int j = 0; j < img.cols; j++) {
					if (grayScale) {
						sum = sum + _abs(img.at<uchar>(i, j), prev_img.at<uchar>(i, j));
						continue;
					}
					sum += _abs(img.at<Vec3b>(i, j)[0], prev_img.at<Vec3b>(i, j)[0]);
					sum += _abs(img.at<Vec3b>(i, j)[1], prev_img.at<Vec3b>(i, j)[1]);
					sum += _abs(img.at<Vec3b>(i, j)[2], prev_img.at<Vec3b>(i, j)[2]);
				}
			}
			fprintf(f, "%d,%d\n", frame, sum);
			prev_img = img.clone();
		}
	}
	printf("frame_skip : %d / grayScale : %s done\n", frame_skip, grayScale ? "true" : "false");
}

void main() {
	out1 = fopen("output1.txt", "w");
	out2 = fopen("output2.txt", "w");
	out3 = fopen("output3.txt", "w");
	out4 = fopen("output4.txt", "w");
	out5 = fopen("output5.txt", "w");
	out6 = fopen("output6.txt", "w");
	out7 = fopen("output7.txt", "w");
	out8 = fopen("output8.txt", "w");

	string path = "Resources/test_video.mp4";
	VideoCapture cap(path);
	frame_num = cap.get(CAP_PROP_FRAME_COUNT);

	checkFrameChange(cap, 1, out1, false);
	checkFrameChange(cap, 5, out2, false);
	checkFrameChange(cap, 10, out3, false);
	checkFrameChange(cap, 20, out4, false);
	checkFrameChange(cap, 1, out5, true);
	checkFrameChange(cap, 5, out6, true);
	checkFrameChange(cap, 10, out7, true);
	checkFrameChange(cap, 20, out8, true);

	cap.release();
	destroyAllWindows();
	fclose(out1);
	fclose(out2);
	fclose(out3);
	fclose(out4);
	fclose(out5);
	fclose(out6);

}