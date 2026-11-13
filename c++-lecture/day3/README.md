# C++ Day3 — 객체 사이의 관계, 다형성, 추상 클래스, 연산자 오버로딩

> 2026-11-12 학습 정리

## 수업 메모
프로그램을 만들 때
1. 기능 정의
2. 기능 명세화 — 객체를 구상 가능
3. UML

객체 사이의 관계
- 포함 관계: has a — 소유
- 상속 관계: is a — 본질 자체

```cpp
// 그림판 앱: 원 그리기, 삼각형 그리기..
class Point {
    int x, y;
};

class Circle {       // Circle has a Point
    Point p;
    double r;
};

class Triangle {     // Triangle has 3 Points
    Point p1, p2, p3;
};
```

상속
- 공통점을 뽑아서 부모 클래스로 정의
- 업캐스팅: 상속 관계의 객체를 부모 타입으로 저장. 포인터(또는 참조)로만 가능

부모 클래스의 `print()`를 `virtual`(가상 함수)로 변경함
- 가상 함수는 동적 바인딩
- vptr: 가상 함수 테이블(vtable)의 주소를 갖는 숨은 멤버

추상 클래스: 순수 가상 함수를 하나 이상 포함한 클래스
- 완성된 클래스가 아니기 때문에 객체를 만들 수 없다.
- 객체를 만들고 싶으면 파생 클래스를 만들어서 모든 순수 가상 함수 구현 → Dog, Cat으로 객체 생성

## 함수 재정의(오버라이딩)
코드: [main.cpp](main.cpp)

```cpp
class Parent {
    int x, y;
public:
    Parent(int x, int y): x(x), y(y) { }
    void print() {
        cout << "x  = " << x << ", y = " << y << endl;
    }
};

class Child : public Parent {
    int z;
public:
    Child(int x, int y, int z): Parent(x, y), z(z) { }
    void print() {
        Parent::print();
        cout << ", z = " << z << endl;
    }
};
```
```
x  = 1, y = 2
x  = 3, y = 4
, z = 5
```
- 자식이 부모와 같은 이름의 함수를 만들면 자식 것이 부모 것을 가린다. 부모 것은 `Parent::print()`로 부른다.
- 부모의 `x`, `y`는 `private`라서 자식이 직접 못 쓴다. 그래서 부모 생성자와 부모 `print()`에 맡겼다.
- 부모 `print()`가 `endl`로 줄을 바꿔서 `z`가 다음 줄에 나온다.
- 이 `print()`는 `virtual`이 아니다. `Parent* p = &c; p->print();`는 **부모 것**을 호출한다(정적 바인딩).

## 가상 함수와 업캐스팅
코드: [Car/main.cpp](Car/main.cpp)

```cpp
class Car {
public:
    virtual void horn() { cout << "bbb" << endl; }
};

class PoliceCar : public Car {
    void horn() override { cout << "ground" << endl; }
};

class Embulance : public Car {
    void horn() override { cout << "ground" << endl; }
};

Car * cars[] = {new Car(), new PoliceCar(), new Embulance() };

for(int i = 0; i < 3; i++) {
    cars[0]->horn();
}
```
```
bbb
bbb
bbb
```
- 자식 객체를 부모 포인터 배열 하나에 담았다(**업캐스팅**). 종류가 다른 차를 한 번에 다룰 수 있다.
- `horn()`이 `virtual`이라 포인터 타입(`Car*`)이 아니라 **실제 객체 타입**의 함수가 호출된다(동적 바인딩).
- ⚠️ 반복문이 `cars[i]`가 아니라 `cars[0]`만 써서 `bbb`만 세 번 나온다. `cars[i]`로 고치면 `bbb ground ground`가 나온다.
- ⚠️ `delete cars[0]`도 3번 실행돼서 같은 객체를 세 번 해제한다(실행하면 비정상 종료). 또 `Car`에 `virtual ~Car() {}`가 있어야 부모 포인터로 자식을 안전하게 지운다.

## 추상 클래스와 인터페이스
코드: [List/main.cpp](List/main.cpp), [MultipleInheritance/main.cpp](MultipleInheritance/main.cpp)

```cpp
class Dao {  // DAO(database access object): DB 처리 전담 클래스. 인터페이스
public:
    virtual void insert() = 0;
    virtual void select() = 0;
    virtual void update() = 0;
    virtual void del() = 0;
};

class DaoOracleImpl : public Dao { /* Oracle 버전 구현 */ };
class DaoMySQLImpl  : public Dao { /* MySQL 버전 구현 */ };

class Service {
    Dao* dao;
public:
    Service(Dao* dao): dao(dao) {}
    ~Service() { delete dao; }
    void add() { dao->insert(); }
    void get() { dao->select(); }
    /* ... */
};

Service s(new DaoMySQLImpl());
s.add();
s.get();
```
```
MySQL insert
MySQL select
MySQL update
MySQL delete
```
- `= 0`인 함수가 **순수 가상 함수**다. 하나라도 있으면 추상 클래스라서 `new Dao()`는 안 된다.
- 순수 가상 함수만 있는 클래스는 "이 기능들을 반드시 제공하라"는 약속(인터페이스) 역할을 한다.
- `Service`는 `Dao*`만 알고 Oracle인지 MySQL인지 모른다. `new DaoOracleImpl()`로 바꿔 넣기만 하면 DB가 바뀐다. Day7(C)의 함수 포인터로 비교 함수를 갈아 끼우던 것과 같은 생각이다.
- `MyList`/`MyVector`도 같은 구조다. 다만 `get()` 본문에 `return`이 없어 아직 미완성이다.
- ⚠️ `Dao`에도 `virtual ~Dao() {}`를 넣어야 `delete dao`가 자식 소멸자를 호출한다.

