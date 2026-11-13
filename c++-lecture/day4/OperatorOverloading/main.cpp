#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

class MyString //문자열 처리 클래스
{
private:
    char* str;  //문자열 저장할 메모리 할당 받아 주소 저장할 변수
    int len;    //문자열 길이

public:

    // 기본 생성자
    MyString() :len(0), str(NULL) {}

    // 문자열 생성자
    MyString(const char* s)
    {
        len = strlen(s);
        str = new char[len + 1];
        strcpy(str, s);
    }

    // 복사 생성자
    MyString(const MyString& other)
    {
        len = strlen(other.str);
        str = new char[len + 1];
        strcpy(str, other.str);
    }

    // 소멸자
    ~MyString()
    {
        if(str != NULL)
            delete[] str;
    }

    //-------------------------
    // = 연산자
    //-------------------------
    MyString& operator=(const MyString& other)
    {
        len = other.len;
        if(str != NULL) delete[] str;
        str = new char[len + 1];
        strcpy(str, other.str);

        return *this;
    }

    //-------------------------
    // + 연산자
    //-------------------------
    MyString operator+(const MyString& other) const
    {
        MyString temp;
        temp.len = len + other.len;
        temp.str = new char[temp.len + 1];
        strcpy(temp.str, str); strcpy(temp.str + len, other.str);
        return temp;
    }

    //-------------------------
    // += 연산자
    //-------------------------
    MyString& operator+=(const MyString& other)
    {
        int oldLen = len;
        char * oldStr = str;

        len = len + other.len;
        str = new char[len + 1];
        strcpy(str, oldStr); strcpy(str + oldLen, other.str);
        delete oldStr;

        return *this;
    }

    //-------------------------
    // == 연산자
    //-------------------------
    bool operator==(const MyString& other) const
    {
        return strcmp(str, other.str) == 0;
    }

    //-------------------------
    // [] 연산자
    //-------------------------
    char& operator[](int index)
    {
        return str[index];
    }

    //-------------------------
    // 길이
    //-------------------------
    int length() const
    {
        return len;
    }

    //-------------------------
    // << 연산자
    //-------------------------
    friend ostream& operator<<(ostream& out, const MyString& s);

    //-------------------------
    // >> 연산자
    //-------------------------
    friend istream& operator>>(istream& in, MyString& s);
};

ostream& operator<<(ostream& out, const MyString& s)
{
    out << s.str;
    return out;
}

istream& operator>>(istream& in, MyString& s)
{
    char buf[1024];
    in >> setw(sizeof(buf)) >> buf;
    s = buf;
    return in;
}
int main()
{
    MyString s1("Hello");
    MyString s2(" World");

    MyString s3;

    s3 = s1 + s2;

    cout << s3 << endl;

    s1 += s2;

    cout << s1 << endl;

    if (s1 == s3)
        cout << "Same\n";
    else
        cout << "Different\n";

    cout << s3.length() << endl;

    cout << s3[1] << endl;

    s3[0] = 'h';

    cout << s3 << endl;

    MyString s4;
    cin >> s4;
    cout << "s4: " << s4 << endl;;
}