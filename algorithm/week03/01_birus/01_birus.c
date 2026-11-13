#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if 1

#define MAX_N (100 + 2)

int arr[MAX_N][MAX_N] = { 0 };
int V, E;
int visited[MAX_N] = { 0 };

typedef struct {
    int q[MAX_N];
    int f;
    int r;
} queue;

// 인접행렬
void inputData1(void);
void printAdj1(int (*)[MAX_N], int);
void dfs1(int n);
void bfs1(int n);

// 인접리스트
void inputData2(void);
void printAdj2(int (*)[MAX_N], int);
void dfs2(int n);
void bfs2(int n);

// 공통
void printData(int (*)[MAX_N], int);
void printVisit(int * arr, int n);
void printAns(int *, int);

int main(void) {

    freopen("01_data.txt", "r", stdin);

#if 0
    inputData1();
    printAdj1(arr, 2);
    printData(arr, V);
    // dfs1(1);
    bfs1(1);
    printVisit(visited, V);
    printAns(visited, V);

#else
    inputData2();
    printAdj2(arr, 1);
    printData(arr, V);
    bfs2(1);
    printVisit(visited, V);
    printAns(visited, V);

#endif

    return 0;
}

// 인접행렬
void inputData1(void) {
    int v1, v2;

    scanf("%d %d", &V, &E);

    for(int i = 0; i < E; i++) {
        scanf("%d %d", &v1, &v2);
        arr[v1][v2] = 1;
        arr[v2][v1] = 1;
    }
}

void printAdj1(int (*arr)[MAX_N], int n) {

    printf("%d : ", n);
    for(int i = 1; i <= V; i++) {
        int num = arr[n][i];
        if(num) printf("%d ", i);
    }
    printf("\n");
}

void dfs1(int n) {
    visited[n] = 1;

    for(int i = 1; i <= V; i++) {
        int num = arr[n][i];

        if(num && !visited[i]) dfs1(i);
    }
}

void bfs1(int n) {
    queue q1 = { { 0 }, 0, 0 };

    visited[n] = 1;
    q1.q[q1.r++] = n;

    while(q1.r != q1.f) {
        int node = q1.q[q1.f++];

        for(int i = 1; i <= V; i++) {
            if(arr[node][i] && !visited[i]) {
                visited[i] = 1;
                q1.q[q1.r++] = i;
            }
        }
    }
}

// 인접리스트
void inputData2(void) {
    int v1, v2;

    scanf("%d %d", &V, &E);

    for(int i = 0; i < E; i++) {
        scanf("%d %d", &v1, &v2);
        arr[v1][++arr[v1][0]] = v2;
        arr[v2][++arr[v2][0]] = v1;
    }
}

void printAdj2(int (*arr)[MAX_N], int n) {

    int cnt = arr[n][0];

    if(cnt == 0) return;

    printf("%d : ", n);
    for(int i = 1; i <= cnt; i++) {
        printf("%d ", arr[n][i]);
    }
    printf("\n");
}

void dfs2(int n) {
    visited[n] = 1;

    int cnt = arr[n][0];
    for(int i = 1; i <= cnt; i++) {
        int num = arr[n][i];
        if(!visited[num]) dfs2(num);
    }
}

void bfs2(int n) {
    queue q2 = { { 0 }, 0, 0 };

    visited[n] = 1;
    q2.q[q2.r++] = n;

    while(q2.r != q2.f) {
        int node = q2.q[q2.f++];

        int cnt = arr[node][0];
        for(int i = 1; i <= cnt; i++) {
            int num = arr[node][i];
            if(!visited[num]) {
                visited[num] = 1;
                q2.q[q2.r++] = num;
            }
        }
    }
}

// 공통
void printData(int (*arr)[MAX_N], int n) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printVisit(int * arr, int n) {
    for(int i = 1; i <= n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printAns(int * arr, int n) {
    int cnt = 0;
    for(int i = 2; i <= n; i++) {
        int num = arr[i];
        if(num) cnt++;
    }
    printf("%d\n", cnt);
}

#endif