#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    static int cnt;

    int num;
    string name;
    int price;
public:
    Product(string name, int price): num(cnt++), name(name), price(price) {}
    ~Product() { cnt--; }
    void printInfo() {
        cout << "num: " << num << ", name: " << name << ", price: " << price << endl;
    }
};
int Product::cnt = 0;

int main() {
    Product *p1 = new Product("Toy", 30);
    Product *p2 = new Product("M-SAM Block-II", 10000);
    // Product *p3 = new Product("Raybolt ", 20003);

    p1->printInfo();
    p2->printInfo();
    delete p2;

    Product *p3 = new Product("Raybolt ", 20003);
    p3->printInfo();

    

    return 0;
}