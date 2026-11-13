# C++ Day1 — 클래스와 객체, 생성자, 접근 제어

> 2026-11-10 학습 정리

## 클래스 기본과 new/delete
코드: [hello.cpp](hello.cpp)

```cpp
class Test {
public:
    int a;
    int b;

    void printData() {
        cout << a << ", " << b << endl;
    }
};

Test t1;            // 스택에 객체 생성
t1.a = 10;
t1.b = 20;
t1.printData();     // 10, 20

Test * t2 = new Test;   // 힙에 객체 생성
t2->a = 100;
t2->b = 200;
t2->printData();    // 100, 200

delete t2;
```
- 클래스는 C 구조체에 **함수(멤버 함수)**까지 넣은 것이다. 멤버 함수는 자기 객체의 멤버를 그냥 이름으로 쓴다.
- `new`는 `malloc` + 생성자 호출, `delete`는 소멸자 호출 + `free`라고 보면 된다. 크기 계산이나 캐스팅이 필요 없다.
- 객체는 `.`으로, 객체 포인터는 `->`로 멤버에 접근한다. C 구조체와 같다.
- ⚠️ 코드에서 `delete t2` 뒤에 다시 `t2->a = 100`을 쓴다. 해제한 메모리를 쓰는 것이라 UB다. `delete` 뒤에는 `t2 = nullptr;`을 넣는다.
- `main`이 `#if 0` 안에 있어서 지금 상태로는 링크 오류가 난다.

## 헤더와 소스 나누기
코드: [Person/](Person/)

```cpp
// Person.h
#pragma once
#include <string>

class Person {
public:
    std::string name;
    std::string tel;
    int num;
    void inputInfo(std::string n, std::string t, int no);
    void outputInfo();
};
```
```cpp
// Person.cpp
void Person::inputInfo(string n, string t, int no) {
    name = n;
    tel = t;
    num = no;
}

void Person::outputInfo() {
    cout << "name: " << name << ", tel : " << tel << ", number: " << num << endl;
}
```
```
name: John, tel : 010-1234-1234, number: 5
```
- 클래스 선언은 헤더에, 멤버 함수 정의는 `.cpp`에 둔다. C의 분할 컴파일과 같은 구조다.
- 클래스 밖에서 정의할 때는 `클래스이름::함수이름`으로 어느 클래스의 함수인지 밝힌다. `::`는 범위 지정 연산자다.
- `#pragma once`는 `#ifndef` 인클루드 가드와 같은 역할을 한 줄로 한다.
- 헤더에서는 `using namespace std;` 대신 `std::string`처럼 직접 쓴다. 헤더를 포함하는 모든 파일에 영향을 주기 때문이다.
- 빌드: `g++ main.cpp Person.cpp -o main`

## 생성자
코드: [Generator/Generator.cpp](Generator/Generator.cpp)

```cpp
class Person {
private:
    string name;
    int age;
public:
    Person(): name("amugae"), age(0) { }
    Person(string name, int age):name(name), age(age) { }

    void printInfo() {
        cout << name << " / " << age << endl;
    }
};

Person p;                 // 기본 생성자
Person p2("John", 3);
Person p3 = p;            // 복사 생성자 (컴파일러가 만들어 줌)

Person arr1[3];                                           // 기본 생성자 3번
Person arr2[3] = { {"Max", 3}, {"Lilly", 5}, {"Kan", 10} };
```
```
amugae / 0
John / 3
amugae / 0
amugae / 0
amugae / 0
amugae / 0
Max / 3
Lilly / 5
Kan / 10
```
- 생성자는 클래스 이름과 같고 반환형이 없다. 객체가 만들어질 때 자동으로 한 번 호출된다.
- 매개변수가 다른 생성자를 여러 개 만들 수 있다(오버로딩).
- `: name(name), age(age)`는 **멤버 초기화 리스트**다. 본문에서 대입하는 것보다 먼저, 멤버가 만들어지면서 값이 들어간다. `const` 멤버나 참조 멤버는 여기서만 초기화할 수 있다.
- 매개변수와 멤버 이름이 같아도 초기화 리스트에서는 괄호 밖이 멤버, 괄호 안이 매개변수다.
- 배열을 만들면 원소마다 생성자가 호출된다. 초기값이 없으면 기본 생성자가 필요하다.

## 객체 배열과 동적 할당
코드: [Array/Array.cpp](Array/Array.cpp)

