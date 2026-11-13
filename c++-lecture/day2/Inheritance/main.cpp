#include <iostream>
#include <string>
using namespace std;

class Parent {
public:
    Parent(string name, int age):name(name), age(age) {
        cout << "Parent Generator\n";
    }
    virtual ~Parent() {}
    virtual string toString() const {
        return "name: " + name + ", age: " + to_string(age);
    }
protected:
    string name;
    int age;
};

class Child : public Parent {
public:
    Child(string name, int age, string nickName): Parent(name, age), nickName(nickName) {
        cout << "Child Generator\n";
    }

    string toString() const override {
        return Parent::toString() + ", nickName: " + nickName;
    }
private: 
    string nickName;
};

int main() {
    
    Parent p("Bob", 2);
    cout << p.toString() << endl;

    Child c("Tom", 20, "tommy");
    cout << c.toString() << endl;

    return 0;
}