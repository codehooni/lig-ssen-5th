#include <iostream>
using namespace std;

class Dao { //dao(database access object) db 처리 전담 클래스. 인터페이스
public:
    virtual void insert() = 0;
    virtual void select() = 0;
    virtual void update() = 0;
    virtual void del() = 0;
};

class DaoOracleImpl : public Dao {
public:
    void insert() {
        cout << "Oracle insert" << endl;
    }
    void select() {
        cout << "Oracle select" << endl;
    }
    void update() {
        cout << "Oracle update" << endl;
    }
    void del() {
        cout << "Oracle delete" << endl;
    }
};

class DaoMySQLImpl : public Dao {
public:
    void insert() {
        cout << "MySQL insert" << endl;
    }
    void select() {
        cout << "MySQL select" << endl;
    }
    void update() {
        cout << "MySQL update" << endl;
    }
    void del() {
        cout << "MySQL delete" << endl;
    }
};

class Service {
private:
    Dao* dao;
public:
    Service(Dao* dao): dao(dao) {}
    ~Service() {
        delete dao;
    }
    void add() {
        dao->insert();
    }
    void get() {
        dao->select();
    }
    void edit() {
        dao->update();
    }
    void del() {
        dao->del();
    }
};

int main() {

    Service s(new DaoMySQLImpl());
    s.add();
    s.get();
    s.edit();
    s.del();

    return 0;
}