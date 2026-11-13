#include <iostream>
#include "Person.h"
using namespace std;

void Person::inputInfo(string n, string t, int no) {
    name = n;
    tel = t;
    num = no;
}

void Person::outputInfo() {
    cout << "name: " << name << ", tel : " << tel << ", number: " << num << endl;
}

void test() {
    cout << "test function" << endl;
}