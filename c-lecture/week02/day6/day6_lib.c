#include "day6_lib.h"

void print_ary(int (*arr)[3][4]) {
    int row, col;
    row = SIZE(*arr);
    col = SIZE(**arr);

    int (*p)[4] = (int(*)[4]) arr;
    int *ip = (int*)p;

    for(int r = 0; r < row; r++) {
        for(int c = 0; c < col; c++) {
            printf("%d ", (*arr)[r][c]);
            printf("%d ", p[r][c]);
            printf("%d ", *ip++);
        }
    }

    printf("\n");
}

// a pointer to int 를 이용해 값 교환
void exchange0(int * a, int * b) {

    int temp = *a;
    *a = *b;
    *b = temp;

}

// double pointer를 이용해 값 교환
void exchange1(int ** a, int ** b) {

    int temp = **a;
    **a = **b;
    **b = temp;

}

// triple pointer를 이용해 값 교환
void exchange2(int *** a, int *** b) {

    int temp = ***a;
    ***a = ***b;
    ***b = temp;

}

// an address of a pointer to int 를 이용해 값 교환
void exchange3(int ** a, int ** b) {

    int * temp = *a;
    *a = *b;
    *b = temp;

}

// triple pointer 를 이용해 an address of double pointer 값 교환
void exchange4(int *** a, int *** b) {

    int * temp = **a;
    **a = **b;
    **b = temp;

}

// triple pointer 를 이용해 app, bpp 값 교환
void exchange5(int *** a, int *** b) {

    int ** temp = *a;
    *a = *b;
    *b = temp;

}

int add(int a, int b) {
    return a + b;
}