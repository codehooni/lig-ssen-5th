#ifndef DAY7_LIB_H

#define DAY7_LIB_H
#define _CRT_SECURE_NO_WARNINGS
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _score_t {
    int kor;
    int eng;
    int mat;
} score_t;

int sum(int, int);
int sub(int, int);
int mul(int, int);
int div2(int, int);
int mod(int, int);
void printAry(int *, int);


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

void printDoubleData(double * arr, int n);
void printCharData(char ** arr, int n);
void printDoubleArray(int (* arr)[3], int n, int m);
void printScore(score_t * arr, int n);
void printAllType(void * arr, int n, int size);

int comp_asc(int a, int b);
int comp_desc(int a, int b);
int compint(const void *, const void *);
int compDouble(const void *, const void *);
int compChar(const void *, const void *);
int compDA(const void * a, const void * b);
int compScore(const void * a, const void * b);

int findIndex(int * arr, int start, int n, int (*comp)(int, int));
void selectionSort(int * arr, int n, int (*comp)(int, int));
void bubbleSort(int * arr, int n, int (*comp)(int, int));
void insertionSort(int * arr, int n, int (*comp)(int, int));

#endif