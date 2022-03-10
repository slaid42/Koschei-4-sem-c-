#include <regex>
#include <iostream>
#include <iterator>
#include <vector>

std::vector<std::string> search(const std::regex& pattern, const std::regex& pattern1, const std::string& text) {
    auto begin = std::sregex_iterator(std::begin(text),
        std::end(text), pattern);
    auto end = std::sregex_iterator();
    std::vector<std::string> results(std::distance(begin, end));
    std::transform(begin, end, std::back_inserter(results), [](auto x) {
        return x.str();
        });
    auto begin1 = std::sregex_iterator(std::begin(text), std::end(text), pattern1);
    auto end1 = std::sregex_iterator();
    std::vector<std::string> results1(std::distance(begin1, end1));
    std::transform(begin1, end1, std::back_inserter(results1), [](auto x) {
        return x.str();
    });
    std::copy(results1.begin(), results1.end(), std::back_inserter(results));
    return results;
}


int main()
{
    std::regex data_pattern(R"((\s(0?[0-9])|([12][0-9])|(3[01]))\.((0?[0-9])|(1[12]))\.-?[0-9][0-9]?[0-9]?[0-9])");
    std::regex time_pattern(R"((\s(0?[0-9])|([1][0-9])|(2[0123]))\:((0?[0-9])|([1-5][0-9]))\:((0?[0-9])|([1-5][0-9]))\s)");
    std::string test_sequence = " +79528888888 \n"
        " 13.8.2003\n"
        " 22.01.988 \n"
        " 31.08.666\n"
        " 0:59:42 \n"
        " 12:21:12 \n"
        " 12.2.3213 \n"
        " sadjaskfjpo 13.232,321 dksojf 12:12:12 sdgkjsdgp 31.2.2144\n";
    auto result = search(data_pattern, time_pattern, test_sequence);
    std::copy(std::begin(result), std::end(result), std::ostream_iterator<std::string>(std::cout, " "));
}
