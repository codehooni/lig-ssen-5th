#include "day8_lib.h"

void printData(int * arr, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int getInt() {
    int num;

    printf("Please enter the possitive number: ");

    scanf("%d", &num);
    getchar();

    return num;
}

void freeMem(void ** p) {
    if(p == NULL) return;
    free(*p);
    *p = NULL;
}

void freeDoubleMem(void *** p, int n) {
    if(p == NULL) return;

    for(int i = 0; i < n; i++) {
        free((*p)[i]);
        (*p)[i] = NULL;
    }

    free(*p);
    *p = NULL;

}