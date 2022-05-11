#include<time.h>
#include<string>
#include<iostream>
#include<filesystem>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

using namespace cv;
using namespace std;
using namespace std::filesystem;

FILE* log_txt, * out;

int _abs(int a, int b) {
	if (a > b) return a - b;
	else return b - a;
}

int calcImageDiff(Mat img1, Mat img2) {
	if (img1.rows != img2.rows || img1.cols != img2.cols) {
		cout << "ERR::Size of img1 and img2 is different" << endl;
		exit(0);
	}
	int sum = 0;
	for (int i = 0; i < img1.rows; i++) {
		for (int j = 0; j < img1.cols; j++) {
			sum += _abs(img1.at<Vec3b>(i, j)[0], img2.at<Vec3b>(i, j)[0]);
			sum += _abs(img1.at<Vec3b>(i, j)[1], img2.at<Vec3b>(i, j)[1]);
			sum += _abs(img1.at<Vec3b>(i, j)[2], img2.at<Vec3b>(i, j)[2]);
		}
	}
	return sum;
}

void checkFrameChange(VideoCapture cap, int frame_skip, FILE* f) {
	int frame_num = cap.get(CAP_PROP_FRAME_COUNT);
	cap.set(CAP_PROP_POS_FRAMES, 0);
	Mat img, prev_img;
	for (int frame = 0; frame < frame_num; frame++) {
		cap.read(img);
		if (frame % frame_skip != 0) continue;
		resize(img, img, Size(1280, 720));
		if (frame == 0) {
			prev_img = img.clone();
			continue;
		}
		fprintf(f, "%d,%d\n", frame, calcImageDiff(img, prev_img));
		prev_img = img.clone();
	}
}
int main() {
	string path = "D:/TakeNote/Video";
	int num = 0;
	time_t start, end;
	log_txt = fopen("log.txt", "w");
	for (const auto& file : directory_iterator(path)) {
		num++;
		string textname = "output" + to_string(num) + ".txt";
		out = fopen(textname.c_str(), "w");
		start = time(NULL);
		VideoCapture cap(file.path().string());
		fprintf(log_txt, "Video name : %s\n", file.path().string().c_str());
		printf("Video name : %s\n", file.path().string().c_str());
		checkFrameChange(cap, 30, out);
		end = time(NULL);
		fprintf(log_txt, "Video number %d process completed. (frame skip = 30)\n", num);
		printf("Video number %d process completed. (frame skip = 30)\n", num);
		int fps = cap.get(CAP_PROP_FPS);
		int frame_count = (int)cap.get(CAP_PROP_FRAME_COUNT);
		int dur_min = (frame_count / fps) / 60;
		int dur_sec = (frame_count / fps) % 60;
		fprintf(log_txt, "Duration = %d min %d sec, Frame_count = %d, FPS = %d\n", dur_min, dur_sec, frame_count, fps);
		fprintf(log_txt, "Process time = %lld seconds\n", end - start);
		fclose(out);
		cap.release();
		destroyAllWindows();
		
	}
}

