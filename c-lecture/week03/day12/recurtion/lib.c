#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int N = 3;
int sol[100];
int bitMask = 0;

void printList(int * arr, int n) {
    for(int i = 1; i <= n; i++) {
        printf("%d ", sol[i]);
    }
    printf("\n");
}

void test09(void) {
    for(int i = 1; i <= 3; i++) 
        for(int j = 1; j <= 3; j++) 
            for(int k = 1; k <= 3; k++) 
                if(i != j && j != k && k != i)
                    printf("%d %d %d\n", i, j, k);
}

// N, L, i, start: nCr에서 r에 해당, 출력문 하나에서 현재 위치, 현재 값, 현재 함수에서 출력 가능한 최솟 값
// test08: nCr n개 중에서 r개를 순서 없이 뽑는 갯수

void test08(int L, int start) {
    if(L > N) {
        printList(sol, N);
        return;
    }

    for(int i = start; i <= 6; i++) {
        sol[L] = i;
        test08(L + 1, i + 1);
    }
}

void test07(int L) {
    if(L > N) {
        printList(sol, N);
        return;
    }

    for(int i = 0; i < 3; i++) {
        sol[L] = i;
        test07(L + 1);
    }
}

int factorial(int n) {
    static int sol[100] = { 0 };

    if(n == 1) return 1;

    if(sol[n] != 0) return sol[n];

    sol[n] = n * factorial(n - 1);

    return sol[n];
}

void test04(int n) {
    if(n > 5) return ;
    for(int i = 1; i <= n; i++) printf("%d ", i); 
    printf("\n");
    test04(n + 1);
}

void test03(int n) {
    if(n > 5) return ;

    if(n & 1) printf("%d ", n);
    test03(n + 1);
    if(!(n & 1)) printf("%d ", n);
}

void test02(int n) {
    if(n > 5) return ;
    printf("%d ", n);
    test02(n + 1);
    printf("%d ", n);
}

void test01(int n) {
    if(n > 5) return ;
    test01(n + 1);
    printf("%d ", n);
}

// int main(void) {

//     // printf("%d\n", factorial(5));
//     test07(1);

//     return 0;
// }