#include "day7_lib.h"

#if 0

typedef struct func {
    const char * name;
    int (*fp)(int, int);
    int res;
} FUNC;

int main(void) {

    const FUNC funcs[] = {
        {"sum", sum},
        {"sub", sub},
        {"mul", mul},
        {"div2", div2},
        {"mod", mod},
    };

    FUNC * sp = funcs;

    const int N = SIZE(funcs);
    int n1 = 25, n2 = 6, total = 0;

    for(int i = 0; i < N; i++) {
        sp->res = sp->fp(n1, n2);
        total += sp->res;
        printf("%s = %d\n", sp->name, sp->res);
        sp++;
    }

    printf("sum = %d\n", total);
    
    return 0;
}

#endif

#if 0

typedef struct func {
    const char * name;
    int (*fp)(int, int);
    int res;
} FUNC;

int main(void) {

    const FUNC funcs[] = {
        {"sum", sum},
        {"sub", sub},
        {"mul", mul},
        {"div2", div2},
        {"mod", mod},
    };

    FUNC * sp = funcs;

    const int N = SIZE(funcs);
    int n1 = 25, n2 = 6, total = 0, menu;

    while(1) {
        printf("\nWhich operation do you want to perform?\n");
        for(int i = 0; i < N; i++) {
            printf("%d. %s\n", i, funcs[i].name);
        }
        printf("%d. exit\n", N);
        printf("Select (0-%d): ", N);

        scanf("%d", &menu);

        printf("%s = %d\n", funcs[menu].name, funcs[menu].fp(n1, n2));
    }


    printf("sum = %d\n", total);
    
    return 0;
}

#endif

#if 0

int main(void) {

    int ary[] = { 8, 5, 2, 12, 7, 9, 4, 6, 10, 3  };
    double doubleAry[] = { 8.234, 5.123, 5.14, 5.10, 5.3, 9.3, 4., 6., 10.32, 3.32  };
    char * charAry[] = { "kiwi", "banana", "melon", "apple", "orange" };
    int A[][3] = { {1, 3, 5}, {3, 1, 2}, {2, 4, 1} };
    score_t scr[] = {
        {80, 90, 85},
        {100, 80, 70},
        {90, 95, 100},
        {88, 77, 50},
        {60, 100, 20},
    };

    // printData(ary, SIZE(ary));
    // selectionSort(ary, SIZE(ary), comp_desc);
    // printData(ary, SIZE(ary));
    // bubbleSort(ary, SIZE(ary), comp_asc);
    // printData(ary, SIZE(ary));
    // insertionSort(ary, SIZE(ary), comp_desc);
    // printData(ary, SIZE(ary));

    // qsort(ary, SIZE(ary), sizeof(int), compint);
    // qsort(doubleAry, SIZE(doubleAry), sizeof(double), compDouble);
    // qsort(charAry, SIZE(charAry), sizeof(char *), compChar);
    // qsort(A, SIZE(A), sizeof(*A), compDA);
    qsort(scr, SIZE(scr), sizeof(*scr), compScore);
    // printData(ary, SIZE(ary));
    // printDoubleData(doubleAry, SIZE(doubleAry));
    // printCharData(charAry, SIZE(charAry));
    // printDoubleArray(A, SIZE(A), SIZE(*A));
    printScore(scr, SIZE(scr));

    return 0;
}

#endif

#if 0

typedef int (*FP1)(int);
typedef int (*FP2)(int, int);
typedef FP2 (*FP3)(int, int);

int (*(* act(int, int (*) (int))) (int, int))(int, int);
FP3 act(int, FP1);

int (*getFunction(int no)) (int, int) {
    static int (*fp[])(int, int) = {sum, sub, mul, div2};
    return fp[no];
}

int main(void) {

    int (*fp)(int, int) = getFunction(3);
    printf("%d \n", fp(3, 2));

    return 0;
}

#endif

#if 0

typedef int (*FP) (int, int);

int main(void) {
    void * vp;
    int a = 65;
    double b = 3.14;

    vp = &a;

    printf("%d\n", *(int*) vp);

    vp = &b;

    printf("%.2lf\n", *(double*) vp);
    printf("%d\n", *(int*) vp);
    
    vp = sum;

    printf("%d\n", (*******(int(*)(int, int)) vp)(1, 2));
    printf("%d\n", (***************(FP) vp)(1, 2));
    return 0;
}

#endif