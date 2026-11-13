#include "Poketmon.h"

Poketmon::Poketmon(string name, int level, int hp, double exp): name(name), level(level), hp(hp), exp(exp) { }
void Poketmon::eat() { hp += 10; }
void Poketmon::sleep() { hp += 30; }
void Poketmon::exercize() { 
    hp -= 10;
    exp += 20;
    if(hp <= 0) cout << name << "is Died\n";
    else if(exp > 100) {
        level++;
        cout << name << " level up~!\n";
        exp = 0;
    }
}
void Poketmon::play() { 
    hp -= 5;
    exp += 10;
    if(hp <= 0) cout << name << "is Died\n";
    else if(exp > 100) {
        level++;
        cout << name << " level up~!\n";
        exp = 0;
    }
}
void Poketmon::checkState() {
    cout << name << "'s state:\n";
    cout << "hp: " << hp << endl;
    cout << "level:" << level << endl;
    cout << "exp: " << exp << endl;
} 
void Poketmon::checkLevel() {
    cout << name << "'s level: " << level << endl;
}

void Pikachu::skill() {
    cout << "millionVolts" << endl;
}

void Squirtle::skill() {
    cout << "waterCannon" << endl;
}

void Bulbasaur::skill() {
    cout << "razorReaf" << endl;
}