#ifndef __DAY3_LIB_H__

#define __DAY3_LIB_H__
#define _CRT_SECURE_NO_WARNINGS
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))

#include <stdio.h>
#include <string.h>

void inputData(int * arr, int n);
void printData(int * arr, int n);
int sumData(int * arr, int n);
double avgData(int * arr, int n);
void swap(int * p1, int * p2);
int findMaxData(int * arr, int n);
int findMinData(int * arr, int n);
int findMinIndex(int * arr, int start, int n);
void selectionSortData(int * arr, int n);
void bubbleSortData(int * arr, int n);
void insertionSortData(int * arr, int n);

#endif