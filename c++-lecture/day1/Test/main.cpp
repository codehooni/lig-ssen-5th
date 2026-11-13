#include <iostream>
using namespace std;

class Parent {
private:
    int a;
public:
    int b;
    void setA(int x) {
        a = x;
    }
    int getB() const { // const: 멤버변수 수정 불가
        return a;
    }
protected:
    int c;
};

class Child : Parent {
public:
    void print() {
        c = 30;
        cout << "in Child class c: " << c << endl;
    }
};

int main() {

    Parent p;
    // t.a = 10;
    p.setA(10);
    p.b = 20;
    // t.c = 30;

    cout << p.getB() << endl;
    cout << p.b << endl;

    Child c;
    
    c.print();

    return 0;
}