```cpp
Point *p = new Point(1, 2);                          // 객체 1개
Point points[2];                                     // 스택 배열, 기본 생성자 2번
Point *arr[] = {new Point(2,3), new Point(4,5)};     // 포인터 배열, 객체는 힙

delete p;
for(int i = 0; i < 2; i++) delete arr[i];

Point *arr2 = new Point[3];        // 객체 배열을 힙에
delete[] arr2;

Point **arr3 = new Point* [3];     // 포인터 배열을 힙에
for(int i = 0; i < 3; i++) arr3[i] = new Point(i+2, i);
for(int i = 0; i < 3; i++) delete arr3[i];
delete[] arr3;
```
```
x:1, y:2
x:2, y:3
x:4, y:5
x:0, y:2
x:1, y:3
x:2, y:4
(여기서 비정상 종료 — 아래 ⚠️의 delete[] 3번 때문. 고치면 arr3의 x:2, y:0 / x:3, y:1 / x:4, y:2가 이어서 나온다)
```
- `new`로 하나 만들면 `delete`, `new[]`로 배열을 만들면 `delete[]`로 해제한다. 짝이 맞아야 한다.
- 포인터 배열은 **객체마다** `delete`하고, 배열 자체도 해제한다. Day8(C)의 이중 포인터 해제와 같은 순서다.
- ⚠️ 수업 코드에서 고칠 점
  - `arr2[i] = * new Point(i, i+2);`는 새 객체를 복사만 하고 그 주소를 버려서 메모리가 샌다. `arr2[i] = Point(i, i+2);`로 쓴다.
  - `delete[] arr2;` 앞의 `for`에 중괄호가 없어서 `delete[]`가 3번 실행된다. 실행해 보면 프로그램이 비정상 종료한다.
  - `delete arr3;`는 `new[]`로 만든 배열이므로 `delete[] arr3;`이어야 한다.

## 접근 제어와 상속 맛보기
코드: [Test/main.cpp](Test/main.cpp)

```cpp
class Parent {
private:
    int a;
public:
    int b;
    void setA(int x) { a = x; }
    int getB() const { return a; }   // const: 멤버변수 수정 불가
protected:
    int c;
};

class Child : Parent {
public:
    void print() {
        c = 30;
        cout << "in Child class c: " << c << endl;
    }
};
```
```
10
20
in Child class c: 30
```
| 접근 지정자 | 클래스 안 | 자식 클래스 | 밖 |
|---|---|---|---|
| `private` | O | X | X |
| `protected` | O | O | X |
| `public` | O | O | O |

- `private` 멤버는 `setA` 같은 public 함수(setter/getter)를 통해서만 바꾼다. 이것이 **캡슐화**다.
- 함수 뒤의 `const`는 "이 함수는 멤버를 바꾸지 않는다"는 약속이다. `const` 객체에서도 호출할 수 있다.
- `class Child : Parent`처럼 지정자를 생략하면 `private` 상속이다. 부모의 public 멤버도 밖에서는 안 보인다. 보통은 `: public Parent`로 쓴다.
- `getB()`는 이름과 달리 `a`를 반환한다. 이름과 하는 일을 맞춘다.

## 과제: 주소록
코드: [homework/](homework/)

```cpp
class Person {             // 한 사람의 정보
    int num; string name; string tel;
public:
    string toString() const;
    void setTel(string tel);
    int getNum();
};

class PersonArr {          // Person* 10개를 담는 배열
    Person * arr[10];
    int cnt;
public:
    ~PersonArr();          // 저장된 Person을 모두 delete
    bool addPerson(Person * p);
    Person* getPerson(int idx);
    int getPersonIdx(int num);
    void delPerson(int idx);
};

class PersonService {      // 메뉴 기능 (add, get, edit, del, printAll)
    PersonArr arr;
};
```
```
입력: 1 Kim 010-1 / 2 Lee 010-2 / 3 Park 010-3 추가 → 2번 조회 → 2번 전화 010-9999로 수정 → 1, 3번 삭제
출력(마지막 printAll): num: 2, name: Lee, tel: 010-9999
```
- **역할마다 클래스를 나눴다.** 데이터(`Person`), 저장소(`PersonArr`), 기능(`PersonService`). `PersonService`가 `PersonArr`를 멤버로 가지는 것은 포함(has-a) 관계다.
- `PersonArr`의 소멸자가 `new`로 받은 `Person`을 해제한다. 객체가 사라질 때 자원도 함께 정리된다.
- 삭제할 때 `delete` 후 뒤 원소를 한 칸씩 앞으로 당긴다.
- `toString()`이 문자열을 만들어 돌려주고, 출력은 호출한 쪽이 한다. 출력 방식이 바뀌어도 클래스는 그대로 둘 수 있다.
