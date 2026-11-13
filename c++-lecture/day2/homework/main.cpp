#include "AcademicManagement.h"

int main() {

    Professor p1(100, "Khan", "Software");

    p1.offerCourse("Data Structure");
    p1.offerCourse("Algorithm");
    p1.offerCourse("Architecture of Computer");
    p1.offerCourse("C language");

    p1.viewCourseList();
    
    p1.removeCourse("Algorithm");
    p1.viewCourseList();

    p1.viewProfile();

    Student s1(1, "Tom", "Software");

    s1.courseRegistration("C language");
    s1.courseRegistration("Algorithm");
    s1.viewCourseList();
    s1.courseDrop("C language");
    s1.viewCourseList();

    Faculty f1(10, "Shawn", "Computer Engineering", "aa");
    f1.managingNewHires(1);

    return 0;
}