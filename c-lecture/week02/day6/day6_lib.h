#ifndef DAY_LIB_H

#define DAY_LIB_H
#define _CRT_SECURE_NO_WARNINGS
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_ary(int (*arr)[3][4]);
void exchange0(int * a, int * b);
void exchange1(int ** a, int ** b);
void exchange2(int *** a, int *** b);
void exchange3(int ** a, int ** b);
void exchange4(int *** a, int *** b);
void exchange5(int *** a, int *** b);\
int add(int a, int b);

#endif
