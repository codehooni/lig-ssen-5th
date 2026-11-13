#pragma once

#include <iostream>
#include <string>
using namespace std;

class Poketmon {
private:
    string name;
    int level;
    int hp;
    int exp;
public:
    Poketmon(string name, int level, int hp, double exp);
    virtual ~Poketmon() { }  
    bool isDead() { return hp <= 0; }
    void eat();
    void sleep();
    void exercize();
    void play();
    void checkState();
    void checkLevel();
    virtual void skill() = 0;
};

class Pikachu : public Poketmon {
public:
    Pikachu(): Poketmon("Pikachu", 1, 100, 0) { }
    void skill() override;
};

class Squirtle : public Poketmon {
public:
    Squirtle(): Poketmon("Squirtle", 1, 100, 0) { }
    void skill() override;
};

class Bulbasaur : public Poketmon {
public:
    Bulbasaur(): Poketmon("Bulbasaur", 1, 100, 0) { }
    void skill() override;
};