## 포켓몬 키우기
코드: [Poketmon/](Poketmon/)

```cpp
class Poketmon {
    string name;
    int level, hp, exp;
public:
    virtual ~Poketmon() { }
    bool isDead() { return hp <= 0; }
    void eat();  void sleep();  void exercize();  void play();
    void checkState();
    virtual void skill() = 0;          // 포켓몬마다 다름
};

class Pikachu : public Poketmon {
public:
    Pikachu(): Poketmon("Pikachu", 1, 100, 0) { }
    void skill() override;             // millionVolts
};
/* Squirtle(waterCannon), Bulbasaur(razorReaf)도 같은 구조 */

Poketmon* p = nullptr;
switch(select) {
    case 1: p = new Pikachu();   break;
    case 2: p = new Squirtle();  break;
    case 3: p = new Bulbasaur(); break;
}
```
```
입력: 1(Pikachu) → 6(skill) → 4(exercise) → 5(state) → 7
millionVolts
Pikachu's state:
hp: 90
level:1
exp: 20
```
- 공통 기능(먹기, 자기, 운동...)은 부모에, 포켓몬마다 다른 `skill()`만 순수 가상 함수로 두고 자식이 구현한다.
- 선택에 따라 다른 자식 객체를 만들지만, 이후 코드는 `Poketmon*` 하나로 모두 처리한다.
- `skill()`이 가상 함수라서 `p->skill()`만 써도 실제 포켓몬의 스킬이 나온다. 코드의 `typeid`로 타입을 확인하고 캐스팅하는 부분은 없어도 된다.
- 생성자의 `exp` 매개변수가 `double`인데 멤버는 `int`다. 타입을 맞춘다.

## 과제: 구매자와 상품
코드: [homework1/main.cpp](homework1/main.cpp), [homework2/main.cpp](homework2/main.cpp)

```cpp
// 1번: 상품마다 buy()를 오버로딩
void buy(TV p)       { money -= p.price; point += p.point; }
void buy(Audio p)    { money -= p.price; point += p.point; }
void buy(Computer p) { money -= p.price; point += p.point; }
```
```cpp
// 2번: 부모 타입 하나로 통합
void buy(const Product& p) {
    if(p.price > money) {
        cout << "Please check your balance." << endl;
        return;
    }
    money -= p.price;
    point += p.point;
}
```
```
1번: Money: 2000  Point: 350     (TV, Audio, Computer 구매)
2번: Please check your balance.
     Money: 3000  Point: 300     (TV, Computer 구매 후 두 번째 Computer는 잔액 부족)
```
- 1번은 상품이 늘어날 때마다 `buy`를 하나씩 더 만들어야 한다.
- 2번은 모든 상품이 `Product`를 상속하므로 `const Product&` 하나로 받는다. 자식 객체를 부모 참조로 받는 업캐스팅이다.
- 참조로 받아서 객체를 복사하지 않고, `const`로 상품을 바꾸지 않는다고 밝혔다.

## 연산자 오버로딩
코드: [OperatorOverloading/main.cpp](OperatorOverloading/main.cpp)

```cpp
class Point {
    int x, y;
public:
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    friend Point& operator++(Point& p);         // 전위 ++p
    friend Point operator++(Point& p, int);     // 후위 p++
};

Point& operator++(Point& p) {
    p.x++; p.y++;
    return p;
}

Point operator++(Point& p, int) {
    Point old = p;
    p.x++; p.y++;
    return old;
}

Point p3(p1 + p2);         // (1,2) + (3,4)
cout << (p3 == p1);
```
```
x: 4, y = 6
0
```
- `p1 + p2`는 `p1.operator+(p2)`로 바뀌어 호출된다. 객체도 기본 타입처럼 연산자로 다룰 수 있다.
- 멤버 함수로도, `friend` 전역 함수로도 만들 수 있다.
- 후위 `++`는 구분용으로 쓰지 않는 `int` 매개변수를 받는다.
- 전위는 바뀐 자기 자신을 **참조**로, 후위는 바뀌기 전 값을 **복사본**으로 반환한다. 그래서 전위가 더 가볍다.
- 기본 생성자 `Point() {}`는 `x`, `y`를 초기화하지 않는다. `: x(0), y(0)`을 넣는다.
