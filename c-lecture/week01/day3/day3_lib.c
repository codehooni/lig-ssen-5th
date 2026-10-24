#if 1
#include "day3_lib.h"

int a = 20;

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

#endif