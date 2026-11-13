#include <iostream>
#include <string>
using namespace std;

class MyList {
public:
    virtual void add(string str) = 0;
    virtual string get(int idx) = 0;
};

class MyVector: public MyList {
public:
    void add(string str) override {

    }
    string get(int idx) override {
        
    }
};

class MyArrayList: public MyList {
public:
    void add(string str) override {

    }
    string get(int idx) override {
        
    }
};

int main() {

    MyList * v = new MyVector();
    MyList * al = new MyArrayList();

    return 0;
}