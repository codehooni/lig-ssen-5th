# C++ Day2 — 복사 생성자, this, static, friend, 상속

> 2026-11-11 학습 정리

## 복사 생성자와 this 반환
코드: [main.cpp](main.cpp)

```cpp
class Point {
private:
    int x, y;
    char * name;
public:
    Point() : x(0), y(0) {
       std::cout << "Default Generator\n";
       name = new char[5];
       strcpy(name, "abc");
    }

    Point(int x, int y) : x(x), y(y) {
       name = new char[5];
       strcpy(name, "kkk");
    }

    Point(Point & tmp) : x(tmp.x), y(tmp.y) {   // 복사 생성자
       name = new char[5];
       strcpy(name, tmp.name);
    }

    ~Point() {
        // delete name;
    }

    Point getThis1()  { return *this; }   // 복사본 반환
    Point& getThis2() { return *this; }   // 자기 자신(참조) 반환
    Point* getThis3() { return this; }    // 자기 주소 반환
};

Point p3 = p1;          // 복사 생성자 호출
p3.setName("vvv");      // p1의 name은 그대로
```
```
x = 0, y = 0, name = abc     ← p3 = p1 직후
x = 0, y = 0, name = vvv     ← p3.setName("vvv") 후
address of object: 0x...bb0  ← getThis1()로 받은 복사본 tmp
address of object: 0x...bc0  ← getThis2()
address of object: 0x...bc0  ← getThis3()
```
- **복사 생성자**는 같은 타입 객체로 새 객체를 만들 때(`Point p3 = p1;`, 값으로 넘기기·반환하기) 호출된다.
- 컴파일러가 만들어 주는 기본 복사 생성자는 멤버를 그대로 복사한다(얕은 복사). `name` 같은 포인터는 주소만 복사돼서 두 객체가 같은 문자열을 공유한다.
- 그래서 직접 만든 복사 생성자에서 `name`을 새로 할당하고 내용을 복사했다(**깊은 복사**). `p3`의 이름을 바꿔도 `p1`은 그대로다.
- `this`는 지금 객체의 주소다. `*this`를 값으로 반환하면 복사본이, 참조(`Point&`)로 반환하면 자기 자신이 나간다. 주소 출력 결과로 확인할 수 있다.
- ⚠️ 소멸자의 `delete`가 주석이라 `name`이 해제되지 않는다. `new char[]`로 만들었으니 `delete[] name;`이어야 한다.
- ⚠️ 복사 생성자의 매개변수는 `const Point&`로 쓴다. `const`가 없으면 임시 객체나 `const` 객체로 복사할 수 없다.
- ⚠️ `name`을 5칸만 할당해서 `setName`에 4글자보다 긴 문자열을 넣으면 넘친다.

## 객체를 포함하는 클래스 — 성적
코드: [Score/Score.cpp](Score/Score.cpp)

```cpp
class Score {
    int kor, eng, mat, total;
public:
    void setKor(int kor) {
        total -= this->kor;
        this->kor = kor;
        total += this->kor;
    }
    /* ... */
};

class Student {
    int num;
    string name;
    Score * score;
public:
    Student(int num, string name, Score * score): num(num), name(name), score(score) { }
    ~Student() { delete score; }
};
```
```
num: 1, name: Kim, kor: 90, eng: 80, mat: 70, total: 240
num: 2, name: Lee, kor: 85, eng: 95, mat: 75, total: 255
num: 3, name: Park, kor: 70, eng: 60, mat: 100, total: 230
```
- setter에서 `total`을 함께 고쳐서 합계가 항상 맞게 유지된다. 멤버를 `private`로 두는 이유다.
- `Student`가 `Score`를 가지는 포함(has-a) 관계다. `Student`가 사라질 때 소멸자에서 `score`도 해제한다.
- ⚠️ `Student`를 복사하면 `score` 주소만 복사되고, 두 객체의 소멸자가 같은 주소를 두 번 `delete`한다. 코드 주석대로 깊은 복사를 하는 복사 생성자를 추가해야 한다.

## static 멤버
코드: [Static/main.cpp](Static/main.cpp), [Product/Product.cpp](Product/Product.cpp)

```cpp
class Test {
public:
    int x = 0;
    static int y;          // 모든 객체가 공유

    void f1();             // 일반 멤버 함수: x, y 모두 사용
    static void f2();      // static 멤버 함수: y만 사용
};

int Test::y = 0;           // static 멤버는 클래스 밖에서 한 번 정의

Test::y = 100;
Test t1; t1.x++; t1.y++;   // x: 1, y: 101
Test t2; t2.x++; t2.y++;   // x: 1, y: 102
```
```
100
x: 1, y: 101
x: 1, y: 102
x: 1, y: 2
x: 1, y: 2
```
- `static` 멤버 변수는 객체마다 있는 것이 아니라 클래스에 하나만 있다. `t1.y`와 `t2.y`는 같은 변수라서 계속 늘어난다.
- 객체 없이 `Test::y`, `Test::f2()`로 쓸 수 있다.
- `static` 멤버 함수에는 `this`가 없다. 그래서 일반 멤버 `x`나 일반 함수 `f1()`을 쓸 수 없다. 반대로 일반 함수는 `static` 멤버를 쓸 수 있다.

