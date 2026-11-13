#include <iostream>
using namespace std;

class Point {
private:
    int x;
    int y;
public:
    Point() {}
    Point(int x, int y): x(x), y(y) {}
    void print() {
        cout << "x: " << x << ", y = " << y << endl;
    }
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    friend Point& operator++(Point& p);
    friend Point operator++(Point& p, int);
};

Point& operator++(Point& p) {
    p.x++; p.y++;
    return p;
}

Point operator++(Point& p, int) {
    Point old = p;
    p.x++; p.y++;
    return old;
}

int main() {

    Point p1(1, 2), p2(3, 4);

    Point p3(p1 + p2);
    p3.print();

    cout << ( p3 == p1) << endl;;

    ++p3;
    p3++;

    return 0;
}