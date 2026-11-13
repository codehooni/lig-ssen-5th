#include <iostream>
using namespace std;

class Test {
public:
    int x = 0;
    static int y;

    void printXY() {
        cout << "x: " << x << ", y: " << y << endl;
    }
    void f1();
    static void f2();
    void f3();
    static void f4();
};

void Test::f1() {
    x = 1;
    y = 2;
}

void Test::f2() {
    // x = 1;
    y = 2;
}

void Test::f3() {
    f1();
    f2();
}

void Test::f4() {
    // f1();
    f2();
}

// 스태택 멤버는 밖에서 한 번 초기화 해줘야한다.
int Test::y = 0;

int main() {

    Test::y = 100;
    cout << Test::y << endl;

    Test t1;

    t1.x++;
    t1.y++;
    t1.printXY();
 
    Test t2;

    t2.x++;
    t2.y++;
    t2.printXY();

    t2.f1();
    Test::f2();
    t2.printXY();

    t1.f3();
    t1.printXY();

    return 0;
}