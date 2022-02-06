#include <iostream>
#include <map>
#include <string>
#include <chrono>


using namespace std::chrono;

template <class T>

class Timer {
public:
	Timer() : start(steady_clock::now()), paused(false), time(0){

	}
	void Pause() {
		if (!paused) {
			time += duration_cast<T>(steady_clock::now() - start).count();
			paused = true;
		}
		else {
			start = steady_clock::now();
			paused = false;
		}
	}
	~Timer() {
		if (paused) {
			std::cout << time << std::endl;
		}
		else {
			std::cout << duration_cast<T>(steady_clock::now() - start).count() + time<< std::endl;
		}
	}
private:
	steady_clock::time_point start;
	int time;
	bool paused;
};

int main() {

	double result = 0.;
	{
		Timer<milliseconds> t;
		for (auto i = 0; i < 3000000; i++) {
			result += std::sin(i) + std::cos(i);
		}
		t.Pause();
		for (auto i = 0; i < 3000000; i++) {
			result += std::sin(i) + std::cos(i);
		}
		t.Pause();
		for (auto i = 0; i < 3000000; i++) {
			result += std::sin(i) + std::cos(i);
		}
	}
	std::cout << result << std::endl;
}
