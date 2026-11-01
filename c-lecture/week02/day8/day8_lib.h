#ifndef DAY8_LIB_H

#define DAY8_LIB_H
#define _CRT_SECURE_NO_WARNINGS
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printData(int *, int);
int getInt();
void freeMem(void **);
void freeDoubleMem(void ***, int);
#endif