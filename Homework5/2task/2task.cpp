#include <iostream>
#include <future>
#include <sstream>
#include <thread>
#include <numeric>
#include <algorithm>
#include <chrono>

using namespace std::chrono;

template <class T>

class Timer {
public:
    Timer() : start(steady_clock::now()), paused(false), time(0) {

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
            std::cout << duration_cast<T>(steady_clock::now() - start).count() + time << std::endl;
        }
    }
private:
    steady_clock::time_point start;
    int time;
    bool paused;
};

template<typename T>

std::ostream& operator<<(std::ostream& out, const std::vector<T>& container) {
    out << '[';
    std::copy(std::begin(container), std::prev(std::end(container)), std::ostream_iterator<T>(out, ", "));
    out << *(std::prev(std::end(container)));
    out << ']';
    return out;
}


template <typename Iterator, typename T>
void for_each_block(Iterator first, Iterator last, void f(T)) {
    std::for_each(first, last, f);
}

template <typename Iterator, typename T>
void for_each(void f(T), Iterator first, Iterator last, int num_workers) {
    auto length = std::distance(first, last);
    if (length < 32) {
        std::for_each(first, last, f);
    }
    auto length_per_future = (length)/ num_workers;
    std::vector<std::future<void>> futures;
    Iterator beginning;
    Iterator ending;
    for (auto i = 0; i < num_workers-1; i++) {
        beginning = std::next(first, i * length_per_future);
        ending = std::next(first, (i + 1) * length_per_future);
        futures.push_back(std::async(std::launch::async, for_each_block<Iterator, T>, beginning, ending, f));   
    }
    if (ending != last) {
        std::future<void> cur_future = std::async(std::launch::async, for_each_block<Iterator, T>, ending, last, f);
    }
}

void function(int& a) {
    a += 777;
}  



int main()
{
    std::vector<int> test_sequence(10000);
    std::iota(test_sequence.begin(), test_sequence.end(), 0);
    {
        Timer<microseconds> t;
        for_each(function, test_sequence.begin(), test_sequence.end(), 1);
    }
}
