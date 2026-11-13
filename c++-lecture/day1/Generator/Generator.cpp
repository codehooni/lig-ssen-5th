#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string name;
    int age;
public:
    Person(): name("amugae"), age(0) { }

    Person(string name, int age):name(name), age(age) { }

    void printInfo() {
        cout << name << " / " << age << endl;
    }
};

int main() {    

    Person p;
    Person p2("John", 3);

    p.printInfo();
    p2.printInfo();

    Person p3 = p;
    p3.printInfo();

    Person arr1[3];
    for(int i = 0; i < 3; i++) {
        arr1[i].printInfo();
    }

    Person arr2[3] = { {"Max", 3}, {"Lilly", 5}, {"Kan", 10} };
    for(int i = 0; i < 3; i++) {
        arr2[i].printInfo();
    }

    return 0;
}