```cpp
class Product {
    static int cnt;
    int num;
public:
    Product(string name, int price): num(cnt++), name(name), price(price) {}
    ~Product() { cnt--; }
};
```
```
num: 0, name: Toy, price: 30
num: 1, name: M-SAM Block-II, price: 10000
num: 1, name: Raybolt , price: 20003
```
- `static` 카운터로 객체마다 번호를 붙인다.
- 소멸자에서 `cnt--`를 하니 `p2`를 지운 뒤 만든 `p3`가 다시 1번을 받는다. "지금 살아 있는 개수"와 "다음 번호"를 같은 변수로 쓰면 번호가 겹친다. 둘을 나누어야 한다.
- `p1`, `p3`를 `delete`하지 않았다.

## 싱글톤
코드: [Singletone/Singletone.cpp](Singletone/Singletone.cpp)

```cpp
class Singletone {
private:
    int x;
    Singletone(int a):x(a) { }      // 생성자를 private로
    static Singletone s;            // 유일한 객체
public:
    static Singletone getInstance() {
        return s;
    }
};

Singletone Singletone::s(10);

Singletone s = Singletone::getInstance();
s.printX();                         // x = 10
```
- 생성자를 `private`로 막아 밖에서 객체를 만들 수 없게 하고, 클래스 안에 `static` 객체 하나만 둔다.
- 설정, 로그처럼 프로그램에 하나만 있어야 하는 객체에 쓰는 패턴이다.
- ⚠️ `getInstance()`가 값으로 반환해서 호출할 때마다 **복사본**이 생긴다. 하나만 두려면 `static Singletone& getInstance()`로 참조를 반환한다.

## friend
코드: [Friend/Friend.cpp](Friend/Friend.cpp)

```cpp
class Test {
private:
    int x = 10;
    friend void f1(Test& t);                     // 함수 하나
    friend class TestFriend1;                    // 클래스 전체
    friend void TestFriend2::func1(Test& t);     // 다른 클래스의 멤버 함수 하나
};
```
```
10
10
10
10
```
- `friend`로 지정한 함수나 클래스는 `private` 멤버에 접근할 수 있다.
- `TestFriend2`는 `func1`만 friend라서 `func2`에서는 `t.x`를 쓸 수 없다(주석 처리됨).
- 캡슐화를 깨므로 꼭 필요할 때만 쓴다. Day3~4의 연산자 오버로딩(`operator<<`)에서 주로 쓴다.
- 멤버 함수를 friend로 지정하려면 그 클래스(`TestFriend2`)가 먼저 정의돼 있어야 한다. 그래서 `class Test;` 전방 선언 후 `TestFriend2`를 먼저 썼다.

## 상속과 가상 함수
코드: [Inheritance/main.cpp](Inheritance/main.cpp)

```cpp
class Parent {
public:
    Parent(string name, int age):name(name), age(age) {
        cout << "Parent Generator\n";
    }
    virtual ~Parent() {}
    virtual string toString() const {
        return "name: " + name + ", age: " + to_string(age);
    }
protected:
    string name;
    int age;
};

class Child : public Parent {
public:
    Child(string name, int age, string nickName): Parent(name, age), nickName(nickName) {
        cout << "Child Generator\n";
    }
    string toString() const override {
        return Parent::toString() + ", nickName: " + nickName;
    }
private:
    string nickName;
};
```
```
Parent Generator
name: Bob, age: 2
Parent Generator
Child Generator
name: Tom, age: 20, nickName: tommy
```
- 자식 객체를 만들면 **부모 생성자가 먼저**, 자식 생성자가 나중에 호출된다. 소멸은 반대 순서다.
- 부모 생성자에 인자를 넘기려면 초기화 리스트에 `Parent(name, age)`를 쓴다.
- `override`는 부모의 가상 함수를 재정의한다는 표시다. 이름이나 매개변수가 틀리면 컴파일 오류로 알려 준다.
- `Parent::toString()`으로 부모 버전을 불러 재사용하고 내용만 덧붙였다.
- 부모 소멸자를 `virtual`로 해야 부모 포인터로 자식 객체를 `delete`할 때 자식 소멸자까지 호출된다.

## 과제: 학사 관리
코드: [homework/](homework/), 요구사항: [requirement.md](homework/requirement.md)

```cpp
class Profile {                    // 공통: 번호, 이름, 학과, 내 정보 확인
protected:
    int no; string name; string department;
    Profile(int no, string name, string department);
public:
    void viewProfile();
};

class Student   : public Profile { vector<string> courses; /* 수강신청, 수강취소, 수강목록 */ };
class Professor : public Profile { vector<string> courses; /* 강의 오픈, 오픈 취소, 오픈 목록 */ };
class Faculty   : public Profile { string position;        /* 신입사원 관리 */ };
```
```cpp
void Student::courseDrop(string course) {
    auto it = find(courses.begin(), courses.end(), course);
    if(it != courses.end()) {
        courses.erase(it);
    }
}
```
```
Course List: [Data Structure, Algorithm, Architecture of Computer, C language, ]
Course List: [Data Structure, Architecture of Computer, C language, ]
no: 100, name: Khan, department: Software
```
- 학생, 교수, 교직원의 **공통점(번호, 이름, 학과)을 부모 클래스로** 뽑고, 다른 점만 자식에 둔다.
- `Profile` 생성자를 `protected`로 둬서 `Profile` 자체는 만들 수 없고 자식만 만들 수 있다.
- 과목 목록은 크기가 변하므로 `vector<string>`을 쓴다. `push_back`으로 추가하고, `find`로 찾아 `erase`로 지운다.
- ⚠️ `Faculty` 생성자 매개변수가 `positioin`(오타)이라 `position(position)`이 멤버를 자기 자신으로 초기화한다. 실행하면 `std::bad_alloc`으로 프로그램이 죽는다. 매개변수 이름을 `position`으로 고쳐야 한다.
