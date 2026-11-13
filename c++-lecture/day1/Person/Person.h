#pragma once
#include <string>

class Person {
public:
    std::string name;
    std::string tel;
    int num;
    void inputInfo(std::string n, std::string t, int no);
    void outputInfo();
};

void test();