#include <iostream>
using namespace std;

int main() {

    int a = 1, b = 0;

    try {
        cout << a / b << endl;
        cout << "Program End" << endl;
    } catch (int e) {
        cout << e << endl;
    }
    
    return 0;
}