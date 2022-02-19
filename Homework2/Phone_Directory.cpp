#include <map>
#include <iostream>
#include <iterator>
#include <random>
#include <algorithm>


class PhoneDirectory {
private:
    std::map<std::string, int> m;
public:
    PhoneDirectory() = default;
    PhoneDirectory(std::string name, int number){
        m.insert(std::make_pair(name, number));
    }
    void AddNumber(std::string name, int number) {
        m.insert(std::make_pair(name, number));
    }
    void FindNumber(std::string name) {
        if (m.find(name) == std::end(m)) {
            std::cout << "There are nobody with this name" << std::endl;
        }else {
            std::cout << name << ":" << m.find(name)->second << std::endl;
        }
    }
    void GetAllSortedNumbers() {
        for (const auto& [name, number] : m) {
            std::cout << name << ":" << number << std::endl;
        }
    }
    void GetRandomNumber() {
        std::random_device rd;   
        std::mt19937 gen(rd());
        int random = gen() % (m.size());
        std::cout << random << std::endl;
        std::map<std::string, int>::iterator it = m.begin();
        std::advance(it, random);
        std::cout << it->first << ":" << it->second << std::endl;
    }
};







int main()
{
    PhoneDirectory p;
    p.AddNumber("Slavik", 5429292);
    p.AddNumber("Sasha", 2929292);
    p.AddNumber("Misha", 12329292);
    p.AddNumber("Petya", 52);
    
    p.FindNumber("Lesha");
    p.FindNumber("Slavik");
    
    p.GetRandomNumber();
    
    p.GetAllSortedNumbers();

}
