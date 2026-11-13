#include <iostream>

using namespace std;

class Test {
public:
    int a;
    int b;

    void printData() {
        cout << a << ", " << b << endl;
    }
};

#if 0
int main() {

    Test t1;

    t1.a = 10;
    t1.b = 20;
    t1.printData();

    Test * t2 = new Test;

    t2->a = 100;
    t2->b = 200;
    t2->printData();

    delete t2;

    t2->a = 100;
    t2->b = 200;
    t2->printData();

    return 0;
}
#endif