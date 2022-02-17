#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>
#include <array>
#include <list>
#include <deque>
#include <forward_list>

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




int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> v;
    std::list<int> l;
    std::deque<int> d;
    std::forward_list<int> fl;
    const int parametr = 10000;
    std::array<int, parametr> a;
    int rand;
    for (int i = 0; i < parametr; i++) {
        rand = gen();
        v.push_back(rand);
        d.push_back(rand);
        a[i] = rand;
    }
    
    for (int i = 0; i < parametr; i++) {
        l.push_front(v[parametr - 1 -i]);
        fl.push_front(v[parametr - 1 -i]);
    }
    
    {
        Timer<microseconds> t; 
        std::sort(a.begin(), a.end());
    }
    {
        Timer<microseconds> t;
        std::sort(v.begin(), v.end());
    }
    {
        Timer<microseconds> t;
        std::sort(d.begin(), d.end());
    }
    {
        Timer<microseconds> t;
        l.sort();
    }
    {
        Timer<microseconds> t;
        fl.sort();
    }
}
