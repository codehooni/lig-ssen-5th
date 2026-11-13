#include <iostream>
#include <string>
using namespace std;

class Car {
public:
    virtual void horn() {
        cout << "bbb" << endl;
    }
};

class PoliceCar : public Car {
    void horn() override {
        cout << "ground" << endl;
    }
};

class Embulance : public Car {
    void horn() override {
        cout << "ground" << endl;
    }
};

int main() {

    Car * cars[] = {new Car(), new PoliceCar(), new Embulance() };

    for(int i = 0; i < 3; i++) {
        cars[0]->horn();
    }

    for(int i = 0; i < 3; i++) {
        delete cars[0];
    }

    return 0;
}