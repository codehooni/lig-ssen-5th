#ifndef IDK_LIB_H

#define IDK_LIB_H
#define _CRT_SECURE_NO_WARNINGS
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char * colors[];

typedef struct profile {
    int age;
    size_t colorCnt;
    char ** favorateColor;
    char * name; // 이름 변경 가능 #동적할당
}profile_t;

typedef struct student {
    int num;
    double grade;
    profile_t profile;
}student_t;

typedef struct _class_t { // 사용 해도 되고 안 해도 됨.
    student_t * stu;
    int n;
}class_t;

typedef char str_t[20];

void initClass(class_t **);
int getColorIndex(char *);
void printClass(class_t);
void freeMem(class_t *);

#endif
