#include <iostream>
#include <string>
using namespace std;

// 2번 문제
// 제품들을 상속으로 변경
// Buyer.buy()를 하나로 통합하여 구현

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

    void buy(const Product& p) {
        if(p.price > money) {
            cout << "Please check your balance." << endl;
            return;
        }
	    money -= p.price;
	    point += p.point;
    }
};

int main(){
    Buyer b;
    TV tv1;
    Computer c1;
    b.buy(tv1);
    b.buy(c1);
    b.buy(c1);

    cout << "Money: " << b.money << endl;
    cout << "Point: " << b.point << endl;
    return 0;
}
