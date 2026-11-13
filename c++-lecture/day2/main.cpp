#include <iostream>
#include <cstring>

class Point {
private:
    int x, y;
    char * name;
public:
    Point() : x(0), y(0)     {
       std::cout << "Default Generator\n";
       name = new char[5];
       strcpy(name, "abc");
    }

    Point(int x, int y) : x(x), y(y) { 
       name = new char[5];
       strcpy(name, "kkk");
    }

    Point(Point & tmp) : x(tmp.x), y(tmp.y) {
       name = new char[5];
       strcpy(name, tmp.name);
    }

    ~Point() {
        // delete name;
    } // 보통 객체가 사용한 자원 반환

    void setX(int x) {
        this-> x = x;
    }
    int getX() const {
        return x;
    }

    void setY(int y) {
        this-> y = y;
    }
    int getY() const {
        return y;
    }

    void setName(const char * s) {
        strcpy(name, s);
    }

    void printXY() {
        std::cout << "x = " << x << ", y = " << y << ", name = " << name << std::endl;
    }

    Point getThis1() {
        return *this;
    }

    Point& getThis2() {
        return *this;
    }

    Point* getThis3() {
        return this;
    }
};

int main() {

    Point p1;

    Point * p2 = new Point(1, 3);

    p1.printXY();
    p2->printXY();

    Point arr[2];
    for(int i = 0; i < 2; i++) 
        arr[i].printXY();

    Point arr1[] = {{2, 4}, {5, 7}};
    for(int i = 0; i < 2; i++)
        arr1[i].printXY();

    Point * arr2[] = { new Point(7, 8), new Point(3, 5)};
    for(int i = 0; i < 2; i++)
        arr2[i]->printXY();

    Point p3 = p1;
    p3.printXY();

    p3.setName("vvv");
    p3.printXY();

    p3.getThis1().getX();
    Point tmp = p3.getThis1();
    
    std::cout << "address of object: " << &tmp << std::endl;
    std::cout << "address of object: " << &p3.getThis2() << std::endl;
    std::cout << "address of object: " << p3.getThis3() << std::endl;

    return 0;
}