#include <stdio.h>

#if 1

int main(void) {

    int a[2][3][4] = { 0 }; // an array of 2 array of 3 array of 4 array of int
    int (*b[3])[4] = { 0 }; // an array of a pointer to 4 array of int
    int* (*c[2]) (int *) = { 0 }; // an array of 2 pointer to function (int *) returning pointer to int
    int* d[3][4] = { 0 }; // an array of 3 array of 4 pointer to int
    int (*(*e[5]) (void))[4] = { 0 }; // an array of 5 pointer to function returning a pointer to an array of 4 int
    // pa ~ pe 포인터 편수 선언

    int (*pa)[3][4] = a;
    int (**pb)[4] = b;
    int* (**pc) (int *) = c;
    int* (*pd)[4] = d;
    int (*(**pe) (void))[4] = e;

    return 0;
}

#endif