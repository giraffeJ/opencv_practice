#include<iostream>
#include<filesystem>
using namespace std;
using namespace std::filesystem;


int main() {
	string path = "D:/TakeNote/Video";

	for (const auto& file : directory_iterator(path)) {
		cout << file.path() << endl;
	}
	return 0;
}