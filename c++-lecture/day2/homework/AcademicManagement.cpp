#include "AcademicManagement.h"

Profile::Profile(int no, string name, string department): no(no), name(name), department(department) { }

void Profile::viewProfile() {
    cout << "no: " << no << ", name: " << name << ", department: " << department << endl;
}

Student::Student(int no, string name, string department): Profile(no, name, department) { }

void Student::courseRegistration(string course) {
    courses.push_back(course);
}

void Student::courseDrop(string course) {
    auto it = find(courses.begin(), courses.end(), course);
    if(it != courses.end()) {
        courses.erase(it);
    }
}

void Student::viewCourseList() {
    cout << "Course List: [";
    for(auto& c : courses) {
        cout << c << ' ';
    }
    cout << "]\n";
}

Professor::Professor(int no, string name, string department): Profile(no, name, department) { }

void Professor::offerCourse(string name) {
    courses.push_back(name);
}

void Professor::removeCourse(string name) {
    auto it = find(courses.begin(), courses.end(), name);
    if(it != courses.end()) {
        courses.erase(it);
    }
}

void Professor::viewCourseList() {
    cout << "Course List: [";
    for(auto& c : courses) {
        cout << c << ", ";
    }
    cout << "]\n";
}

Faculty::Faculty(int no, string name, string department, string positioin): Profile(no, name, department), position(position) { }

void Faculty::managingNewHires(int no) {
    cout << "Managing No: " << no << '\n';
}