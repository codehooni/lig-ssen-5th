#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Profile {
protected:
    int no;
    string name;
    string department;
    Profile(int no, string name, string department);
public:
    void viewProfile();
};

class Student : public Profile {
private:
    vector<string> courses;

public:
    Student(int no, string name, string department);
    void courseRegistration(string course);
    void courseDrop(string course);
    void viewCourseList();
};

class Professor : public Profile {
private:
    vector<string> courses;

public:
    Professor(int no, string name, string department);
    void offerCourse(string name);
    void removeCourse(string name);
    void viewCourseList();
};

class Faculty : public Profile {
private:
    string position;

public:
    Faculty(int no, string name, string department, string position);
    void managingNewHires(int no);
};