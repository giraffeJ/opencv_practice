#include<time.h>
#include<chrono>
#include<ctime>
#include<iostream>

using namespace std;
typedef chrono::system_clock Clock;

int main() {
	auto now = Clock::now();
	time_t now_c = Clock::to_time_t(now);
	struct tm* parts = localtime(&now_c);

	cout << 1900 + parts->tm_year << endl;
	time_t now;
	now = time(NULL);
	cout << now << endl;
}

