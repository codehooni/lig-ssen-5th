#ifndef DAY4_LIB_H

#define DAY4_LIB_H
#define _CRT_SECURE_NO_WARNINGS
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))

#include <stdio.h>
#include <string.h>

void my_gets(char * str, int n);
char * to_upper(char * str);
char * my_strcpy(char * to, const char * from);
void increament();
int getNum();

extern int num;

#endif