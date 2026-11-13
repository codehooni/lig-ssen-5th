#include <iostream>
#include <string>
using namespace std;

// 1번 문제

// Product 부모 클래스 생성

class Product {
public:
    string name;
    int price;
    int point;
    Product(string name, int price, int point) : name(name), price(price), point(point) {}
};

class TV : public Product {
public:
    TV(): Product("TV", 2000, 100) {}
};

class Audio : public Product {
public:
    Audio():Product("Audio", 1000,  50) {}
};

class Computer : public Product {
public:
    Computer(): Product("Computer", 5000, 200) {}
};

class Buyer {
public:
    int money = 10000;
    int point = 0;
     
    //물건사는 멤버 함수
    //오버로딩으로 구현
    void buy(TV p) {
	    money -= p.price;
	    point += p.point;
    }
    void buy(Audio p) { 
	    money -= p.price;
	    point += p.point;
    }
    void buy(Computer p) { 
        money -= p.price;
        point += p.point;
    }
};

int main(){
    Buyer b;

    TV tv1; Audio a1; Computer c1;
    b.buy(tv1); b.buy(a1); b.buy(c1);
    cout << "Money: " << b.money << endl;
    cout << "Point: " << b.point << endl;

    return 0;
}
