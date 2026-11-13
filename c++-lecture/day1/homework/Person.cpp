#include "Person.h"

// 수업전에 포함관계 설명해달라고 부탁하기

// Person 구현

string Person::toString() const {
    return "num: " + to_string(num) + ", name: " + name + ", tel: " + tel;
}

void Person::setTel(string tel) {
    this->tel = tel;
}

int Person::getNum() {
    return this->num;
}

// PersonArr

PersonArr::~PersonArr() {
    for(int i = 0; i < cnt; i++)
        delete arr[i];
}

bool PersonArr::addPerson(Person * p) {
    if(cnt < 10) {
        arr[cnt++] = p;
        return true;
    }
    return false;
}

Person* PersonArr::getPerson(int idx) {
    if(idx >= cnt) return NULL;
    return arr[idx];
}

int PersonArr::getPersonIdx(int num) {
    for(int i = 0; i < cnt; i++)
        if(num == arr[i]->getNum()) return i;
    
    return -1;
}

int PersonArr::getCnt() {
    return cnt;
}

void PersonArr::delPerson(int idx) {
    if(idx >= cnt) {
        cout << "Please enter the currect idx" << endl;
        return;
    }

    delete arr[idx];

    cnt--;
    for(int i = idx; i < cnt; i++) {
        arr[i] = arr[i + 1];
    }
}

void PersonService::add() {
	int num, idx=0;
	string name, tel;
	cout << "=== add ===" << endl;
	
	while (idx>=0) {
		cout << "num:";
		cin >> num;
		idx = arr.getPersonIdx(num);
	}
	cout << "name:";
	cin >> name;
	cout << "tel:";
	cin >> tel;
	arr.addPerson(new Person(num, name, tel));
}

void PersonService::get() {
    int num, idx = -1;
	cout << "=== get ===" << endl;

    while(idx == -1) {
        cout << "num:";
		cin >> num;
		idx = arr.getPersonIdx(num);
    }

    Person *p = arr.getPerson(idx);

	cout << p->toString() << endl;
}

void PersonService::edit() {
    int num, idx = -1;
    string tel;
	cout << "=== edit ===" << endl;

    while(idx == -1) {
        cout << "num:";
		cin >> num;
		idx = arr.getPersonIdx(num);
    }

	cout << "tel:";
	cin >> tel;

    Person * p = arr.getPerson(idx);
    p->setTel(tel);
}

void PersonService::del() {
    int num, idx = -1;
	cout << "=== del ===" << endl;

    while(idx == -1) {
        cout << "num:";
		cin >> num;
		idx = arr.getPersonIdx(num);
    }

    arr.delPerson(idx);    
}

void PersonService::printAll() {
    for(int i = 0; i < arr.getCnt(); i++) {
        cout << arr.getPerson(i)->toString() << endl;
    }
}