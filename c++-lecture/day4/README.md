# C++ Day4 — 연산자 오버로딩 심화, 예외 처리

> 2026-11-13 학습 정리

## 복습: 증감, 복합 대입, 입출력 연산자
코드: [review.cpp](review.cpp)

```cpp
class Point {
    int x, y;
public:
    Point& operator++() {          // 전위
        x++; y++;
        return *this;
    }
    Point operator++(int) {        // 후위
        Point old = *this;
        x++; y++;
        return old;
    }
    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    friend istream& operator>>(istream& in, Point& p);
    friend ostream& operator<<(ostream& out, const Point& p);
};

ostream& operator<<(ostream& out, const Point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

Point p(1, 2);
p.print();          // (1, 2)
p++;
p++.print();        // (2, 3)  ← 증가 전 복사본을 출력, p는 (3, 4)
(++p).print();      // (4, 5)

Point q(10, 20);
p += q;
cout << p << endl;  // (14, 25)
```
```
(1, 2)
(2, 3)
(4, 5)
(14, 25)
```
- Day3에서 `friend` 전역 함수로 만든 `++`를 이번에는 멤버 함수로 만들었다. 멤버 함수에서는 `*this`를 반환한다.
- `p++.print()`는 증가 **전** 복사본으로 출력하므로 `(2, 3)`이 나오고, `p` 자신은 `(3, 4)`가 된다.
- `+=`는 자기 자신을 바꾸고 참조를 반환한다. 그래서 `a += b += c`처럼 이어 쓸 수 있다.
- `<<`, `>>`는 왼쪽 피연산자가 `cout`/`cin`이라 멤버 함수로 만들 수 없다. 전역 함수로 만들고 `private`에 접근하려고 `friend`로 지정한다.
- 스트림을 참조로 반환해야 `cout << p << endl;`처럼 이어진다.

## MyString — 동적 메모리를 가진 클래스
코드: [OperatorOverloading/main.cpp](OperatorOverloading/main.cpp)

```cpp
class MyString {
    char* str;
    int len;
public:
    MyString() :len(0), str(NULL) {}

    MyString(const char* s) {
        len = strlen(s);
        str = new char[len + 1];
        strcpy(str, s);
    }

    MyString(const MyString& other) {        // 복사 생성자: 깊은 복사
        len = strlen(other.str);
        str = new char[len + 1];
        strcpy(str, other.str);
    }

    ~MyString() {
        if(str != NULL) delete[] str;
    }

    MyString& operator=(const MyString& other) {
        len = other.len;
        if(str != NULL) delete[] str;        // 기존 메모리 해제
        str = new char[len + 1];
        strcpy(str, other.str);
        return *this;
    }

    MyString operator+(const MyString& other) const {
        MyString temp;
        temp.len = len + other.len;
        temp.str = new char[temp.len + 1];
        strcpy(temp.str, str); strcpy(temp.str + len, other.str);
        return temp;
    }

    MyString& operator+=(const MyString& other) { /* 새로 할당해 이어 붙이고 옛 메모리 해제 */ }
    bool operator==(const MyString& other) const { return strcmp(str, other.str) == 0; }
    char& operator[](int index) { return str[index]; }
};

istream& operator>>(istream& in, MyString& s) {
    char buf[1024];
    in >> setw(sizeof(buf)) >> buf;
    s = buf;
    return in;
}
```
```cpp
MyString s1("Hello");
MyString s2(" World");
MyString s3;

s3 = s1 + s2;           cout << s3 << endl;     // Hello World
s1 += s2;               cout << s1 << endl;     // Hello World
cout << (s1 == s3 ? "Same" : "Different");      // Same
cout << s3.length();                             // 11
cout << s3[1];                                   // e
s3[0] = 'h';            cout << s3 << endl;     // hello World
cin >> s4;              // abcdef 입력 → s4: abcdef
```
- 포인터 멤버가 있는 클래스는 **소멸자, 복사 생성자, 대입 연산자** 셋을 함께 직접 만들어야 한다(3의 법칙). 하나라도 빠지면 얕은 복사로 같은 메모리를 두 번 해제한다.
- 대입 연산자는 복사 생성자와 달리 이미 메모리를 가진 객체에 대입하므로, 기존 `str`을 먼저 해제한다.
- `operator[]`가 `char&`를 반환해서 `s3[0] = 'h'`처럼 값을 바꿀 수 있다.
- `>>`는 버퍼에 읽은 뒤 `s = buf;`로 대입한다. `buf`가 `MyString(const char*)`로 바뀐 다음 `operator=`가 호출된다.
- `setw(sizeof(buf))`는 버퍼보다 긴 입력을 잘라 넘침을 막는다.
- ⚠️ `operator+=`에서 `new[]`로 만든 `oldStr`을 `delete`로 해제한다. `delete[]`여야 한다.
- ⚠️ `operator=`에 자기 대입 확인이 없다. `s1 = s1;`이면 자기 `str`을 먼저 지운 뒤 지운 곳에서 복사한다. 맨 앞에 `if(this == &other) return *this;`를 넣는다.
- ⚠️ 빈 `MyString`(str이 NULL)을 복사하면 `strlen(NULL)`로 죽는다. 복사 생성자에서 `other.len`을 쓰고 NULL을 확인한다.

## 예외 처리
코드: [a/main.cpp](a/main.cpp)

```cpp
int a = 1, b = 0;

try {
    cout << a / b << endl;
    cout << "Program End" << endl;
} catch (int e) {
    cout << e << endl;
}
```
```
(아무것도 출력되지 않고 프로그램이 비정상 종료)
```
- `try` 안에서 `throw`된 예외를 타입이 맞는 `catch`가 받는다.
- 정수를 0으로 나누는 것은 C++ 예외가 아니라 CPU 오류(UB)다. `throw`가 없으니 `catch`로 잡히지 않고 프로그램이 죽는다.
- 잡으려면 직접 검사해서 던진다.
```cpp
try {
    if(b == 0) throw b;
    cout << a / b << endl;
} catch (int e) {
    cout << "divide by " << e << endl;
}
```
- `throw` 뒤의 코드("Program End")는 실행되지 않고 바로 `catch`로 간다.
