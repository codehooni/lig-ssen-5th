#include <iostream>
#include <string>
using namespace std;

class Score {
private:
    int kor;
    int eng;
    int mat;
    int total;
public:
    Score(): kor(0), eng(0), mat(0), total(0) { }
    Score(int kor, int eng, int mat): kor(kor), eng(eng), mat(mat) {
        total = kor + eng + mat;
    }
    void setKor(int kor) {
        total -= this->kor;
        this->kor = kor;
        total += this->kor;
    }
    int getKor() const {
        return kor;
    }
    void setEng(int eng) {
        total -= this->eng;
        this->eng = eng;
        total += this->eng;
    }
    int getEng() const {
        return eng;
    }
    void setMat(int mat) {
        total -= this->mat;
        this->mat = mat;
        total += this->mat;
    }
    int getMat() const {
        return mat;
    }
    int getTotal() const {
        return total;
    }
};

class Student {
private:
    int num;
    string name;
    Score * score; // 후에 깊은 복사는 복사 생성자 추가하기
public:
    Student():num(0), name("None"), score(new Score(0, 0, 0)) { }
    Student(int num, string name, Score * score): num(num), name(name), score(score) { }
    ~Student() { delete score; }
    void setScore(int kor, int eng, int mat) {
        score->setKor(kor);
        score->setEng(eng);
        score->setMat(mat);
    }

    string toString() const {
        return "num: " + to_string(num) + ", name: " + name +
            ", kor: " + to_string(score->getKor()) +
            ", eng: " + to_string(score->getEng()) +
            ", mat: " + to_string(score->getMat()) +
            ", total: " + to_string(score->getTotal());
    }
};

int main() {
    Student* students[10] = {
        new Student(1, "Kim", new Score(90, 80, 70)),
        new Student(2, "Lee", new Score(85, 95, 75)),
        new Student(3, "Park", new Score(70, 60, 100))
    };

    for (int i = 0; i < 3; i++)
        cout << students[i]->toString() << endl;

    for (int i = 0; i < 3; i++)
        delete students[i];   // new로 만든 건 delete로 해제

    


    return 0;
}
