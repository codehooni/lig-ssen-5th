#define _CRT_SECURE_NO_WARNINGS
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))

#include <stdio.h>
#include <string.h>

#if 1

void func1(int (*p) [4], int r) {
    int c = sizeof(*p) / sizeof(**p);
    int n = r * c;

    for(int i = 0; i < n; i++) {
        printf("%d ", *(*p + i));
    }
}

void func2(int (*p) [4], int r) {
    int c = sizeof(*p) / sizeof(**p);
    int n = r * c;

    int (*p2)[6] = (int (*) [6])p;
    r = n / 6;
    c = 6;

    for(int i = 0; i < n; i++) {
        printf("%d ", *(*p + i));
    }

    int (*p3)[2][3] = (int (*) [2][3]) p;
}

void func3(int (*p)[3][4]) {
    int r = SIZE(*p);
    int c = SIZE(**p);

    printf("%d %d\n", r, c);
}

void func4(int (*p)[2][3][4]) {
    int d = SIZE(*p);
    int r = SIZE(**p);
    int c = SIZE(***p);

    printf("%d %d %d\n", d, r, c);
}

// int a[2][3][4]
// 구성요소: 2개
// 구성요소의 타입: int [3][4]

// int (*b[3])[4]
// 구성요소: 3개
// 구성요소의 타입: int (*) [4]

// int* (*c[2])(int*)
// 구성요소: 2개
// 구성요소의 타입: int* (*) (int*)

// int* d[3][4]
// 구성요소: 3개
// 구성요소의 타입: int* [4]

// int(*(*e[5])(void))[4]
// 구성요소: 5개
// 구성요수의 타입: (*(*) (void))[4]




int main(void) {

    int arr[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int b[2][3][4] = { 0 };


    // func1(arr, SIZE(arr));
    // func2(arr, SIZE(arr));
    // func3(&arr);

    func4(&b);

    return 0;
}

#endif



#if 0

void printData(int *, int);

// call by value
void func1(int a, int b) {
    a = 20;
}

// call by reference
void func2(int * pa, int * pb) {
    *pa = 20;
}

void func3(const int (*p1)[5], int (*p2), const int n) {
    for (int i = 0; i < n; i++) {
        p2[i] += 5;
    }
}

void func4(int (*p1)[5]) {
    for (int i = 0; i < sizeof(*p1) / sizeof((*p1)[0]); i++) {
        (*p1)[i] += 5;
    }
}

// p[0][0] = **p, (*p)[0], *p[0]
// p[0][1] = *(*p + 1), (*p)[1], *(p[0] + 1)
// p[1][2] = *(*(p + 1) + 2), (*(p + 1))[2], *(p[1] + 2)
// p[3][0] = **(p + 3), (*(p + 3))[0], *p[3]
// p[1][2][3] = 
// {
//     (*(p + 1))[2][3],
//     *((*(p + 1))[2] + 3)),
//     (*((*(p + 1)) + 2))[3],
//     *(*(*(p + 1) + 2) + 3),

//     *(*(p[1] + 2) + 3),
//     (*(*(p[1] + 2)))[3]
//     *(p[1][2] + 3),
//     p[1][2][3],
// }

int main(void) {

    int a = 10, b = 20;

    func1(a, b);
    func2(&a, &b);

    int arr[5] = { 1, 2, 3, 4, 5 };
    printf("%p %p %p\n", &arr, arr, &arr[0]);
    func3(&arr, arr, SIZE(arr));
    printData(arr, SIZE(arr));
    func4(&arr);
    printData(arr, SIZE(arr));

    return 0;
}

void printData(int * arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

#endif

#if 0

int * func(int * arr) {

    return arr;
}

int main(void) {

    int arr[5] = {1, 2, 3, 4, 5};
    int * pa = 0;
    pa = func(arr);
    printf("%p %p\n", pa, arr);
    
    return 0;
}

#endif

#if 0

void func(char (*p)[10]) {
    printf("%d %d\n", sizeof(p), sizeof(*p));
}

void func2(char (*p)[5][10]) {
    printf("%d %d\n", sizeof(p), sizeof(*p));
}

void func3(char* p[5][10]) {
    printf("%d %d\n", sizeof p , sizeof(*p)); // 4 40
}

void func4(char **p) {
    printf("%d %d %d\n", sizeof(p), sizeof(*p), sizeof(**p)); // 4 4 1
}

char (* func5(void)) [10] {
    static char str[5][10] = {"apple", "banana", "orange"};
    return str; // char (*) [10]
}


int main(void) {

    char str[5][10];

    printf("sizeof(str[0]): %d\n", sizeof(str[0]));
    printf("sizeof(*str): %d\n", sizeof(*str));
    printf("sizeof(*(str + 1)): %d\n", sizeof(*(str + 1)));

    func(str);
    func2(&str);
    // func3(str);
    // func4(str);
    char (*p)[10] = func5();
    printf("%s %s %s", p[0], p[1], p[2]);

    return 0;
}

#endif