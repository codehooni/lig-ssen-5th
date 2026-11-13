#include <iostream>
using namespace std;

class Parent {
private:
    int x, y;
public:
    Parent(int x, int y): x(x), y(y) { }
    void print() {
        cout << "x  = " << x << ", y = " << y << endl;
    }
};

class Child : public Parent {
private:
    int z;
public:
    Child(int x, int y, int z): Parent(x, y), z(z) { }
    void print() {
        Parent::print();
        cout << ", z = " << z << endl;
    }
};

int main() {

    Parent p(1, 2);

    p.print();

    Child c(3, 4, 5);

    c.print();

    return 0;
}