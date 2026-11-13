#include <iostream>
using namespace std;

class Point {
    int x, y;

public:
    Point(int x, int y): x(x), y(y) {}
    void print() {
        cout << "(" << x << ", " << y << ")\n";
    }
    Point& operator++() {
        x++; y++;
        return * this;
    }
    Point operator++(int) {
        Point old = *this;
        x++; y++;
        return old;
    }
    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    friend istream& operator>>(istream& in, Point& p);
    friend ostream& operator<<(ostream& out, const Point& p);
};

istream& operator>>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

ostream& operator<<(ostream& out, const Point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

int main() {

    Point p(1, 2);
    p.print();
    p++;
    p++.print();
    (++p).print();

    Point q(10, 20);
    p += q;
    cout << p << endl;

    return 0;
}