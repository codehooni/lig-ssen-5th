#include <iostream>
using namespace std;

class Singletone {
private:
    int x;
    Singletone(int a):x(a) { }
    static Singletone s;

public:
    void printX() {
        cout << "x = " << x << endl;
    }
    static Singletone getInstance() {
        return s;
    }
};

Singletone Singletone::s(10);

int main() {

    Singletone s = Singletone::getInstance();
    s.printX();

    return 0;
}