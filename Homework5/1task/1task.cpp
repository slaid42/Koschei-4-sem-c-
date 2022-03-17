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
void accumulate_block(Iterator first, Iterator last, T init, T& result) {
    result = std::accumulate(first, last, init);
}

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init, int num_workers) {
    auto length = std::distance(first, last);
    if (length < 32) {
        return std::accumulate(first, last, init);
    }
    auto length_per_thread = (length) / num_workers;
    std::vector<std::thread> threads;
    Iterator beginning;
    Iterator ending;
    std::vector<T> results(num_workers);
    for (auto i = 0u; i < num_workers - 1; i++) {
        beginning = std::next(first, i * length_per_thread);
        ending = std::next(first, (i + 1) * length_per_thread);
        threads.push_back(std::thread(accumulate_block<Iterator, T>, beginning, ending, 0, std::ref(results[i])));
    }
    auto main_result = std::accumulate(std::next(first, (num_workers - 1) * length_per_thread), last, init);
    std::for_each(std::begin(threads), std::end(threads), std::mem_fn(&std::thread::join));//не на msvc: mem_fun_ref
    return std::accumulate(std::begin(results), std::end(results), main_result);
}

int main()
{
    std::vector<int> test_sequence(10000);
    std::iota(test_sequence.begin(), test_sequence.end(), 0);
    {
        Timer<microseconds> t;
        int result = parallel_accumulate(test_sequence.begin(), test_sequence.end(), 0, 1);
    }
    {
        Timer<microseconds> t;
        int result = parallel_accumulate(test_sequence.begin(), test_sequence.end(), 0, 2);
    }
    {
        Timer<microseconds> t;
        int result = parallel_accumulate(test_sequence.begin(), test_sequence.end(), 0, 3);
    }
    {
        Timer<microseconds> t;
        int result = parallel_accumulate(test_sequence.begin(), test_sequence.end(), 0, 4);
    }
    {
        Timer<microseconds> t;
        int result = parallel_accumulate(test_sequence.begin(), test_sequence.end(), 0, 5);
    }
    {
        Timer<microseconds> t;
        int result = parallel_accumulate(test_sequence.begin(), test_sequence.end(), 0, 6);
    }
    {
        Timer<microseconds> t;
        int result = parallel_accumulate(test_sequence.begin(), test_sequence.end(), 0, 7);
    }
    {
        Timer<microseconds> t;
        int result = parallel_accumulate(test_sequence.begin(), test_sequence.end(), 0, 8);
    }
}
