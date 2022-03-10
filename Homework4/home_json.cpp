#include <iostream>
#include "json.hpp"
#include <fstream>
#include <filesystem>

using nlohmann::json;

struct PersonInfo{
    int age;
    std::string name;
    bool sex; //1-male, 0-female
    double height; // в метрах(1.8)
};

std::istream& operator>>(std::istream& in, PersonInfo& p) {
    in >> p.age >> p.name >> p.sex >> p.height;
    return in;
};

std::ostream& operator<<(std::ostream& out, PersonInfo& p) {
    out << "Age:" << p.age << std::endl;
    out << "Name:" << p.name << std::endl;
    out << "Sex:" << p.sex << std::endl;
    out << "Height:" << p.height << std::endl;
    return out;
};

json fromPI(PersonInfo& p) {
    json obj;
    obj["age"] = p.age;
    obj["name"] = p.name;
    obj["sex"] = p.sex;
    obj["height"] = p.height;
    return obj;
};

void Save(std::filesystem::path path, std::string name, std::string to_save) {
    auto new_path = path / name;
    std::ofstream fs;
    fs.open(new_path);
    fs << to_save;
    fs.close();
};

int main()
{
    PersonInfo p1;
    PersonInfo p2;
    PersonInfo p3;
    PersonInfo p4;
    std::cin >> p1;
    std::cin >> p2;
    std::cin >> p3;
    std::cin >> p4;
    json obj1 = fromPI(p1);
    auto as_string1 = obj1.dump(4);
    json obj2 = fromPI(p2);
    auto as_string2 = obj2.dump(4);
    json obj3 = fromPI(p3);
    auto as_string3 = obj3.dump(4);
    json obj4 = fromPI(p4);
    auto as_string4 = obj4.dump(4);

    std::filesystem::path current_path(".");
    std::filesystem::create_directory("Objects");
    Save(current_path / "Objects", "p1.txt", as_string1);
    Save(current_path / "Objects", "p2.txt", as_string2);
    Save(current_path / "Objects", "p3.txt", as_string3);
    Save(current_path / "Objects", "p4.txt", as_string4);
}
