#include <iostream> 
#include <vector>
#include <ostream>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <random>
#include <chrono>
#include <deque>



template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& container) {
    out << '[';
    std::copy(std::begin(container), std::prev(std::end(container)), std::ostream_iterator<T>(out, ", "));
    out << *(std::prev(std::end(container)));
    out << ']';
    return out;
}

auto IfSimlpeNumber = [](int elem) {
    bool flag = false;
    for (int i = 1; i <= elem; i++) {
        if (std::gcd(i, elem) == elem && elem != 1) {
            flag = true;
        }
    }
    return flag;
};

int main()
{   
    std::vector<int> P1(10);//First step
    std::iota(std::begin(P1), std::end(P1), 1);
    std::cout << P1 << std::endl;

    std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(P1));//Second step
    std::cout << P1 << std::endl;

    std::random_device rd;//Third step
    std::mt19937 gen(rd());
    std::shuffle(P1.begin(), P1.end(), gen);
    std::cout << P1 << std::endl;

    auto to_delete = std::unique(std::begin(P1), std::end(P1));//4 step
    P1.erase(to_delete, std::end(P1));
    std::cout << P1 << std::endl;

    int odd = std::count_if(std::begin(P1), std::end(P1), [](auto elem) {return (elem) % 2; }); //5 step
    std::cout << odd << std::endl;

    int max = *std::max_element(P1.begin(), P1.end());//6 step
    int min = *std::min_element(P1.begin(), P1.end());
    std::cout << "MAX:" << max << "," << "MIN:" << min << std::endl;

    int simple;                                                                         //8 step
    if (std::find_if(std::begin(P1), std::end(P1), IfSimlpeNumber) != std::end(P1)) {
        int simple = *std::find_if(std::begin(P1), std::end(P1), IfSimlpeNumber);
        std::cout << simple << std::endl;
    }
    else {
        std::cout << "There aren't simple numbers" << std::endl;
    }

    std::transform(std::begin(P1), std::end(P1), std::begin(P1), [](auto elem) {return elem * elem; }); //9 step
    std::cout << P1 << std::endl;

    std::vector<int> P2;                                                //10 step
    auto distribution = std::uniform_int_distribution(-100, 100);
    std::generate_n(std::back_inserter(P2), P1.size(), [&gen, &distribution]() {return distribution(gen); });
    std::cout << P2 << std::endl;

    std::transform(std::begin(P2), std::next(std::begin(P2), 5), std::begin(P2), [](auto elem) {return 1; }); //11 step
    std::cout << P2 << std::endl;

    std::vector<int> P3;
    std::transform(std::begin(P1), std::end(P1), std::begin(P2), std::back_inserter(P3), [](auto lhs, auto rhs) {return lhs - rhs; }); //12 step
    std::cout << P3 << std::endl;

    std::transform(std::begin(P3), std::end(P3), std::begin(P3), [](auto elem) {if (elem < 0) { return 0; } else { return elem; }}); //13 step
    std::cout << P3 << std::endl;

    std::sort(std::begin(P3), std::end(P3));                                //14 step
    auto find_zeros = std::find_if(std::begin(P3), std::end(P3), [](auto elem) {return elem != 0; });
    P3.erase(std::begin(P3), find_zeros);
    std::cout << P3 << std::endl;

    std::reverse(std::begin(P3), std::end(P3)); //15 step
    std::cout << P3 << std::endl;

    std::vector<int>::iterator it = std::begin(P3); //16 step (P3 is already sorted)
    while (it != std::end(P3) && it - std::begin(P3) < 3) {
        std::cout << *it << " ";
        it++;
    }
    std::cout << std::endl;

    std::sort(std::begin(P1), std::end(P1)); //17 step
    std::sort(std::begin(P2), std::end(P2));
    std::cout << P1 << std::endl << P2 << std::endl;

    std::vector<int> P4;                //18 step
    std::merge(std::begin(P1), std::end(P1), std::begin(P2), std::end(P2), std::back_inserter(P4));
    std::cout << P4 << std::endl;

    auto diapason = std::equal_range(std::begin(P4), std::end(P4), 1);

    std::cout << P1 << std::endl;  //20 step
    std::cout << P2 << std::endl;
    std::cout << P3 << std::endl;
    std::cout << P4 << std::endl;
}
