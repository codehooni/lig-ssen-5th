#pragma once
#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    int num;
    string name;
    string tel;

public:
    Person():num(0), name(""), tel("") {}
    Person(int num, string name, string tel):num(num), name(name), tel(tel) {}
    string toString() const;
    void setTel(string tel);
    int getNum();
};

class PersonArr {
private:
    Person * arr[10];
    int cnt;
public:
    PersonArr(): cnt(0), arr({NULL, }) {}
    // 소멸자, arr 방에 저장된 주소를 해제
    ~PersonArr();
    bool addPerson(Person * p);
    Person* getPerson(int idx);
    int getPersonIdx(int num);
    int getCnt();
    void delPerson(int idx);

};

class PersonService {
private:
    PersonArr arr;
public:
    void add();
    void get();
    void edit();
    void del();
    void printAll();
};