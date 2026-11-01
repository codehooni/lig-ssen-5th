#include "day7_lib.h"

int sum(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mul(int a, int b) {
    return a * b;
}

int div2(int a, int b) {
    return a / b;
}

int mod(int a, int b) {
    return a % b;
}

void printAry(int * arr, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void inputData(int * arr, int n) {

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

}

void printData(int * arr, int n) {
    
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int sumData(int * arr, int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += arr[i];
    }
    return total;
}

double avgData(int * arr, int n) {
    return (double) sumData(arr, n) / n;
}

void swap(int * p1, int * p2) {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int findMaxData(int * arr, int n) {

    int max = arr[0];

    for(int i = 1; i < n; i++) {
        if(max < arr[i])
            max = arr[i];
    }

    return max;
}

int findMinData(int * arr, int n) {

    int min = arr[0];

    for(int i = 1; i < n; i++) {
        if(min > arr[i])
            min = arr[i];
    }

    return min;
}

int findMinIndex(int * arr, int start, int n) {

    int minIndex = start;

    for(int i = start + 1; i < n; i++) {
        if(arr[minIndex] > arr[i])
            minIndex = i;
    }

    return minIndex;
}

void selectionSortData(int * arr, int n) {

    for(int i = 0; i < n - 1; i++) {
        int minIndex = findMinIndex(arr, i, n);
        swap(arr + i, arr + minIndex);
    }

}

void bubbleSortData(int * arr, int n) {

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - 1 - i; j++) {
            if(arr[j] > arr[j + 1])
                swap(arr + j, arr + (j + 1));
        }
    }

}

void insertionSortData(int * arr, int n) {

    for(int i = 1; i < n; i++) {
        for(int j = i - 1; j >= 0; j--) {
            if(arr[j] > arr[j + 1]) 
                swap(arr + j, arr + (j + 1));
            else
                break;
        }
    }

}

void printDoubleData(double * arr, int n) {
    for(int i = 0; i < n; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}

void printCharData(char ** arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");
}

void printDoubleArray(int (* arr)[3], int n, int m) {
    for(int i = 0; i < n; i++) {
        printf("[");
        for(int j = 0; j < m; j++) {
            printf("%d, ", arr[i][j]);
        }
        printf("]\n");
    }
}

void printScore(score_t * arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n", arr[i].kor, arr[i].eng, arr[i].mat);
    }
    printf("\n");
}

void printAllType(void * arr, int n, int size) {
    for (int i = 0; i < n; i++) {
       puts(arr);
    }
    printf("\n");
}

int comp_asc(int a, int b) {
    return a > b;
}

int comp_desc(int a, int b) {
    return a < b;
}

int compint(const void * a, const void * b) {
    return *(int *) a - *(int *) b;
}

int compDouble(const void * a, const void * b) {
    double da = *(double *) a;
    double db = *(double *) b;

    if(da > db) return 1;
    if (da == db) return 0;
    return -1;
}

int compChar(const void * a, const void * b) {
    return strcmp(*(char **) a, *(char **) b);
}

int compDA(const void * a, const void * b) {
    int * ap = *(int (*)[3]) a;
    int * bp = *(int (*)[3]) b;
    return ap[1] - bp[1];
}

int compScore(const void * a, const void * b) {
    score_t scoreA = *(score_t *) a;
    score_t scoreB = *(score_t *) b;
    return scoreA.mat - scoreB.mat;
}

int findIndex(int * arr, int start, int n, int (*comp)(int, int)) {

    int index = start;

    for(int i = start + 1; i < n; i++) {
        if(comp(arr[index], arr[i]))
            index = i;
    }

    return index;
}

void selectionSort(int * arr, int n, int (*comp)(int, int)) {

    for(int i = 0; i < n - 1; i++) {
        int minIndex = findIndex(arr, i, n, comp);
        swap(arr + i, arr + minIndex);
    }

}

void bubbleSort(int * arr, int n, int (*comp)(int, int)) {

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - 1 - i; j++) {
            if(comp(arr[j], arr[j + 1]))
                swap(arr + j, arr + (j + 1));
        }
    }

}

void insertionSort(int * arr, int n, int (*comp)(int, int)) {

    for(int i = 1; i < n; i++) {
        for(int j = i - 1; j >= 0; j--) {
            if(comp(arr[j], arr[j + 1])) 
                swap(arr + j, arr + (j + 1));
            else
                break;
        }
    }

}