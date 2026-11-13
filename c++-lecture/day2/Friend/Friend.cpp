#include <iostream>
using namespace std;

class Test;

class TestFriend2 {
public:
    void func1(Test& t);
    void func2(Test& t);
};

class Test {
private:
    int x = 10;
    friend void f1(Test& t);
    friend class TestFriend1;
    friend void TestFriend2::func1(Test& t);
};


void f1(Test& t) {
    cout << t.x << endl;
}

class TestFriend1 {
public:
    void func1(Test& t) {
        cout << t.x << endl;
    }  
    void func2(Test& t) {
        cout << t.x << endl;
    }
};

void TestFriend2::func1(Test& t) {
    cout << t.x << endl;
}

void TestFriend2::func2(Test& t) {
    // cout << t.x << endl;
}

int main() {
    Test t1;
    f1(t1);

    TestFriend1 a;
    a.func1(t1);
    a.func2(t1);

    TestFriend2 b;
    b.func1(t1);

    return 0;
}