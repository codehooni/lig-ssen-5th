#include <stdio.h>

extern int N;
extern int sol[10];
extern int bitMask;
void printList(int * arr, int n);

void test10(int L) {
    if(L > N) {
        printList(sol, N);
        return;
    }

    for(int i = 1; i <= N; i++) {
        if((bitMask >> i) & 1u) continue;

        sol[L] = i;
        bitMask |= (1 << i);
        test10(L + 1);
        bitMask &= ~(1 << i);
    }
}

int main(void) {

    test10(1);

    return 0;
}